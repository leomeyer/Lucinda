

/*******************************************************
* Application-specific defines
*******************************************************/
#define APP_NAME "Lucinda v2"
#define WAVETABLE_SIZE  1024

/*******************************************************
* Board-specific defines
*******************************************************/
#define LUCINDA_NUMLEDS 8
#define LUCINDA_MAXCHANNELS (LUCINDA_NUMLEDS + 1) // one for the halogen lamp

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
* Arducom defines
*******************************************************/
#define ARDUCOM_COMMAND_GETCONFIG 1
#define ARDUCOM_COMMAND_DEFINECHANNEL 2


/*******************************************************
* Types
*******************************************************/
typedef uint8_t wavetable_t[WAVETABLE_SIZE];

// Defines a PWM channel. It can be mapped to multiple outputs.
typedef struct {
  uint8_t enabled;
  uint8_t bitmask;
  uint16_t period;
  uint16_t counter;
  uint8_t offset;
  uint8_t brightness;
  uint8_t dutycycle;
  uint16_t phaseshift;
  wavetable_t* wavetable;
} channel_t;

// Defines the relation of timer and OCR register and output mode.
typedef struct {
  uint16_t timerReg;
  uint8_t outputMode;
  uint16_t ocrReg;
} timermap_t;
