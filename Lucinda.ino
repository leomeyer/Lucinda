// Lucinda v2
// by Leo Meyer <leo@leomeyer.de>

#if not defined(__AVR_ATmega2560__)
#error This sketch is designed to run on an Arduino Mega with an ATmega 2560 processor.
#endif

#include "lucinda.h"

#include <Arducom.h>

// #define LUCINDA_DEBUG 1

/*******************************************************
* Data Structures
*******************************************************/

// Defines how the output pins map to PWM registers.
// This table is filled at setup from the information in outputPins.
timermap_t timerMaps[LUCINDA_MAXCHANNELS];

// Holds the PWM definition and counter for each channel.
channel_t channels[LUCINDA_MAXCHANNELS];

// Buffer for each channel with changes to apply at the end of a period.
channel_t channel_buffers[LUCINDA_MAXCHANNELS];

volatile uint8_t global_brightness = 255;
volatile uint8_t global_speed = 1;

/*******************************************************
* Constants
*******************************************************/

// Defines the pins of the connected lamps.
// The first pin is for the halogen lamp.
// The others are for the LEDs. If a lamp is not connected use 0.
// The halogen lamp should be connected to a TIMER2 pin (9 or 10) because it can run on an 8 bit PWM.
// All other lamps must be connected to a pin that uses as 10-bit PWM capable timer except TIMER0 (pins 4, 13).
uint8_t outputPins[LUCINDA_MAXCHANNELS] = {10, 2, 3, 5, 6, 7, 8, 11, 12};

// minimal test definitions for Uno etc.
// uint8_t outputPins[LUCINDA_MAXCHANNELS] = {11, 3, 5, 6, 9, 10, 0, 0, 0};

// include constant table definitions
#include "tables.h"

/*******************************************************
* Internal functions
*******************************************************/

inline void resetCounters(channel_t* channel) {
  channel->counter = 0;
  channel->macrocycle_counter = 0;
}

/*******************************************************
* PWM Control
*******************************************************/

inline void setPinValue(uint8_t pin, timermap_t* timermap, uint16_t val) {
  if (pin == 0)
    return;
  int16_t mval = (pin == outputPins[0] ? 1023 - val : val);
  // set PWM value, do not use analogWrite for performance
  if (mval <= 0)
    // switch off PWM
    *(volatile char*)(timermap->timerReg) &= ~_BV(timermap->outputMode);
  else {
    *(volatile char*)(timermap->timerReg) |= _BV(timermap->outputMode);
    if (timermap->is8Bit) {
      *(volatile char*)(timermap->ocrRegH) = mval / 4;
    } else {
      // special treatment for halogen pin (invert)
      *(volatile char*)(timermap->ocrRegH) = mval / 256;
      *(volatile char*)(timermap->ocrRegL) = mval % 256;
    }
  }
}

inline void setLightValues(channel_t* channel, uint16_t val) {
  if ((channel->flags & CHANNELFLAG_NO_LIGHTS) == CHANNELFLAG_NO_LIGHTS)
    return;
  // apply value to the controlled pins
  // special case: first pin (halogen lamp) is controlled by
  // any channel that has its bitmask value set to 0
  if (channel->bitmask == 0) {
    setPinValue(outputPins[0], &(timerMaps[0]), val);
  } else {
    uint8_t b = 1;    // the lowest bit corresponds to the first LED
    uint8_t mask = channel->bitmask;
    while (mask > 0) {
      // test bit if the pin is defined
      if ((mask & 1) == 1 && outputPins[b] > 0) {
        // bit is set, i. e. LED no. b is controlled by this channel
/*  pin 4 cannot be used because it is controlled by TIMER0
        // special treatment for pin 4 (won't turn off completely on Mega)
        if (outputPins[b] == 4)
          analogWrite(outputPins[b], val / 4);
        else
*/        
        // set PWM value, do not use analogWrite for performance
        setPinValue(outputPins[b], &(timerMaps[b]), val);
      }
      mask >>= 1;
      b++;
    }
  }
}

