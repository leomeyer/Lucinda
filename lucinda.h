#ifndef __LUCINDA_H
#define __LUCINDA_H

/*******************************************************
* Application-specific defines
*******************************************************/
#define WAVETABLE_SIZE  1024
#define MAX_PERIOD  (WAVETABLE_SIZE * 10)

#define CHANNELFLAG_NO_EYE_CORRECTION   1   // no not apply the eye correction table
#define CHANNELFLAG_INVERT              2   // invert the channel brightness
#define CHANNELFLAG_REVERSE             4   // when using a wave table, index from the end
#define CHANNELFLAG_APPLY               128   // when this flag is set all channel modifications of command DEFINE_CHANNEL are applied directly

#define CHANNELFLAG_ALL (CHANNELFLAG_NO_EYE_CORRECTION | CHANNELFLAG_INVERT | CHANNELFLAG_REVERSE)

// Defines the Arducom commands used for communicating with a Lucinda sketch

#define ARDUCOM_CMD_GET_CONFIG 1
#define ARDUCOM_CMD_DEFINE_CHANNEL 2
#define ARDUCOM_CMD_SET_GLOBAL_SPEED 3
#define ARDUCOM_CMD_SET_GLOBAL_BRIGHTNESS 4
#define ARDUCOM_CMD_ENABLE_CHANNEL 5
#define ARDUCOM_CMD_DISABLE_CHANNEL 6
#define ARDUCOM_CMD_SET_CHANNEL_PERIOD 7
#define ARDUCOM_CMD_SET_CHANNEL_PHASESHIFT 8
#define ARDUCOM_CMD_SET_CHANNEL_OFFSET 9
#define ARDUCOM_CMD_SET_CHANNEL_BRIGHTNESS 10
#define ARDUCOM_CMD_SET_CHANNEL_DUTYCYCLE 11

#ifdef ARDUINO
#include "Arduino.h"

#define DEVICE_NAME "Lucinda v2"

// definitions of internal flags
#define CHANNEL_IFLAG_COPY      1         // copying from the buffer is required at the end of a period
#define CHANNEL_IFLAG_ON_PHASE  2         // set while the channel is within a duty cycle "on" phase
#define CHANNEL_IFLAG_PHASE_CHANGE  4     // set when the duty cycle phase has changed from "on" to "off" or vice versa
#define CHANNEL_IFLAG_PHASE_OK      8     // set when the channel has entered the start of a duty cycle at least once
#define CHANNEL_IFLAG_IN_MACROCYCLE 16    // set while the channel is in an active macrocycle
#define CHANNEL_IFLAG_MACROCYCLE_CHANGE 32     // set when the channel enters or leaves an active macrocycle
#define CHANNEL_IFLAG_MACROCYCLE_OK     64     // set when the channel has entered the start of a macrocycle at least once

/*******************************************************
* Board-specific defines
*******************************************************/
#define LUCINDA_NUMLEDS 8
#define LUCINDA_MAXCHANNELS (LUCINDA_NUMLEDS + 1) // plus one for the halogen lamp

#if defined(__AVR_ATmega2560__)

#define PWM_TIMER_VECTOR    TIMER5_OVF_vect
#define PWM_TIMER_COUNTER   TCNT5
// The PWM timer must run at 1024 ticks per second.
#define PWM_TIMER_PRELOAD   (65536 - F_CPU / 64 / 1024)
#define PWM_TIMER_INIT      \
  TCCR5A = 0;               \
  TCCR5B = 0;               \
  PWM_TIMER_COUNTER = PWM_TIMER_PRELOAD;   \
  TCCR5B |= (1 << CS51) | (1 << CS50);  \
  TIMSK5 |= (1 << TOIE5);   // enable timer overflow interrupt

#else

#define PWM_TIMER_VECTOR    TIMER1_OVF_vect
#define PWM_TIMER_COUNTER   TCNT1
// The PWM timer must run at 1024 ticks per second.
#define PWM_TIMER_PRELOAD   (65536 - F_CPU / 64 / 1024)
#define PWM_TIMER_INIT      \
  TCCR1A = 0;               \
  TCCR1B = 0;               \
  PWM_TIMER_COUNTER = PWM_TIMER_PRELOAD;   \
  TCCR1B |= (1 << CS11) | (1 << CS10);  \
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt

#endif

/*******************************************************
* Types
*******************************************************/
typedef const uint8_t wavetable_t[WAVETABLE_SIZE];

// Defines a PWM channel. It can be mapped to multiple outputs.
typedef struct {
  // externally settable variables
  uint8_t enabled;
  uint8_t bitmask;
  uint16_t period;
  uint8_t offset;
  uint8_t brightness;
  uint8_t dutycycle;
  uint8_t phaseshiftPercent;
  uint16_t phaseshift;
  const wavetable_t* wavetable;
  uint8_t flags;
  uint8_t macrocycle_length;
  uint8_t macrocycle_count;
  uint8_t macrocycle_shift;

  // internal management
  uint16_t counter;
  uint8_t macrocycle_counter;
  uint8_t internal_flags;
} channel_t;

// Defines the relation of timer and OCR register and output mode.
typedef struct {
  uint16_t timerReg;
  uint8_t outputMode;
  uint16_t ocrReg;
} timermap_t;

/*******************************************************
* Forward Declarations
*******************************************************/

bool fillTimerMap(timermap_t* timerMap, uint8_t pin);

#endif // ARDUINO


#endif    // defined __LUCINDA_H
