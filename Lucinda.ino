// Lucinda v2
// by Leo Meyer <leo@leomeyer.de>

#include "lucinda.h"

#include <Arducom.h>

// #define LUCINDA_DEBUG 1

// for some reason this forward declaration is necessary
void addCommand(ArducomCommand* cmd);
//extern wavetable_t WAVE_SINE;     // defined in tables.cpp

/*******************************************************
* Data Structures
*******************************************************/

// Defines how the output pins map to PWM registers.
// This table is filled at setup from the information in outputPins.
timermap_t timerMaps[LUCINDA_MAXCHANNELS];

// Holds the PWM definition and counter for each channel.
channel_t channels[LUCINDA_MAXCHANNELS];

volatile uint8_t global_brightness = 255;
volatile uint8_t global_speed = 1;

/*******************************************************
* Constants
*******************************************************/

// Defines the pins of the connected lamps.
// The first pin is for the halogen lamp.
// The others are for the LEDs. If a lamp is not connected use 0.
#if defined(__AVR_ATmega2560__)
// the Mega supports more PWM pins
uint8_t outputPins[LUCINDA_MAXCHANNELS] = {11, 2, 3, 4, 5, 6, 7, 8, 9};
#else
// minimal test definitions for Uno etc.
uint8_t outputPins[LUCINDA_MAXCHANNELS] = {11, 3, 5, 6, 9, 10, 0, 0, 0};
#endif

// include constant table definitions
#include "tables.h"

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

