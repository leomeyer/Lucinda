

#define APP_NAME "Lucinda v2"

#define ARDUCOM_COMMAND_GETCONFIG 1
#define ARDUCOM_COMMAND_DEFINECHANNEL 2

#define LUCINDA_NUMLEDS 8
#define LUCINDA_MAXCHANNELS (LUCINDA_NUMLEDS + 1) // one for the halogen lamp

/*******************************************************
* Types
*******************************************************/
// Defines a PWM channel. It can be mapped to multiple outputs.
typedef struct {
  uint8_t enabled;
  uint8_t bitmask;
  uint16_t period;
  uint16_t counter;
  uint8_t offset;
  uint8_t brightness;
  uint16_t phaseshift;
} channel_t;

// Defines the relation of timer and OCR register and output mode.
typedef struct {
  uint16_t timerReg;
  uint8_t outputMode;
  uint16_t ocrReg;
} timermap_t;
