#include "App/Device/hardwarelib.h"
#include "App/menus.h"

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
