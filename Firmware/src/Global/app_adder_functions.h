#pragma once

#include "../App/AppManager.h"

// Convencion de nombres: para una app registrada con ADD_APP(nombre) se
// esperan estas 4 funciones (definidas por ti en cualquier .cpp):
//
//     void app_nombre_init(void);
//     void app_nombre_run(void);
//     void app_nombre_deinit(void);
//     bool app_nombre_event(uint32_t event);

// 1) Enum con un id por app: app_<nombre>_id, mas app_total_count al final.
#define ADD_APP(name) app_##name##_id,
enum app_id_t {
    #include "app_adder_config.h"
    app_total_count,
};
#undef ADD_APP

// 2) Prototipos de las funciones de cada app.
#define ADD_APP(name)                  \
    void app_##name##_init(void);      \
    void app_##name##_run(void);       \
    void app_##name##_deinit(void);    \
    bool app_##name##_event(uint32_t event);
#include "app_adder_config.h"
#undef ADD_APP

// Tabla con las funciones de todas las apps (definida en el .cpp).
extern const app_t apps[app_total_count];
