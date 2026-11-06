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
        AppManager_t(void* context_user, app_t* app, uint32_t total_apps);
        void loop(void);
        bool event(uint32_t event);
        void go_to_app(uint32_t app_number);

    private:
        void* context;
        app_t* apps;
        uint32_t total_apps;
        uint32_t next_app;
        uint32_t current_app;

        bool start_app; // Flag to know if the app should be started
        bool stop_app; // Flag to know if the app should be stopped
        bool run_app; // Flag to know if the app should be run
}; 