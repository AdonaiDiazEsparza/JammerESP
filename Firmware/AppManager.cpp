#include "AppManager.h"

// Constructor of the AppManager class
AppManager_t::AppManager_t(void* context_user, app_t* app, uint32_t total_apps)
{
    this->context = context_user;
    this->apps = app;
    this->total_apps = total_apps;
    this->current_app = 0;
}


// Function to go to the next app
void AppManager_t::go_to_app(uint32_t app_number)
{

    if(app_number >= this->total_apps)
    {
        return;
    }

    this->next_app = app_number;
    this->stop_app = true;
}

// Function to loop the app manager
void AppManager_t::loop(void)
{

    // Function to start the app
    if(this->start_app)
    {
        
        if(this->apps[this->current_app].init != NULL)
        {
            this->apps[this->current_app].init();
            this->start_app = false;
            this->run_app = true;
        }
    }

    // Function to run the app
    if(this->run_app)
    {
        if(this->apps[this->current_app].run != NULL)
        {
            this->apps[this->current_app].run();
        }
    }

    // Function to stop the app
    if(this->stop_app)
    {

        if(this->apps[this->current_app].deinit != NULL)
        {
            this->apps[this->current_app].deinit();
            this->stop_app = false;
            this->start_app = true;
            this->current_app = this->next_app;
        }
    }
}