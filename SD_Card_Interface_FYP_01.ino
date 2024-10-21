#include "FS.h"
#include "SD.h"
#include "SPI.h"


//  Uncomment and set up if you want to use custom pins for the SPI communication
#define REASSIGN_PINS
int sck = 14;
int miso = 12;
int mosi = 13;
int cs = 27;

void appendFile(fs::FS &fs, const char *path, int message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  while (!file) 
  {
    Serial.println("Failed to open file for writing");
    delay(100);
  }
  file.print(message);
  file.close();
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial) 
  {
    delay(10);
  }

  #ifdef REASSIGN_PINS
    SPI.begin(sck, miso, mosi, cs);
    if (!SD.begin(cs)) 
    {
  #else
 
  if (!SD.begin()) 
  {
    #endif
    Serial.println("Card Mount Failed");
    delay(100);
  }
  uint8_t cardType = SD.cardType();

  while (cardType == CARD_NONE) 
  {
    Serial.println("No SD card attached");
    delay(100);
  }
  int a = 10;
  appendFile(SD, "/hello.txt", a);
  Serial.printf("Test Passed");
}

void loop() 
{

}