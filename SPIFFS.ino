
//most of this from SPIFFS test example

void copyfromSPIFSS(fs::FS &fs, const char * dirname, uint8_t levels) {
  if (!SPIFFS.begin(false)) {
    Serial.println("SPIFFS FAILED");
    while (1) {}
  }

  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    Serial.print("  FILE: ");
    Serial.print(file.name());
    Serial.print("\tSIZE: ");
    Serial.println(file.size());
    File newSDFIle = SD.open(file.name(), FILE_WRITE);
    if (newSDFIle) {
      File FSfile = fs.open(file.name());
      if (FSfile) {
        digitalWrite(YELLOW_pin, HIGH);
        while (FSfile.available()) {
          newSDFIle.write(FSfile.read());
        }
        digitalWrite(YELLOW_pin, LOW);
        Serial.print("DONE WRITING ");
        Serial.println(file.name());
        FSfile.close();
        newSDFIle.close();
      } else {
        digitalWrite(RED_pin, HIGH);
        Serial.print("error FS file ");
        Serial.println(file.name());
        while (1) {}
      }
    } else {
      digitalWrite(RED_pin, HIGH);
      Serial.print("error SD file ");
      Serial.println(file.name());
      while (1) {}
    }
    file = root.openNextFile();
  }
}

//  void readFile(fs::FS & fs, const char * path) {
//    Serial.printf("Reading file: %s\r\n", path);
//
//    File file = fs.open(path);
//    if (!file || file.isDirectory()) {
//      Serial.println("- failed to open file for reading");
//      return;
//    }
//
//    Serial.println("- read from file:");
//    while (file.available()) {
//      Serial.write(file.read());
//    }
//    file.close();
//  }
