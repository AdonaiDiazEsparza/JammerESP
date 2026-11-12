#pragma once

#include "Global/app_adder_functions.h"
#include "Global/hardwarelib.h"
#include "App/menus.h"


typedef struct {
    AppManager_t* app_manager;
    Menus_t* menus;
} app_context_t;