inline void processChannel(int i) {
#ifdef LUCINDA_DEBUG  
    Serial.print("Channel: ");
    Serial.print(i);
    Serial.print(" @: ");
    Serial.println(channels[i].counter);
#endif          
  uint16_t val = 0;
  if (channels[i].enabled == 0) {
#ifdef LUCINDA_DEBUG  
    Serial.println("Channel is disabled");
#endif          
    // a disabled channel's lights will be switched off
    setLightValues(&(channels[i]), 0);
  } else {
    // assume an active cycle when macrocycle length is less than 2
    bool activeCycle = channels[i].macrocycle_length < 2;
    // or the channel is in an active dutycycle
    // this ensures that a duty cycle is completed even in case of counter rollover
    if ((channels[i].internal_flags & CHANNEL_IFLAG_ON_PHASE) == CHANNEL_IFLAG_ON_PHASE)
      activeCycle |= true;
    // macrocycling enabled?
    if (!activeCycle && channels[i].macrocycle_count > 0) {
      uint8_t macrocycleEnd = channels[i].macrocycle_shift + channels[i].macrocycle_count;
      activeCycle = (macrocycleEnd <= channels[i].macrocycle_length
                      ? (channels[i].macrocycle_counter >= channels[i].macrocycle_shift) && (channels[i].macrocycle_counter < macrocycleEnd)
                      : (channels[i].macrocycle_counter < macrocycleEnd - channels[i].macrocycle_length) || (channels[i].macrocycle_counter >= channels[i].macrocycle_shift));
      // special case: a wrapped-over macrocycle has not yet "begun"; to avoid undesired starting in the middle of such a macrocycle
      // detect whether the macrocycle has started at least once
      if (macrocycleEnd > channels[i].macrocycle_length) {
        // in the "middle" of a macrocycle?
        if (channels[i].macrocycle_counter < macrocycleEnd - channels[i].macrocycle_length) {
          // allow this only if the start of a macrocycle has already been detected
          activeCycle = (channels[i].internal_flags & CHANNEL_IFLAG_MACROCYCLE_OK) == CHANNEL_IFLAG_MACROCYCLE_OK;
        } else {
          // at start of the phase, set the flag to remember this
          channels[i].internal_flags |= CHANNEL_IFLAG_MACROCYCLE_OK;
        }
      }
    }
    // macrocycle active?
    if (activeCycle) {
#ifdef LUCINDA_DEBUG
        Serial.println("Active cycle");
#endif
      // macrocycle changed?
      if ((channels[i].internal_flags & CHANNEL_IFLAG_IN_MACROCYCLE) == 0) {
        channels[i].internal_flags |= CHANNEL_IFLAG_IN_MACROCYCLE | CHANNEL_IFLAG_MACROCYCLE_CHANGE;
#ifdef LUCINDA_DEBUG
        Serial.println("Macrocycle change detected");
#endif
      } else {
        // already "on" phase
        channels[i].internal_flags &= ~CHANNEL_IFLAG_MACROCYCLE_CHANGE;
      }
      val = channels[i].brightness;  // assume square
      // calculate length of in-phase cycle in ticks
      int16_t phaseLength = ((uint32_t)channels[i].period * (channels[i].dutycycle + 1)) / 256;
#ifdef LUCINDA_DEBUG
        Serial.print("phaseLength: " );
        Serial.println(phaseLength);
#endif
      // apply phaseshift
      int16_t phaseEnd = channels[i].phaseshift + phaseLength;
#ifdef LUCINDA_DEBUG
        Serial.print("phaseEnd: " );
        Serial.println(phaseEnd);
#endif
      int16_t phaseStart = channels[i].phaseshift;
#ifdef LUCINDA_DEBUG
        Serial.print("phaseStart: " );
        Serial.println(phaseStart);
#endif
      // "on" phase?
      bool onPhase = (channels[i].dutycycle > 0) && (phaseEnd <= channels[i].period     // no wrapover?
                        ? (channels[i].counter >= phaseStart) && (channels[i].counter < phaseEnd)   // counter must be within phase start and end
                        : (channels[i].counter < phaseEnd - channels[i].period) || (channels[i].counter >= phaseStart));  // correct for wrapover
      // special case: a wrapped-over phase has not yet "begun"; to avoid undesired starting in the middle of such a phase
      // detect whether the phase has started at least once
      if (phaseEnd > channels[i].period) {
        // in the "middle" of a phase?
        if (channels[i].counter < phaseEnd - channels[i].period) {
          // allow this only if the start of a phase has already been detected
          onPhase = (channels[i].internal_flags & CHANNEL_IFLAG_PHASE_OK) == CHANNEL_IFLAG_PHASE_OK;
        } else {
          // at start of the phase, set the flag to remember this
          channels[i].internal_flags |= CHANNEL_IFLAG_PHASE_OK;
        }
      }
      if (onPhase) {
#ifdef LUCINDA_DEBUG
        Serial.println("On phase");
#endif
        // "on" phase
        // phase changed?
        if ((channels[i].internal_flags & CHANNEL_IFLAG_ON_PHASE) == 0) {
          channels[i].internal_flags |= CHANNEL_IFLAG_ON_PHASE | CHANNEL_IFLAG_PHASE_CHANGE;
#ifdef LUCINDA_DEBUG
          Serial.println("Phase change detected");
#endif
        } else {
          // already "on" phase
          channels[i].internal_flags &= ~CHANNEL_IFLAG_PHASE_CHANGE;
        }
        // non-square wave?
        if (channels[i].wavetable != nullptr) {
          // calculate the index in the wavetable
          uint16_t index = channels[i].counter >= phaseStart    // no wrapover?
                            ? (int32_t)(channels[i].counter - phaseStart) * (WAVETABLE_SIZE - 1) / phaseLength
                            : (int32_t)(channels[i].period - (phaseEnd - channels[i].counter - phaseLength)) * (WAVETABLE_SIZE - 1) / phaseLength;   // correct for wrapover
          // reverse?
          if ((channels[i].flags & CHANNELFLAG_REVERSE) == CHANNELFLAG_REVERSE)
            index = (WAVETABLE_SIZE - 1) - index;
#ifdef LUCINDA_DEBUG
          Serial.print("WT index: ");
          Serial.println(index);
#endif
          val = pgm_read_word((uint32_t)channels[i].wavetable + index * 2);
        }
        // adjust brightness
        if (channels[i].brightness < 255) {
          val = ((uint32_t)val * channels[i].brightness) / 256;
        }
        // apply offset
        if (val < channels[i].offset)
          val = channels[i].offset;
      } else {
        // "off" phase
        // phase changed?
        if ((channels[i].internal_flags & CHANNEL_IFLAG_ON_PHASE) == CHANNEL_IFLAG_ON_PHASE) {
          channels[i].internal_flags &= ~CHANNEL_IFLAG_ON_PHASE;
          channels[i].internal_flags |= CHANNEL_IFLAG_PHASE_CHANGE;
        } else {
          // already "off" phase
          channels[i].internal_flags &= ~CHANNEL_IFLAG_PHASE_CHANGE;
        }
        val = channels[i].offset;
      }
    } else {
#ifdef LUCINDA_DEBUG
        Serial.println("Inactive cycle");
#endif
      // macrocycle changed?
      if ((channels[i].internal_flags & CHANNEL_IFLAG_IN_MACROCYCLE) == CHANNEL_IFLAG_IN_MACROCYCLE) {
        channels[i].internal_flags &= ~CHANNEL_IFLAG_IN_MACROCYCLE;
        channels[i].internal_flags |= CHANNEL_IFLAG_MACROCYCLE_CHANGE;
        // clear PHASE_OK to prevent undesired flickering
        channels[i].internal_flags &= ~CHANNEL_IFLAG_PHASE_OK;
      } else {
        // already "off" phase
        channels[i].internal_flags &= ~CHANNEL_IFLAG_MACROCYCLE_CHANGE;
      }
      // no active macrocycle, always at base level
      val = channels[i].offset;
    }

    // inversion?
    if ((channels[i].flags & CHANNELFLAG_INVERT) == CHANNELFLAG_INVERT)
      val = 1024 - val;

    // apply global brightness
    if (global_brightness < 255) {
      val = ((uint32_t)val * global_brightness) / 256;
    }
    
    // apply eye correction?
    if ((channels[i].flags & CHANNELFLAG_NO_EYE_CORRECTION) == 0)
      val = pgm_read_word((uint32_t)&eye_correction + val * 2);

#ifdef LUCINDA_DEBUG
        Serial.print("val: " );
        Serial.println(val);
#endif
    // set value to all controlled outputs
    setLightValues(&(channels[i]), val);
  }  // if (channel enabled)

  channels[i].counter += global_speed;
  // period end reached?
  if (channels[i].counter > channels[i].period) {
    // copy from buffer requested?
    if ((channels[i].internal_flags & CHANNEL_IFLAG_COPY) == CHANNEL_IFLAG_COPY) {
      // before applying new channel settings, switch off all lights
      setLightValues(&(channels[i]), 0);
      channels[i] = channel_buffers[i];
    } else {
      channels[i].counter = 0;
      // increase macrocycle counter at end of period
      channels[i].macrocycle_counter++;
      if (channels[i].macrocycle_counter >= channels[i].macrocycle_length) {
        channels[i].macrocycle_counter = 0;
      }
    }
  }   // period end
}

