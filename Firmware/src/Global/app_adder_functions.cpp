#include "app_adder_functions.h"

// 3) Construye la tabla apps[] a partir de la misma lista.
//    Cada entrada apunta a las funciones app_<nombre>_init/run/deinit/event.
#define ADD_APP(name) { app_##name##_init, app_##name##_run, app_##name##_deinit, app_##name##_event },
const app_t apps[app_total_count] = {
    #include "app_adder_config.h"
};
#undef ADD_APP
