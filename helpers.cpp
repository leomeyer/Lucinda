// Lucinda helper functions

#include "lucinda.h"

// Fills a timer map from the given pin.
// Code adapted from analogWrite.
// This code is theoretically compatible with processors other than the ATmega 2560.
bool fillTimerMap(timermap_t* timerMap, uint8_t pin) {

#define mapTimer(timer, com) timerMap->timerReg = (uint16_t)&(timer); timerMap->outputMode = com;

  switch(digitalPinToTimer(pin))
  {
    // XXX fix needed for atmega8
    #if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
    case TIMER0A:
      // connect pwm to pin on timer 0
      mapTimer(TCCR0, COM00);
      timerMap->ocrReg = (uint16_t)&OCR0;
      break;
    #endif

    #if defined(TCCR0A) && defined(COM0A1)
    case TIMER0A:
      // connect pwm to pin on timer 0, channel A
      mapTimer(TCCR0A, COM0A1);
      timerMap->ocrReg = (uint16_t)&OCR0A;
      break;
    #endif

    #if defined(TCCR0A) && defined(COM0B1)
    case TIMER0B:
      // connect pwm to pin on timer 0, channel B
      mapTimer(TCCR0A, COM0B1);
      timerMap->ocrReg = (uint16_t)&OCR0B;
      break;
    #endif

    #if defined(TCCR1A) && defined(COM1A1)
    case TIMER1A:
      // connect pwm to pin on timer 1, channel A
      mapTimer(TCCR1A, COM1A1);
      timerMap->ocrReg = (uint16_t)&OCR1A;
      break;
    #endif

    #if defined(TCCR1A) && defined(COM1B1)
    case TIMER1B:
      // connect pwm to pin on timer 1, channel B
      mapTimer(TCCR1A, COM1B1);
      timerMap->ocrReg = (uint16_t)&OCR1B;
      break;
    #endif

    #if defined(TCCR1A) && defined(COM1C1)
    case TIMER1C:
      // connect pwm to pin on timer 1, channel B
      mapTimer(TCCR1A, COM1C1);
      timerMap->ocrReg = (uint16_t)&OCR1C;
      break;
    #endif

    #if defined(TCCR2) && defined(COM21)
    case TIMER2:
      // connect pwm to pin on timer 2
      mapTimer(TCCR2, COM21);
      timerMap->ocrReg = (uint16_t)&OCR2;
      break;
    #endif

    #if defined(TCCR2A) && defined(COM2A1)
    case TIMER2A:
      // connect pwm to pin on timer 2, channel A
      mapTimer(TCCR2A, COM2A1);
      timerMap->ocrReg = (uint16_t)&OCR2A;
      break;
    #endif

    #if defined(TCCR2A) && defined(COM2B1)
    case TIMER2B:
      // connect pwm to pin on timer 2, channel B
      mapTimer(TCCR2A, COM2B1);
      timerMap->ocrReg = (uint16_t)&OCR2B;
      break;
    #endif

    #if defined(TCCR3A) && defined(COM3A1)
    case TIMER3A:
      // connect pwm to pin on timer 3, channel A
      mapTimer(TCCR3A, COM3A1);
      timerMap->ocrReg = (uint16_t)&OCR3A;
      break;
    #endif

    #if defined(TCCR3A) && defined(COM3B1)
    case TIMER3B:
      // connect pwm to pin on timer 3, channel B
      mapTimer(TCCR3A, COM3B1);
      timerMap->ocrReg = (uint16_t)&OCR3B;
      break;
    #endif

    #if defined(TCCR3A) && defined(COM3C1)
    case TIMER3C:
      // connect pwm to pin on timer 3, channel C
      mapTimer(TCCR3A, COM3C1);
      timerMap->ocrReg = (uint16_t)&OCR3C;
      break;
    #endif

    #if defined(TCCR4A)
    case TIMER4A:
      //connect pwm to pin on timer 4, channel A
      mapTimer(TCCR4A, COM4A1);
      #if defined(COM4A0)   // only used on 32U4
      // cbi(TCCR4A, COM4A0);
      #endif
      timerMap->ocrReg = (uint16_t)&OCR4A;
      break;
    #endif
    
    #if defined(TCCR4A) && defined(COM4B1)
    case TIMER4B:
      // connect pwm to pin on timer 4, channel B
      mapTimer(TCCR4A, COM4B1);
      timerMap->ocrReg = (uint16_t)&OCR4B;
      break;
    #endif

    #if defined(TCCR4A) && defined(COM4C1)
    case TIMER4C:
      // connect pwm to pin on timer 4, channel C
      mapTimer(TCCR4A, COM4C1);
      timerMap->ocrReg = (uint16_t)&OCR4C;
      break;
    #endif
      
    #if defined(TCCR4C) && defined(COM4D1)
    case TIMER4D:       
      // connect pwm to pin on timer 4, channel D
      mapTimer(TCCR4C, COM4D1);
      #if defined(COM4D0)   // only used on 32U4
      cbi(TCCR4C, COM4D0);
      #endif
      timerMap->ocrReg = (uint16_t)&OCR4D;
      break;
    #endif
            
    #if defined(TCCR5A) && defined(COM5A1)
    case TIMER5A:
      // connect pwm to pin on timer 5, channel A
      mapTimer(TCCR5A, COM5A1);
      timerMap->ocrReg = (uint16_t)&OCR5A;
      break;
    #endif

    #if defined(TCCR5A) && defined(COM5B1)
    case TIMER5B:
      // connect pwm to pin on timer 5, channel B
      mapTimer(TCCR5A, COM5B1);
      timerMap->ocrReg = (uint16_t)&OCR5B;
      break;
    #endif

    #if defined(TCCR5A) && defined(COM5C1)
    case TIMER5C:
      // connect pwm to pin on timer 5, channel C
      mapTimer(TCCR5A, COM5C1);
      timerMap->ocrReg = (uint16_t)&OCR5C;
      break;
    #endif

    case NOT_ON_TIMER:
      return false;
  }
  return true;
}
