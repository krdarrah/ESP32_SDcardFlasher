
//HSPI MOSI=13, MISO=12, CLK=14, CS=25
//VSPI MOSI=23, MISO=19, CLK=18, CS=25

void clearSDfiles() {
  Serial.println("Looking for SD files");
  File root;
  root = SD.open("/");
  while (true) {

    File entry =  root.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    Serial.print("DELETING: ");
    Serial.println(entry.name());
    SD.remove(entry.name());
    entry.close();
  }
}


void initSDcard() {
  spiSD.begin(18, 19, 23, SD_CS_pin); //SCK,MISO,MOSI,SS
  while (!SD.begin( SD_CS_pin, spiSD ))
  {
    Serial.println("Card Mount Failed");
    digitalWrite(RED_pin, HIGH);
    delay(1000);
  }


  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    while (1) {
      digitalWrite(RED_pin, HIGH);
    }
  }
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  clearSDfiles();
}
