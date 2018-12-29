// Lucinda helper functions

#include "lucinda.h"

// Fills a timer map from the given pin.
// Code adapted from analogWrite.
// This code is theoretically compatible with processors other than the ATmega 2560.
// However, all OCR registers must be 16 bit regiisters for 10 bit PWM, so certain pins cannot be used
// because their OCR registers are only 8 bit (e. g. OCR2A and OCR2B).
// Except: If canUse8Bit is true TIMER2 can also be used but it should only assigned to the halogen
// lamp because this one needs to run on a slower frequency anyway due to possible interference with USB.
// It is the responsibility of the caller to enforce this constraint.
bool fillTimerMap(timermap_t* timerMap, uint8_t pin, bool canUse8Bit) {

#define mapTimer(timer, com) timerMap->timerReg = (uint16_t)&(timer); timerMap->outputMode = com;

  timerMap->is8Bit = false;
  switch(digitalPinToTimer(pin))
  {
    // XXX fix needed for atmega8
    #if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
    case TIMER0A:
      // In theory this would be a valid 10 bit PWM capable timer but as its interrupt routine
      // is used to implement delay() and millis() and we need to adjust the PWM frequency
      // in order to achieve 10 bit resolution this timer cannot be used.
      return false;
/*      
      // connect pwm to pin on timer 0
      mapTimer(TCCR0, COM00);
      timerMap->ocrRegH = (uint16_t)&OCR0H;
      timerMap->ocrRegL = (uint16_t)&OCR0L;
*/      
      break;
    #endif
    #if defined(TCCR0A) && defined(COM0A1)
    case TIMER0A:
      return false;
/*      
      // connect pwm to pin on timer 0, channel A
      mapTimer(TCCR0A, COM0A1);
      timerMap->ocrRegH = (uint16_t)&OCR0AH;
      timerMap->ocrRegL = (uint16_t)&OCR0AL;
*/      
      break;
    #endif
    #if defined(TCCR0A) && defined(COM0B1)
    case TIMER0B:
      return false;
/*      
      // connect pwm to pin on timer 0, channel B
      mapTimer(TCCR0A, COM0B1);
      timerMap->ocrRegH = (uint16_t)&OCR0BH;
      timerMap->ocrRegL = (uint16_t)&OCR0BL;
*/      
      break;
    #endif

    #if defined(TCCR1A) && defined(COM1A1)
    case TIMER1A:
      // connect pwm to pin on timer 1, channel A
      mapTimer(TCCR1A, COM1A1);
      timerMap->ocrRegH = (uint16_t)&OCR1AH;
      timerMap->ocrRegL = (uint16_t)&OCR1AL;
      break;
    #endif

    #if defined(TCCR1A) && defined(COM1B1)
    case TIMER1B:
      // connect pwm to pin on timer 1, channel B
      mapTimer(TCCR1A, COM1B1);
      timerMap->ocrRegH = (uint16_t)&OCR1BH;
      timerMap->ocrRegL = (uint16_t)&OCR1BL;
      break;
    #endif

    #if defined(TCCR1A) && defined(COM1C1)
    case TIMER1C:
      // connect pwm to pin on timer 1, channel B
      mapTimer(TCCR1A, COM1C1);
      timerMap->ocrRegH = (uint16_t)&OCR1CH;
      timerMap->ocrRegL = (uint16_t)&OCR1CL;
      break;
    #endif

    #if defined(TCCR2) && defined(COM21)
    case TIMER2:
      // connect pwm to pin on timer 2
      mapTimer(TCCR2, COM21);
      timerMap->ocrRegH = (uint16_t)&OCR2H;
      timerMap->ocrRegL = (uint16_t)&OCR2L;
      break;
    #endif

    #if defined(TCCR2A) && defined(COM2A1)
    case TIMER2A:
      if (!canUse8Bit)
        return false;
      timerMap->is8Bit = true;
      // connect pwm to pin on timer 2, channel A
      mapTimer(TCCR2A, COM2A1);
      timerMap->ocrRegH = (uint16_t)&OCR2A;
      timerMap->ocrRegL = 0;
      break;
    #endif

    #if defined(TCCR2A) && defined(COM2B1)
    case TIMER2B:
      if (!canUse8Bit)
        return false;
      timerMap->is8Bit = true;
      // connect pwm to pin on timer 2, channel B
      mapTimer(TCCR2A, COM2B1);
      timerMap->ocrRegH = (uint16_t)&OCR2B;
      timerMap->ocrRegL = 0;
      break;
    #endif

    #if defined(TCCR3A) && defined(COM3A1)
    case TIMER3A:
      // connect pwm to pin on timer 3, channel A
      mapTimer(TCCR3A, COM3A1);
      timerMap->ocrRegH = (uint16_t)&OCR3AH;
      timerMap->ocrRegL = (uint16_t)&OCR3AL;
      break;
    #endif

    #if defined(TCCR3A) && defined(COM3B1)
    case TIMER3B:
      // connect pwm to pin on timer 3, channel B
      mapTimer(TCCR3A, COM3B1);
      timerMap->ocrRegH = (uint16_t)&OCR3BH;
      timerMap->ocrRegL = (uint16_t)&OCR3BL;
      break;
    #endif

    #if defined(TCCR3A) && defined(COM3C1)
    case TIMER3C:
      // connect pwm to pin on timer 3, channel C
      mapTimer(TCCR3A, COM3C1);
      timerMap->ocrRegH = (uint16_t)&OCR3CH;
      timerMap->ocrRegL = (uint16_t)&OCR3CL;
      break;
    #endif

    #if defined(TCCR4A)
    case TIMER4A:
      //connect pwm to pin on timer 4, channel A
      mapTimer(TCCR4A, COM4A1);
      #if defined(COM4A0)   // only used on 32U4
      // cbi(TCCR4A, COM4A0);
      #endif
      timerMap->ocrRegH = (uint16_t)&OCR4AH;
      timerMap->ocrRegL = (uint16_t)&OCR4AL;
      break;
    #endif
    
    #if defined(TCCR4A) && defined(COM4B1)
    case TIMER4B:
      // connect pwm to pin on timer 4, channel B
      mapTimer(TCCR4A, COM4B1);
      timerMap->ocrRegH = (uint16_t)&OCR4BH;
      timerMap->ocrRegL = (uint16_t)&OCR4BL;
      break;
    #endif

    #if defined(TCCR4A) && defined(COM4C1)
    case TIMER4C:
      // connect pwm to pin on timer 4, channel C
      mapTimer(TCCR4A, COM4C1);
      timerMap->ocrRegH = (uint16_t)&OCR4CH;
      timerMap->ocrRegL = (uint16_t)&OCR4CL;
      break;
    #endif
      
    #if defined(TCCR4C) && defined(COM4D1)
    case TIMER4D:       
      // connect pwm to pin on timer 4, channel D
      mapTimer(TCCR4C, COM4D1);
      #if defined(COM4D0)   // only used on 32U4
      cbi(TCCR4C, COM4D0);
      #endif
      timerMap->ocrRegH = (uint16_t)&OCR4DH;
      timerMap->ocrRegL = (uint16_t)&OCR4DL;
      break;
    #endif
            
    #if defined(TCCR5A) && defined(COM5A1)
    case TIMER5A:
      // connect pwm to pin on timer 5, channel A
      mapTimer(TCCR5A, COM5A1);
      timerMap->ocrRegH = (uint16_t)&OCR5AH;
      timerMap->ocrRegL = (uint16_t)&OCR5AL;
      break;
    #endif

    #if defined(TCCR5A) && defined(COM5B1)
    case TIMER5B:
      // connect pwm to pin on timer 5, channel B
      mapTimer(TCCR5A, COM5B1);
      timerMap->ocrRegH = (uint16_t)&OCR5BH;
      timerMap->ocrRegL = (uint16_t)&OCR5BL;
      break;
    #endif

    #if defined(TCCR5A) && defined(COM5C1)
    case TIMER5C:
      // connect pwm to pin on timer 5, channel C
      mapTimer(TCCR5A, COM5C1);
      timerMap->ocrRegH = (uint16_t)&OCR5CH;
      timerMap->ocrRegL = (uint16_t)&OCR5CL;
      break;
    #endif

    case NOT_ON_TIMER:
      return false;
  }
  return true;
}
