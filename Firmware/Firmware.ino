#include "src/App.h"

// unsigned int flag = 0;   //HSPI// Flag variable to keep track of direction
// unsigned int flagv = 0;  //VSPI// Flag variable to keep track of direction

void one() {
  radio1.setChannel(random(80));
  radio.setChannel(random(80));
  delayMicroseconds(random(60));
}

app_context_t app_context;

AppManager_t appManager(nullptr, apps, app_total_count);

Menus_t MenusManager(&display);

void setup(){
  // Start Screen
  initHardware();

  app_context.app_manager = &appManager;
  app_context.menus = &MenusManager;

  appManager.setContext(&app_context);
}

void loop(){
  appManager.loop();
}