ISR(PWM_TIMER_VECTOR)        // interrupt service routine 
{
#ifndef LUCINDA_DEBUG  
  PWM_TIMER_COUNTER = PWM_TIMER_PRELOAD;   // preload timer

  // disable all LEDs when the speed is 0
  if (global_speed == 0) {
    for (int i = 0; i < LUCINDA_MAXCHANNELS; i++)
      setLightValues(&(channels[i]), 0);
    return;
  }

  // regular running mode
  // go through all channels
  for (int i = 0; i < LUCINDA_MAXCHANNELS; i++) {
    processChannel(i);
  }
#endif
}

inline void calculatePhaseshift(channel_t& channel) {
  if (channel.period > MAX_PERIOD - 1)
    channel.period = MAX_PERIOD - 1;
  channel.phaseshift = (int32_t)channel.period * channel.phaseshiftPercent / 256;
}

/*******************************************************
* Arducom commands
*******************************************************/

// This command returns the configuration of the Lucinda setup.
class ArducomGetConfig: public ArducomCommand {
public:
  ArducomGetConfig() : ArducomCommand(ARDUCOM_CMD_GET_CONFIG, 0) {}   // this command expects zero parameter bytes
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    const char* configStr = "Cl";
    strncpy((char*)destBuffer, configStr, maxBufferSize);
    destBuffer[1] = '0' + LUCINDA_MAXCHANNELS;
    *dataSize = strlen((const char*)destBuffer);
    return ARDUCOM_OK;
  }
};

