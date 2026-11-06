#include "src/Global/hardwarelib.h"
#include "src/App/AppManager.h"
#include "src/App/menus.h"
#include "src/Global/app_adder_functions.h"

// unsigned int flag = 0;   //HSPI// Flag variable to keep track of direction
// unsigned int flagv = 0;  //VSPI// Flag variable to keep track of direction

void one() {
  radio1.setChannel(random(80));
  radio.setChannel(random(80));
  delayMicroseconds(random(60));
}

// Administrador de apps alimentado con la tabla generada por los X-macro.
AppManager_t appManager(nullptr, apps, app_total_count);

void setup(){
  // Start Screen
  initHardware();
}

void loop(){
  appManager.loop();
}
