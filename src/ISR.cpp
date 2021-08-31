#include "definitions.h"
#include <STM32SD.h>

#define SetPE14Pin    GPIOE->BSRR = 0x00004000;   //PE14 = 1 
#define ClearPE14Pin  GPIOE->BSRR = 0x40000000;   //PE14 = 0   

extern File dataFile;

void timer1_isr(void)
{
    SetPE14Pin 
    uint16_t data0 = analogRead(Sensor0Ch);
    uint16_t data1 = analogRead(Sensor1Ch);
    dataFile.write((uint8_t*)data0, 2);
    dataFile.write((uint8_t*)data1, 2);
    ClearPE14Pin

}