// This command defines the configuration of a channel.
// It expects the following parameters:
// byte 0: channel number (may be 0 to LUCINDA_MAXCHANNELS - 1)
// byte 1: enabled flag. The channel is used if the flag is 1.
// byte 2: bit mask for the outputs. Each bit corresponds to an LED. If no bit is set the channel is for the halogen lamp.
// bytes 3 and 4: period (LSB first)
// byte 5: offset
// byte 6: brightness factor
// byte 7: duty cycle
// bytes 8: phase shift
// byte 9: waveform to use (0: square, 1: sine, 2: triangle, 3: flicker, 4: linear/sawtooth)
// byte 10: flags that control additional behavior
// byte 11: macrocycle length
// byte 12: macrocycle count
// byte 13: macrocycle shift
// If an error occurs the requested changes are not applied.
class ArducomDefineChannel: public ArducomCommand {
public:
  ArducomDefineChannel() : ArducomCommand(ARDUCOM_CMD_DEFINE_CHANNEL, 14) {}   // number of expected parameter bytes
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = 0;
      return ARDUCOM_FUNCTION_ERROR;
    }
    channel_t local;    // local buffer
    local.enabled = dataBuffer[1] & 0x01; // the lowest bit decides
    local.bitmask = dataBuffer[2];
    local.period = (uint16_t)dataBuffer[3] + dataBuffer[4] * 256;
    if (local.period > WAVETABLE_SIZE * 10) {
      *errorInfo = 3;
      return ARDUCOM_FUNCTION_ERROR;
    }
    local.offset = dataBuffer[5] * 4;
    local.brightness = dataBuffer[6] * 4;
    local.dutycycle = dataBuffer[7];
    local.phaseshiftPercent = dataBuffer[8];
    calculatePhaseshift(local);
    uint8_t wavetable = dataBuffer[9];
    switch (wavetable) {
      case 0: // square
        local.wavetable = nullptr;
        break;
      case 1: // sine
        local.wavetable = &WAVE_SINE;
        break;
      case 2: // triangle
        local.wavetable = &WAVE_TRIANGLE;
        break;
      case 3: // flicker
        local.wavetable = &WAVE_FLICKER;
        break;
      case 4: // linear (sawtooth)
        local.wavetable = &WAVE_LINEAR;
        break;
      default:  {
        *errorInfo = 9;
        return ARDUCOM_FUNCTION_ERROR;
      }
    }
    local.flags = dataBuffer[10] & CHANNELFLAG_ALL;
    local.macrocycle_length = dataBuffer[11];
    local.macrocycle_count = dataBuffer[12];
    local.macrocycle_shift = dataBuffer[13];
    // limit count
    if (local.macrocycle_count > local.macrocycle_length)
      local.macrocycle_count = local.macrocycle_length;
    // limit shift
    if (local.macrocycle_shift > local.macrocycle_length)
      local.macrocycle_shift = local.macrocycle_length > 0 ? local.macrocycle_shift % local.macrocycle_length : 0;

    // reset internal management data
    resetCounters(&local);
    local.internal_flags = 0;

    // copy local changes to the buffer
    channel_buffers[channelNo] = local;
    // apply directly?
    if ((dataBuffer[11] & CHANNELFLAG_APPLY) == CHANNELFLAG_APPLY) {
      // copy the local changes to the channel
      // disable interrupts during copy
      noInterrupts();
      // switch off all previous lights
      setLightValues(&(channels[channelNo]), 0);      
      channels[channelNo] = local;
      interrupts();
    } else {
      // request the interrupt routine to copy the data after the next period
      noInterrupts();
      channels[channelNo].internal_flags |= CHANNEL_IFLAG_COPY;
      interrupts();
    }
    
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the global speed of the channels in ticks. One tick corresponds to one millisecond.
class ArducomSetGlobalSpeed: public ArducomCommand {
public:
  ArducomSetGlobalSpeed() : ArducomCommand(ARDUCOM_CMD_SET_GLOBAL_SPEED, 1) {}   // this command expects one parameter byte
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    // speed increased after processing has been disabled?
    if ((global_speed == 0) && (dataBuffer[0] > 0)) {
      // need to reset all counters
      for (int i = 0; i < LUCINDA_MAXCHANNELS; i++) {
        resetCounters(&(channel_buffers[i]));
      }
      // copy all buffers to actual definitions
      noInterrupts();
      memcpy(channels, channel_buffers, sizeof(channel_t) * LUCINDA_MAXCHANNELS);
      interrupts();
    }
    global_speed = dataBuffer[0];
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the global brightness.
class ArducomSetGlobalBrightness: public ArducomCommand {
public:
  ArducomSetGlobalBrightness() : ArducomCommand(ARDUCOM_CMD_SET_GLOBAL_BRIGHTNESS, 1) {}   // this command expects one parameter byte
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    global_brightness = dataBuffer[0];
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command enables a channel.
class ArducomEnableChannel : public ArducomCommand {
public:
  ArducomEnableChannel() : ArducomCommand(ARDUCOM_CMD_ENABLE_CHANNEL, 1) {}   // this command expects one parameter byte
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_FUNCTION_ERROR;
    }
    // need to reset counters?
    if (channels[channelNo].enabled == 0) {
      // no need to disable interrupts here because the channel is not yet enabled
      resetCounters(&(channels[channelNo]));
    }
    // modify channel directly
    channels[channelNo].enabled = 1;
    channel_buffers[channelNo].enabled = 1;
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command disables a channel.
class ArducomDisableChannel : public ArducomCommand {
public:
  ArducomDisableChannel() : ArducomCommand(ARDUCOM_CMD_DISABLE_CHANNEL, 1) {}   // this command expects one parameter byte
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_FUNCTION_ERROR;
    }
    channel_buffers[channelNo].enabled = 0;
    // modify channel directly
    channels[channelNo].enabled = 0;
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the period (frequency) of a channel.
class ArducomSetChannelPeriod: public ArducomCommand {
public:
  ArducomSetChannelPeriod() : ArducomCommand(ARDUCOM_CMD_SET_CHANNEL_PERIOD, 3) {}   // this command expects three parameter bytes
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_FUNCTION_ERROR;
    }
    // modify channel directly
    noInterrupts();
    channels[channelNo].period = (uint16_t)dataBuffer[1] + dataBuffer[2] * 256;
    calculatePhaseshift(channels[channelNo]);
    interrupts();
    channel_buffers[channelNo].period = (uint16_t)dataBuffer[1] + dataBuffer[2] * 256;
    calculatePhaseshift(channel_buffers[channelNo]);
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the phase shift of a channel (relative from 0 .. 255).
class ArducomSetChannelPhaseShift: public ArducomCommand {
public:
  ArducomSetChannelPhaseShift() : ArducomCommand(ARDUCOM_CMD_SET_CHANNEL_PHASESHIFT, 2) {}   // this command expects two parameter bytes
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_FUNCTION_ERROR;
    }
    // modify channel directly
    channels[channelNo].phaseshiftPercent = dataBuffer[1];
    noInterrupts();
    calculatePhaseshift(channels[channelNo]);
    interrupts();
    channel_buffers[channelNo].phaseshiftPercent = dataBuffer[1];
    calculatePhaseshift(channel_buffers[channelNo]);
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the offset (lowest brightness) of a channel.
class ArducomSetChannelOffset: public ArducomCommand {
public:
  ArducomSetChannelOffset() : ArducomCommand(ARDUCOM_CMD_SET_CHANNEL_OFFSET, 2) {}   // this command expects two parameters
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_FUNCTION_ERROR;
    }
    // modify channel directly
    channels[channelNo].offset = dataBuffer[1] * 4;
    channel_buffers[channelNo].offset = dataBuffer[1] * 4;
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the brightness of a channel.
class ArducomSetChannelBrightness: public ArducomCommand {
public:
  ArducomSetChannelBrightness() : ArducomCommand(ARDUCOM_CMD_SET_CHANNEL_BRIGHTNESS, 2) {}   // this command expects two parameters
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_FUNCTION_ERROR;
    }
    // modify channel directly
    channels[channelNo].brightness = dataBuffer[1] * 4;
    channel_buffers[channelNo].brightness = dataBuffer[1] * 4;
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the duty cycle of a channel.
class ArducomSetChannelDutyCycle: public ArducomCommand {
public:
  ArducomSetChannelDutyCycle() : ArducomCommand(ARDUCOM_CMD_SET_CHANNEL_DUTYCYCLE, 2) {}   // this command expects two parameters
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_FUNCTION_ERROR;
    }
    // modify channel directly
    channels[channelNo].dutycycle = dataBuffer[1];
    channel_buffers[channelNo].dutycycle = dataBuffer[1];
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};


/*******************************************************
* Arducom system variables
*******************************************************/

// setup Arducom communication on the Serial stream
ArducomTransportStream arducomTransport(&Serial);
Arducom arducom(&arducomTransport);

/*******************************************************
* Setup
*******************************************************/

void addCommand(ArducomCommand* cmd) {
  uint8_t code = arducom.addCommand(cmd);
  if (code != ARDUCOM_OK) {
    Serial.print(F("Setup error: Error adding command "));
    Serial.print((int)cmd->commandCode);
    Serial.print(F(" (code "));
    Serial.print(code);
    Serial.println(F(")"));
    while (true);
  }
}

void fillTimerMaps() {
  for (int i = 0; i < LUCINDA_MAXCHANNELS; i++) {
    if (outputPins[i] == 0)
      continue;
    // on the first pin (the halogen lamp pin) allow the use of an 8 bit timer
    if (!fillTimerMap(&(timerMaps[i]), outputPins[i], i == 0)) {
      if (i == 0)
        Serial.print(F("Setup error: Pin not on a valid 8- or 10-bit PWM capable timer or on TIMER0: "));
      else
        Serial.print(F("Setup error: Pin not on a valid 10-bit PWM capable timer or on TIMER0: "));
      Serial.println(outputPins[i]);
      while (true);
    }
  }
/*  
  Serial.print("timerMaps[0] = {");
  Serial.print(timerMaps[0].timerReg);
  Serial.print(", ");
  Serial.print(timerMaps[0].outputMode);
  Serial.print(", ");
  Serial.print(timerMaps[0].ocrReg);
  Serial.println(")");
*/  
}

void setup()
{
  
#if defined(__AVR_ATmega2560__)

#endif

  // setup pins
  // special treatment for halogen pin (hardware version 1 which inverts the halogen pin)
  pinMode(outputPins[0], OUTPUT);
  analogWrite(outputPins[0], 255);
  for (int i = 1; i < LUCINDA_MAXCHANNELS; i++)
    if (outputPins[i] != 0) {
      pinMode(outputPins[i], OUTPUT);
      analogWrite(outputPins[i], 0);
    }
  
	// initialize communication
	Serial.begin(ARDUCOM_DEFAULT_BAUDRATE);

#ifdef LUCINDA_DEBUG
  Serial.println(F(DEVICE_NAME));
#endif

  fillTimerMaps();

  // setup timers for 10 bit non-inverted fast PWM
  TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1);
  TCCR1B = (1 << WGM12) | (1 << CS11);
  TCCR3A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1);
  TCCR3B = (1 << WGM12) | (1 << CS11);
  TCCR4A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1);
  TCCR4B = (1 << WGM12) | (1 << CS11);
  
  uint8_t code;
	// setup Arducom system
  addCommand(new ArducomVersionCommand(DEVICE_NAME));
  addCommand(new ArducomGetConfig());
  addCommand(new ArducomDefineChannel());
  addCommand(new ArducomSetGlobalSpeed());
  addCommand(new ArducomSetGlobalBrightness());
  addCommand(new ArducomEnableChannel());
  addCommand(new ArducomDisableChannel());
  addCommand(new ArducomSetChannelPeriod());
  addCommand(new ArducomSetChannelPhaseShift());
  addCommand(new ArducomSetChannelOffset());
  addCommand(new ArducomSetChannelBrightness());
  addCommand(new ArducomSetChannelDutyCycle());

