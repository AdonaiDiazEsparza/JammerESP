// Ejemplo de app. Se registra en src/Global/app_adder_config.h con:
//
//     ADD_APP(main_menu)
//
// Solo hay que definir estas 4 funciones; el enum y la tabla apps[]
// se generan solos.

#include "../../Global/hardwarelib.h"

void app_main_menu_init(void)
{
    // Se llama una vez al entrar a la app.
}

void app_main_menu_run(void)
{
    // Se llama en cada vuelta del loop mientras la app esta activa.
}

void app_main_menu_deinit(void)
{
    // Se llama una vez al salir de la app.
}

bool app_main_menu_event(uint32_t event)
{
    // Devuelve true si la app consume el evento.
    (void)event;
    return false;
}
