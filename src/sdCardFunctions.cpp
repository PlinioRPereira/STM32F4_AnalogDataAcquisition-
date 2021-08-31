#include "Definitions.h"
#include <STM32SD.h>
#include <Arduino.h>

extern Sd2Card sdCard;
extern SdFatFs fatFs;
extern File dataFile;

void initializeSDCard()
{
  //digitalWrite(yellowLed, HIGH);
  SerialUSB.print("Initializing SD card... ");
  bool disp = false;
  while (!sdCard.init(sdPresent_pin))
  {
    if (!disp)
    {
      SerialUSB.println("initialization failed. Is a card inserted?");
      disp = true;
    }
    delay(10);
  }
   while (!SD.begin(sdPresent_pin))
  {
    delay(10);
  }

  //digitalWrite(yellowLed, LOW);
  SerialUSB.println("SD card initialized.");
}

void printSDCardInfo()
{
  SerialUSB.println("\n*********** SD Card info ***********");
  SerialUSB.print("Card type: ");
  switch (sdCard.type()) {
    case SD_CARD_TYPE_SD1:
      SerialUSB.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      SerialUSB.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      SerialUSB.println("SDHC");
      break;
    default:
      SerialUSB.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!fatFs.init()) {
    SerialUSB.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }

  // print the type and size of the first FAT-type volume
  uint64_t volumesize;
  SerialUSB.print("\nVolume type is FAT");
  SerialUSB.println(fatFs.fatType(), DEC);
  SerialUSB.println();

  volumesize = fatFs.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= fatFs.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                        // SD card blocks are always 512 bytes
  SerialUSB.print("Volume size (bytes): ");
  SerialUSB.println(volumesize);
  SerialUSB.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  SerialUSB.println(volumesize);
  SerialUSB.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  SerialUSB.println(volumesize);


  SerialUSB.println("\nFiles found on the card (name, date and size in bytes): ");
  File root = SD.openRoot();

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();
  SerialUSB.println("###### End of the SD tests ######");
}

void uploadBinaryFile(const char* fileName)
{
  dataFile = SD.open(fileName);
  SerialUSB.print("File position: ");
  SerialUSB.println(dataFile.position());
  if (dataFile) {
    //digitalWrite(yellowLed, HIGH); 
    while (dataFile.available()) {
      SerialUSB.write(dataFile.read());      
    }
    dataFile.close();
    //digitalWrite(yellowLed, LOW);
    SerialUSB.println("Data upload finished successfuly");
  } else {
    SerialUSB.print("404. Error opening ");
    SerialUSB.print(fileName);
    SerialUSB.println(". File may not exist or SD card is not present");
    accessError();
  }
}

void accessError()
{
  for(int i=0; i<4; i++){
    digitalWrite(redLed, HIGH);
    delay(400);
    digitalWrite(redLed, LOW);
    delay(400);
  }
}