#ifdef LUCINDA_DEBUG
  Serial.println(F("Setup complete."));
#endif

  // test: initialize channel 0
  channel_buffers[0].period = WAVETABLE_SIZE;
  channel_buffers[0].enabled = 0;
  channel_buffers[0].dutycycle = 127;
/*
#define TESTSPEED / 2
  for (int i = 1; i < LUCINDA_MAXCHANNELS; i++) {
    channel_buffers[i].period = WAVETABLE_SIZE TESTSPEED;
    channel_buffers[i].bitmask = 1 << (i - 1);
    channel_buffers[i].enabled = 1;
    channel_buffers[i].brightness = 127;
    channel_buffers[i].offset = 50;
    channel_buffers[i].dutycycle = 127;
    channel_buffers[i].phaseshift = ((i - 1) * WAVETABLE_SIZE TESTSPEED / LUCINDA_MAXCHANNELS);
    channel_buffers[i].wavetable = &WAVE_SINE;
    channel_buffers[i].macrocycle_length = 16;
    channel_buffers[i].macrocycle_count = 3;
    channel_buffers[i].macrocycle_shift = i * 2;    
  } 
*/    
#ifdef LUCINDA_DEBUG
    channel_buffers[1].period = WAVETABLE_SIZE;
    channel_buffers[1].bitmask = 1 | 4 | 16 | 64;
    channel_buffers[1].enabled = 1;
    channel_buffers[1].brightness = 512;
    channel_buffers[1].offset = 0;
    channel_buffers[1].dutycycle = 127;
    channel_buffers[1].phaseshiftPercent = 0;
    channel_buffers[1].wavetable = &WAVE_SINE;
    calculatePhaseshift(channel_buffers[1]);

    channel_buffers[2].period = WAVETABLE_SIZE;
    channel_buffers[2].bitmask = 2 | 8 | 32 | 128;
    channel_buffers[2].enabled = 1;
    channel_buffers[2].brightness = 512;
    channel_buffers[2].offset = 0;
    channel_buffers[2].dutycycle = 127;
    channel_buffers[2].phaseshiftPercent = 50;
    channel_buffers[2].wavetable = &WAVE_SINE;
    calculatePhaseshift(channel_buffers[2]);
//    channel_buffers[1].enabled = 1;
//    channel_buffers[6].enabled = 1;

  // copy buffers to channels
  memcpy(channels, channel_buffers, sizeof(channel_t) * LUCINDA_MAXCHANNELS);


  Serial.println("Start test");

  int i = 1;

  int32_t j = 0;
  while (j++ < channels[i].period) {
      processChannel(i);
  }

  Serial.println("Test done");
  while (1);

#endif
/*  
  channels[2].period = WAVETABLE_SIZE * 2;
  channels[2].bitmask = 4;
  channels[2].enabled = 1;
  channels[2].brightness = 255;
  channels[2].dutycycle = 127;
  channels[2].phaseshift = WAVETABLE_SIZE;
*/
  noInterrupts();

  // copy buffers to channels
  memcpy(channels, channel_buffers, sizeof(channel_t) * LUCINDA_MAXCHANNELS);
  
  PWM_TIMER_INIT

  interrupts();
}

/*******************************************************
* Main loop
*******************************************************/

void loop()
{
	// handle Arducom commands
	arducom.doWork();
}
