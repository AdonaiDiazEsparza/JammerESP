// Lista de apps registradas.
//
// Para agregar una app nueva basta con una linea aqui:
//
//     ADD_APP(mi_app)
//
// y definir en algun .cpp sus 4 funciones:
//
//     void app_mi_app_init(void);
//     void app_mi_app_run(void);
//     void app_mi_app_deinit(void);
//     bool app_mi_app_event(uint32_t event);
//
// NO poner #pragma once ni include guard: este archivo se incluye varias
// veces a proposito (patron X-macro).

ADD_APP(main_menu)
