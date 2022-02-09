/*
 * This code copies files from internal SPIFFS memory on the ESP32 to an SD Card, 
 *  - First deletes everything on the card
 *  - reads SPIFFS root, and copies files one by one
 *  - reset the ESP32 for the next card 
 *
 *  Sketch Data Upload Tool: https://github.com/me-no-dev/arduino-esp32fs-plugin/releases
 *  
 *  Kevin Darrah
 *  2022
 *  https://www.kdcircuits.com
 */



#include "FS.h"
#include "SPIFFS.h"
#include <SPI.h>
#include "SD.h"
const int SD_CS_pin = 25;

const int RED_pin = 22;
const int GREEN_pin = 32;
const int YELLOW_pin = 33;

SPIClass spiSD(VSPI);

void initSDcard();
void copyfromSPIFSS(fs::FS &fs, const char * dirname, uint8_t levels);
void clearSDfiles();

void setup() {
  pinMode(RED_pin, OUTPUT);
  pinMode(GREEN_pin, OUTPUT);
  pinMode(YELLOW_pin, OUTPUT);

  digitalWrite(YELLOW_pin, HIGH);
  Serial.begin(115200);
  delay(2000);
  //  redLED(true);
  initSDcard();
  unsigned long startTime = millis();
  copyfromSPIFSS(SPIFFS, "/", 0);
  Serial.print("Time to Write: ");
  Serial.print((millis() - startTime) / 1000);
  Serial.println("sec");
  Serial.print("EVERYTHING DONE!!!");
  digitalWrite(YELLOW_pin, LOW);
  digitalWrite(RED_pin, LOW);
}

void loop() {
  digitalWrite(GREEN_pin, HIGH);
  delay(100);
  digitalWrite(GREEN_pin, LOW);
  delay(100);
}
