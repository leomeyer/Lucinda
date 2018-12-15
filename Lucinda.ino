// Lucinda v2
// by Leo Meyer <leo@leomeyer.de>

#if not defined(__AVR_ATmega2560__)
#error This sketch is designed to run on an Arduino Mega with an ATmega 2560 processor.
#endif

#include "lucinda.h"

#include <Arducom.h>

// #define LUCINDA_DEBUG 1

// for some reason this forward declaration is necessary
// void addCommand(ArducomCommand* cmd);

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
uint8_t outputPins[LUCINDA_MAXCHANNELS] = {11, 2, 3, 4, 5, 6, 7, 8, 9};

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

inline void setPinValue(uint8_t pin, timermap_t* timermap, uint8_t val) {
  if (pin == 0)
    return;

  // set PWM value, do not use analogWrite for performance
  *(volatile char*)(timermap->timerReg) |= _BV(timermap->outputMode);
  // special treatment for halogen pin (invert)
  *(volatile char*)(timermap->ocrReg) = (pin == outputPins[0] ? 255 - val : val);
}

inline void setChannelValues(channel_t* channel, uint8_t val) {
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
        // special treatment for pin 4 (won't turn off completely on Mega)
        if (outputPins[b] == 4)
          analogWrite(outputPins[b], val);
        else {
          // set PWM value, do not use analogWrite for performance
          setPinValue(outputPins[b], &(timerMaps[b]), val);
        }
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
  uint8_t val = 0;
  if (channels[i].enabled == 0) {
#ifdef LUCINDA_DEBUG  
    Serial.println("Channel is disabled");
#endif          
    // a disabled channel's lights will be switched off
    setChannelValues(&(channels[i]), 0);
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
          val = pgm_read_byte((uint32_t)channels[i].wavetable + index);
        }
        // adjust brightness
        if (channels[i].brightness < 255) {
          val = ((uint16_t)val * channels[i].brightness) / 256;
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
      val = 255 - val;

    // apply global brightness
    if (global_brightness < 255) {
      val = ((uint16_t)val * global_brightness) / 256;
    }
    
    // apply eye correction?
    if ((channels[i].flags & CHANNELFLAG_NO_EYE_CORRECTION) == 0)
      val = pgm_read_byte((uint32_t)&eye_correction + val);

#ifdef LUCINDA_DEBUG
        Serial.print("val: " );
        Serial.println(val);
#endif

    // set value to all controlled outputs
    setChannelValues(&(channels[i]), val);
  }  // if (channel enabled)

  channels[i].counter += global_speed;
  // period end reached?
  if (channels[i].counter > channels[i].period) {
    // copy from buffer requested?
    if ((channels[i].internal_flags & CHANNEL_IFLAG_COPY) == CHANNEL_IFLAG_COPY) {
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
      setChannelValues(&(channels[i]), 0);
    return;
  }

  // regular running mode
  // go through all channels
  for (int i = 0; i < LUCINDA_MAXCHANNELS; i++) {
    processChannel(i);
  }
#endif
}

/*******************************************************
* Arducom commands
*******************************************************/
#include "commands.h"

// This command returns the configuration of the Lucinda setup.
class ArducomGetConfig: public ArducomCommand {
public:
  ArducomGetConfig() : ArducomCommand(ARDUCOM_CMD_GET_CONFIG, 0) {}   // this command expects zero parameters
  
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
// bytes 8 and 9: phase shift (LSB first)
// byte 10: waveform to use (0: square, 1: sine, 2: triangle, 3: flicker, 4: linear/sawtooth)
// byte 11: flags that control additional behavior
// byte 12: macrocycle length
// byte 13: macrocycle count
// byte 14: macrocycle shift
// If an error occurs the requested changes are not applied.
class ArducomDefineChannel: public ArducomCommand {
public:
  ArducomDefineChannel() : ArducomCommand(ARDUCOM_CMD_DEFINE_CHANNEL, 15) {}   // number of expected parameter bytes
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
    }
    channel_t local;    // local buffer
    local.enabled = dataBuffer[1] & 0x01; // the lowest bit decides
    local.bitmask = dataBuffer[2];
    local.period = dataBuffer[3] + dataBuffer[4] * 256;
    if (local.period > WAVETABLE_SIZE * 10) {
      *errorInfo = 3;
      return ARDUCOM_FUNCTION_ERROR;
    }
    local.offset = dataBuffer[5];
    local.brightness = dataBuffer[6];
    local.dutycycle = dataBuffer[7];
    local.phaseshift = (dataBuffer[8] + dataBuffer[9] * 256) % local.period;
    uint8_t wavetable = dataBuffer[10];
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
        *errorInfo = 10;
        return ARDUCOM_FUNCTION_ERROR;
      }
    }
    local.flags = dataBuffer[11] & CHANNELFLAG_ALL;
    local.macrocycle_length = dataBuffer[12];
    local.macrocycle_count = dataBuffer[13];
    local.macrocycle_shift = dataBuffer[14];
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
class ArducomSetSpeed: public ArducomCommand {
public:
  ArducomSetSpeed() : ArducomCommand(ARDUCOM_CMD_SET_SPEED, 1) {}   // this command expects one parameter
  
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
  ArducomSetGlobalBrightness() : ArducomCommand(ARDUCOM_CMD_SET_GLOBAL_BRIGHTNESS, 1) {}   // this command expects one parameter
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    global_brightness = dataBuffer[0];
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command enables a channel.
class ArducomEnableChannel : public ArducomCommand {
public:
  ArducomEnableChannel() : ArducomCommand(ARDUCOM_CMD_ENABLE_CHANNEL, 1) {}   // this command expects one parameter
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
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
  ArducomDisableChannel() : ArducomCommand(ARDUCOM_CMD_DISABLE_CHANNEL, 1) {}   // this command expects one parameter
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
    }
    channel_buffers[channelNo].enabled = 0;
    // modify channel directly
    channels[channelNo].enabled = 0;
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the offset (lowest brightness) of a channel.
class ArducomSetOffset: public ArducomCommand {
public:
  ArducomSetOffset() : ArducomCommand(ARDUCOM_CMD_SET_OFFSET, 2) {}   // this command expects two parameters
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
    }
    // modify channel directly
    channels[channelNo].offset = dataBuffer[1];
    channel_buffers[channelNo].offset = dataBuffer[1];
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the brightness of a channel.
class ArducomSetBrightness: public ArducomCommand {
public:
  ArducomSetBrightness() : ArducomCommand(ARDUCOM_CMD_SET_BRIGHTNESS, 2) {}   // this command expects two parameters
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
    }
    // modify channel directly
    channels[channelNo].brightness = dataBuffer[1];
    channel_buffers[channelNo].brightness = dataBuffer[1];
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the duty cycle of a channel.
class ArducomSetDutyCycle: public ArducomCommand {
public:
  ArducomSetDutyCycle() : ArducomCommand(ARDUCOM_CMD_SET_DUTYCYCLE, 2) {}   // this command expects two parameters
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
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
    if (!fillTimerMap(&(timerMaps[i]), outputPins[i])) {
      Serial.print(F("Setup error: Pin not on timer: "));
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
  Serial.println(F(APP_NAME));
#endif

  fillTimerMaps();

  uint8_t code;
	// setup Arducom system
  addCommand(new ArducomVersionCommand(APP_NAME));
  addCommand(new ArducomGetConfig());
  addCommand(new ArducomDefineChannel());
  addCommand(new ArducomSetSpeed());
  addCommand(new ArducomSetGlobalBrightness());
  addCommand(new ArducomEnableChannel());
  addCommand(new ArducomDisableChannel());
  addCommand(new ArducomSetOffset());
  addCommand(new ArducomSetBrightness());
  addCommand(new ArducomSetDutyCycle());

#ifdef LUCINDA_DEBUG
  Serial.println(F("Setup complete."));
#endif

  noInterrupts();

  // test: initialize channel 0
  channel_buffers[0].period = WAVETABLE_SIZE;
  channel_buffers[0].enabled = 0;
  channel_buffers[0].dutycycle = 127;

#define TESTSPEED / 11
  for (int i = 1; i < LUCINDA_MAXCHANNELS; i++) {
    channel_buffers[i].period = WAVETABLE_SIZE TESTSPEED;
    channel_buffers[i].bitmask = 1 << (i - 1);
    channel_buffers[i].enabled = 1;
    channel_buffers[i].brightness = 127;
    channel_buffers[i].dutycycle = 127;
    channel_buffers[i].phaseshift = ((i - 1) * WAVETABLE_SIZE TESTSPEED / LUCINDA_MAXCHANNELS);
    channel_buffers[i].wavetable = &WAVE_SINE;
    channel_buffers[i].macrocycle_length = 16;
    channel_buffers[i].macrocycle_count = 3;
    channel_buffers[i].macrocycle_shift = i * 2;    
  } 

//    channel_buffers[1].enabled = 1;
//    channel_buffers[6].enabled = 1;

  // copy buffers to channels
  memcpy(channels, channel_buffers, sizeof(channel_t) * LUCINDA_MAXCHANNELS);

#ifdef LUCINDA_DEBUG
  Serial.println("Start debug");

  int i = 8;

  int j = 0;
  while (j++ < 20 * channels[i].period) {
      processChannel(i);
  }
#endif
/*  
  channels[2].period = WAVETABLE_SIZE * 2;
  channels[2].bitmask = 4;
  channels[2].enabled = 1;
  channels[2].brightness = 255;
  channels[2].dutycycle = 127;
  channels[2].phaseshift = WAVETABLE_SIZE;
*/

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
