#pragma once

#include "Arduino.h"


// Functions prototypes for the apps
typedef void (*app_init_t)(void);
typedef void (*app_run_t)(void);
typedef void (*app_deinit_t)(void);
typedef bool (*app_event_t)(uint32_t event);


// Struct to save the functions for apps
typedef struct {
    app_init_t init;
    app_run_t run;
    app_deinit_t deinit;
    app_event_t event;
} app_t;


// Class to manage 
class AppManager_t {
    public:
        void init(void* context_user, app_t* app, uint32_t total_apps);
        void run(void);
        bool event(uint32_t event);

        void next_app(void);
        void previous_app(void);

        void set_app(uint32_t index);

    private:
        void* context;
        app_t* apps;
        uint32_t total_apps;

}; 