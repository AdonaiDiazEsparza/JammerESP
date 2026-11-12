#include "../App.h"

/*
 Menu of the jammer app
*/

const char* jammer_menu_items[] = {
    "Attack",
    "Test Radios"
};

uint8_t jammer_menu_items_count = sizeof(jammer_menu_items) / sizeof(jammer_menu_items[0]);

void jammer_menu_callback(void* context, uint32_t index) {
    app_context_t* app_context = (app_context_t*)context;
    AppManager_t* app_manager = (AppManager_t*)app_context->app_manager;
    
    switch(index) {
        case 0:
            app_manager->go_to_app(app_jammer_attacker_id);
            break;

        case 1:
            app_manager->go_to_app(app_test_radios_id);
            break;
    }

}

// Return to main menu
void jammer_menu_callback_back(void* context){
    app_context_t* app_context = (app_context_t*)context;
    AppManager_t* app_manager = (AppManager_t*)app_context->app_manager;
    app_manager->go_to_app(app_main_menu_id);
}

bool app_jammer_menu_event(void* context, uint32_t event) {

}

void app_jammer_menu_init(void* context) {
    app_context_t* app_context = (app_context_t*)context;
    Menus_t* menus = (Menus_t*)app_context->menus;
    menus->setItems(jammer_menu_items, jammer_menu_items_count, jammer_menu_callback, jammer_menu_callback_back, app_context);
}

void app_jammer_menu_run(void* context) {
    app_context_t* app_context = (app_context_t*)context;
    Menus_t* menus = (Menus_t*)app_context->menus;
    menus->run();
}

void app_jammer_menu_deinit(void* context) {
    app_context_t* app_context = (app_context_t*)context;
    app_context->menus->reset();
}



/*
    Jammer attacker app
*/

bool app_jammer_attacker_event(void* context, uint32_t event) {

}

void app_jammer_attacker_init(void* context) {

}

void app_jammer_attacker_run(void* context) {

}

void app_jammer_attacker_deinit(void* context) {

}


/*
    Test radios app
*/

bool app_test_radios_event(void* context, uint32_t event) {

}

void app_test_radios_init(void* context) {

}

void app_test_radios_run(void* context) {

}

void app_test_radios_deinit(void* context) {

}