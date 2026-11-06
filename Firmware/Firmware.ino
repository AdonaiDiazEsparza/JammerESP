#include "RF24.h"
#include <SPI.h>
#include "esp_bt.h"
#include "esp_wifi.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "hardwarelib.h"
#include "menus.h"

// unsigned int flag = 0;   //HSPI// Flag variable to keep track of direction
// unsigned int flagv = 0;  //VSPI// Flag variable to keep track of direction

void one() {
  radio1.setChannel(random(80));
  radio.setChannel(random(80));
  delayMicroseconds(random(60));
}

void setup(){
  // Start Screen
  initHardware();

}

void loop(){
  
}
