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

    app_context_t* app_context = (app_context_t*)context;
    AppManager_t* app_manager = (AppManager_t*)app_context->app_manager;

    switch(index) {
        case 0:
            Serial.println("Jammer");
            app_manager->go_to_app(app_jammer_menu_id);

            break;

        case 1:
            Serial.println("Bluetooth Spoofing");
            app_manager->go_to_app(app_bluetooth_spoofing_id);

            break;

        case 2:
            Serial.println("Deauther");
            app_manager->go_to_app(app_deauther_id);

            break;

        case 3:
            Serial.println("Credits");
            app_manager->go_to_app(app_credits_id);

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