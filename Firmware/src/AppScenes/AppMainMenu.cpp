#include "../App.h"


/*
* This is the cpp file that contain all the first main menu
* by the moment, it is set as the first view of the app
*
* It is used to navigate through the apps and to show the main menu
*/


const char* items[] = {
    "Jammer",
    "BlueSpoof",
    "Deauther",
    "Settings",
    "Credits"
};

void main_menu_callback(void* context, uint32_t index) {
    switch(index) {
        case 0:
            Serial.println("Jammer");
            break;
        case 1:
            Serial.println("BlueSpoof");
            break;
        case 2:
            Serial.println("Deauther");
            break;
        case 3:
            break;
        case 4:
            break;
    }
}


void app_main_menu_init(void* context) {
    app_context_t* app_context = (app_context_t*)context;

    app_context->menus->setButtons(&btn_up, &btn_down, &btn_left, &btn_right);

    app_context->menus->setItems(items, 5, main_menu_callback, NULL, context);

    app_context->menus->showMenu();
    
}

void app_main_menu_run(void* context) {
    app_context_t* app_context = (app_context_t*)context;
    app_context->menus->run();
}

void app_main_menu_deinit(void* context) {
    app_context_t* app_context = (app_context_t*)context;
    app_context->menus->reset();
}

bool app_main_menu_event(void* context, uint32_t event) {
    (void)event;
    return false;
}