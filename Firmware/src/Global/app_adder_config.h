// Lista de apps registradas.
//
// Para agregar una app nueva basta con una linea aqui:
//
//     ADD_APP(mi_app)
//
// y definir en algun .cpp sus 4 funciones:
//
//     void app_mi_app_init(void* context);
//     void app_mi_app_run(void* context);
//     void app_mi_app_deinit(void* context);
//     bool app_mi_app_event(void* context, uint32_t event);
//
// NO poner #pragma once ni include guard: este archivo se incluye varias
// veces a proposito (patron X-macro).

ADD_APP(main_menu)
ADD_APP(jammer_app)
ADD_APP(deauther_app)
ADD_APP(settings_app)
ADD_APP(credits_app)
