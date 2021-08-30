#include "Arduino.h"
#include "USBSerial.h"
#include "definitions.h"

#define timer1Period 22 //22 for Sample rate = 44.100 Hz

int count = 0;
uint8_t ledBit = HIGH;
uint8_t buffer[10];
HardwareTimer timer1(TIM1);

uint16_t n = 0;
float fi;

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(DataLoggerTrigger, OUTPUT);

  SerialUSB.begin(115200);

  timer1.setMode(1, TIMER_OUTPUT_COMPARE);
  timer1.setOverflow(timer1Period, MICROSEC_FORMAT);
  timer1.attachInterrupt(1, timer1_isr);
  timer1.resumeChannel(1);

  SerialUSB.println("Inicializado!");

  bip();  

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
  }
}

void bip(){
  digitalWrite(Buzzer, HIGH); 
  delay(100);
  digitalWrite(Buzzer, LOW); 
}


