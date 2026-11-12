#include "AppManager.h"

// Constructor of the AppManager class
AppManager_t::AppManager_t(void* context_user, const app_t* app, uint32_t total_apps)
{
    this->context = context_user;
    this->apps = app;
    this->total_apps = total_apps;
    this->current_app = 0;
    this->next_app = 0;
    this->start_app = true;   // Arranca la primera app al iniciar
    this->run_app = false;
    this->stop_app = false;
}

// Constructor of the AppManager class
AppManager_t::AppManager_t(void)
{
    this->context = NULL;
    this->apps = NULL;
    this->total_apps = 0;
    this->current_app = 0;
    this->next_app = 0;
}

// Function to set the manager
void AppManager_t::setManager(const app_t* app, uint32_t total_apps, void* context)
{
    this->apps = app;
    this->total_apps = total_apps;
    this->context = context;
}

// Function to set context
void AppManager_t::setContext(void* context)
{
    this->context = context;
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

// Function to event the app manager
bool AppManager_t::event(uint32_t event)
{
    if(this->apps[this->current_app].event != NULL)
    {
        return this->apps[this->current_app].event(this->context, event);
    }
    return false;
}


// Function to loop the app manager
void AppManager_t::loop(void)
{

    // Function to start the app
    if(this->start_app)
    {
        
        if(this->apps[this->current_app].init != NULL)
        {
            this->apps[this->current_app].init(this->context);   
            this->start_app = false;
            this->run_app = true;
        }
    }

    // Function to run the app
    if(this->run_app)
    {
        if(this->apps[this->current_app].run != NULL)
        {
            this->apps[this->current_app].run(this->context);
        }
    }

    // Function to stop the app
    if(this->stop_app)
    {

        if(this->apps[this->current_app].deinit != NULL)
        {
            this->apps[this->current_app].deinit(this->context);
            this->stop_app = false;
            this->start_app = true;
            this->current_app = this->next_app;
        }
    }
}