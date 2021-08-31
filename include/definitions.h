#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include "Arduino.h"
#include <STM32SD.h>

#define Led                 PD1
#define redLed              PD1
#define Buzzer              PD8
#define Trimpot1            A0
#define Trimpot2            A1
#define Sensor0Ch           A2 
#define Sensor1Ch           A3
#define Button              PB13
#define DataLoggerRunning   PC7
#define sdPresent_pin       PA8

void respondToUsbCommand();
void timer1_isr(void);
void bip();
void blinkLed();

void printSDCardInfo();
void initializeSDCard();
void uploadBinaryFile(const char* fileName);
void accessError();

#endif