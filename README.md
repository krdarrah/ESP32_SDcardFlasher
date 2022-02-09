# ESP32_SDcardFlasher


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
 