ISR(PWM_TIMER_VECTOR)        // interrupt service routine 
{
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
    uint8_t val = 0;
    if (channels[i].enabled == 1 && channels[i].period > 0) {
      uint8_t val = channels[i].brightness;  // assume square
      // calculate end of cycle if the duty cycle is > 0
      if (channels[i].dutycycle > 0) {
        // calculate length of in-phase cycle
        int16_t phaseLength = ((uint32_t)channels[i].period * (channels[i].dutycycle + 1)) / 256;
        // apply phaseshift
        // phaseshift is guaranteed to be less or equal than the period
        int16_t phaseEnd = (channels[i].phaseshift + phaseLength) % (channels[i].period + 1);
        // correct for wrapover
        int16_t phaseStart = channels[i].phaseshift > phaseEnd ? (phaseEnd - phaseLength) : channels[i].phaseshift;
        // "on" phase?
        bool onPhase = ((int16_t)channels[i].counter >= phaseStart) && (channels[i].counter < phaseEnd);
        if (onPhase) {
          // "on" phase
          // non-square wave?
          if (channels[i].wavetable != nullptr) {
            // calculate the index in the wavetable
            uint16_t index = (int32_t)(channels[i].counter - phaseStart) * (WAVETABLE_SIZE - 1) / phaseLength;
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
          val = channels[i].offset;
        }
      } else {
        // duty cycle is 0, always at base level
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
      
      // set value to all controlled outputs
      setChannelValues(&(channels[i]), val);
  
      channels[i].counter += global_speed;
      if (channels[i].counter > channels[i].period)
        channels[i].counter = 0;
    }
  }  // for (channels)
}

/*******************************************************
* Arducom commands
*******************************************************/
#define ARDUCOM_COMMAND_GETCONFIG 1
#define ARDUCOM_COMMAND_DEFINECHANNEL 2
#define ARDUCOM_COMMAND_SETSPEED 3

// This command returns the configuration of the Lucinda setup.
class ArducomGetConfig: public ArducomCommand {
public:
  ArducomGetConfig(uint8_t commandCode) : ArducomCommand(commandCode, 0) {}   // this command expects zero parameters
  
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
// byte 10: wavetable to use (0: square, 1: sine, 2: triangle, 3: flicker, 4: linear/sawtooth)
// byte 11: flags that control additional behavior
// The channel is disabled and all pins are set to 0.
// After all values have been applied the channel is switched on again.
// If an error occurs the channel remains switched off.
class ArducomDefineChannel: public ArducomCommand {
public:
  ArducomDefineChannel(uint8_t commandCode) : ArducomCommand(commandCode, 12) {}   // number of expected parameter bytes
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
    }
    // disable channel during aplication
    channels[channelNo].enabled = 0;
    // reset counter
    channels[channelNo].counter = 0;
    // switch off all LEDs
    setChannelValues(&(channels[channelNo]), 0);
    channels[channelNo].bitmask = dataBuffer[2];
    channels[channelNo].period = dataBuffer[3] + dataBuffer[4] * 256;
    if (channels[channelNo].period > WAVETABLE_SIZE * 10) {
      *errorInfo = 3;
      return ARDUCOM_FUNCTION_ERROR;
    }
    channels[channelNo].offset = dataBuffer[5];
    channels[channelNo].brightness = dataBuffer[6];
    channels[channelNo].dutycycle = dataBuffer[7];
    channels[channelNo].phaseshift = (dataBuffer[8] + dataBuffer[9] * 256) % channels[channelNo].period;
    uint8_t wavetable = dataBuffer[10];
    switch (wavetable) {
      case 0: // square
        channels[channelNo].wavetable = nullptr;
        break;
      case 1: // sine
        channels[channelNo].wavetable = &WAVE_SINE;
        break;
      case 2: // triangle
        channels[channelNo].wavetable = &WAVE_TRIANGLE;
        break;
      case 3: // flicker
        channels[channelNo].wavetable = &WAVE_FLICKER;
        break;
      case 4: // linear (sawtooth)
        channels[channelNo].wavetable = &WAVE_LINEAR;
        break;
      default:  {
        *errorInfo = 10;
        return ARDUCOM_FUNCTION_ERROR;
      }
    }
    channels[channelNo].flags = dataBuffer[11] & CHANNELFLAG_ALL;
    channels[channelNo].enabled = dataBuffer[1] & 0x01; // the lowest bit decides
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the global speed of the channels in ticks. One tick corresponds to one millisecond.
class ArducomSetSpeed: public ArducomCommand {
public:
  ArducomSetSpeed(uint8_t commandCode) : ArducomCommand(commandCode, 1) {}   // this command expects one parameter
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    global_speed = dataBuffer[0];
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};


/*******************************************************
* Arducom system variables
*******************************************************/

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
  // setup pins
  // special treatment for halogen pin
  pinMode(outputPins[0], OUTPUT);
  analogWrite(outputPins[0], 255);
  for (int i = 1; i < LUCINDA_MAXCHANNELS; i++)
    if (outputPins[i] != 0) {
      pinMode(outputPins[i], OUTPUT);
      analogWrite(outputPins[i], 0);
    }
  
	// initialize hardware
	Serial.begin(57600);

#ifdef LUCINDA_DEBUG
  Serial.println(F(APP_NAME));
#endif

  fillTimerMaps();

  uint8_t code;
	// setup Arducom system
  addCommand(new ArducomVersionCommand(APP_NAME));
  addCommand(new ArducomGetConfig(ARDUCOM_COMMAND_GETCONFIG));
  addCommand(new ArducomDefineChannel(ARDUCOM_COMMAND_DEFINECHANNEL));
  addCommand(new ArducomSetSpeed(ARDUCOM_COMMAND_SETSPEED));

#ifdef LUCINDA_DEBUG
  Serial.println(F("Setup complete."));
#endif

  // test: initialize channel 0
  channels[0].period = WAVETABLE_SIZE;
  channels[0].enabled = 0;
  channels[0].dutycycle = 127;

  for (int i = 1; i < LUCINDA_MAXCHANNELS; i++) {
    channels[i].period = WAVETABLE_SIZE * 2;
    channels[i].bitmask = 1 << (i - 1);
    channels[i].enabled = 1;
    channels[i].brightness = 255;
    channels[i].dutycycle = 127;
    channels[i].phaseshift = i * WAVETABLE_SIZE / LUCINDA_MAXCHANNELS;
    channels[i].wavetable = &WAVE_SINE;
  } 

/*
    // debug
  channels[8].period = 0x800;
  channels[8].phaseshift = 0x500;
  channels[8].dutycycle = 0x2F;
  int i = 8;
  for (channels[8].counter = 0; channels[8].counter < channels[8].period; channels[8].counter += 10) {
      uint8_t val = channels[i].brightness;  // assume square
        // calculate length of in-phase cycle
        int16_t phaseLength = ((uint32_t)channels[i].period * (channels[i].dutycycle + 1)) / 256;
        Serial.print("phaseLength: " );
        Serial.println(phaseLength);
        // apply phaseshift
        // phaseshift is guaranteed to be less or equal than the period
        int16_t phaseEnd = (channels[i].phaseshift + phaseLength) % (channels[i].period + 1);
        Serial.print("phaseEnd: " );
        Serial.println(phaseEnd);
        // correct for wrapover
        int16_t phaseStart = channels[i].phaseshift > phaseEnd ? (phaseEnd - phaseLength) : channels[i].phaseshift;
        Serial.print("phaseStart: " );
        Serial.println(phaseStart);
        // "on" phase?
          Serial.print("counter: " );
          Serial.println(channels[i].counter);
        if ((((int16_t)channels[i].counter >= phaseStart) && (channels[i].counter < phaseEnd))) {
          // "on" phase
          // adjust brightness
          if (channels[i].brightness < 255) {
            val = ((uint16_t)val * channels[i].brightness) / 256;
          }
          // apply offset
          if (val < channels[i].offset)
            val = channels[i].offset;
        } else {
          // "off" phase
          val = channels[i].offset;
        }
        Serial.print("val: " );
        Serial.println(val);
  }
 */ 
/*  
  channels[2].period = WAVETABLE_SIZE * 2;
  channels[2].bitmask = 4;
  channels[2].enabled = 1;
  channels[2].brightness = 255;
  channels[2].dutycycle = 127;
  channels[2].phaseshift = WAVETABLE_SIZE;
*/
  noInterrupts();
  
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
