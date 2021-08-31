#include "Arduino.h"
#include "Definitions.h"
#include "HardwareTimer.h"
#include "USBSerial.h"
#include <STM32SD.h>
//#include <STM32F4ADC.h>

#define timer1Period 1000 //10us for Sample rate = 100000 Hz

//global objects
uint8_t ledBit = HIGH;
uint8_t buffer[10];
File dataFile;
Sd2Card sdCard;
SdFatFs fatFs;

HardwareTimer timer1(TIM1);


void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(DataLoggerRunning, OUTPUT);

  SerialUSB.begin();

  timer1.setMode(1, TIMER_OUTPUT_COMPARE);
  timer1.setOverflow(timer1Period, MICROSEC_FORMAT);
  timer1.attachInterrupt(1, timer1_isr);
  timer1.resumeChannel(1);

  initializeSDCard();
  printSDCardInfo();
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    SerialUSB.print("Writing to test.txt...");
    dataFile.println("testing 1, 2, 3.");
    // close the file:
    dataFile.close();
    SerialUSB.println("done.");
  } else {
    // if the file didn't open, print an error:
    SerialUSB.println("error opening test.txt");
  }
  dataFile = SD.open("datalog2.txt", FILE_WRITE);

  SerialUSB.println("Ready!");

  bip();
  blinkLed();  

}

void loop() {
  if(SerialUSB.available()){
    respondToUsbCommand();
  }
  

  delay(100);

}
  
void respondToUsbCommand()
{
  char command = SerialUSB.read();

  switch(command){
    case '0':
      SerialUSB.println("The command received was 0");
    break;
    
    case 'r':
      uploadBinaryFile("datalog.bin");
    break;
  }
}

void bip(){
  digitalWrite(Buzzer, HIGH); 
  delay(100);
  digitalWrite(Buzzer, LOW); 
}

void blinkLed(){
  digitalWrite(Led, LOW);
	delay(500);
	digitalWrite(Led, HIGH);
}


