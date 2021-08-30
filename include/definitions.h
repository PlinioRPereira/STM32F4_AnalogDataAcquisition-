#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include "Arduino.h"

#define Led         PD1
#define Buzzer      PD8
#define Trimpot1    A0
#define Trimpot2    A1
#define Button      PB13
#define DataLoggerTrigger PC7

void respondToUsbCommand();
void timer1_isr(void);
void bip();

#endif