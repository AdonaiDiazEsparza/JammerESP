#pragma once

#include <stdint.h>
#include <Adafruit_SSD1306.h>

// ---------------------------------------------------------------------------
// Button identifiers and events used by the menu navigation logic.
//
// These used to come from buttons_controller.h (ESP-IDF). In the Arduino
// version they are defined here and fed from menus.cpp using the Button2
// library.
// ---------------------------------------------------------------------------
enum {
    BUTTON_UP = 0,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
};

enum {
    BUTTON_PRESS_DOWN = 0,  // button pressed
    BUTTON_PRESS_UP,        // button released
};

// Prototype for the menu callback
typedef void (*menu_callback_t)(void* args, uint32_t index);

// Prototype menu
typedef struct {
    uint32_t index;
    uint32_t total_items;
    menu_callback_t callback;
    const char** items;
    void* args;
} menu_t;

typedef struct {
    uint16_t current_index_menu;
    uint16_t total_menus;
    uint16_t* menu_order;
    menu_t* menu_instances;
    void* args;
} menu_manager_t;

/**
 * @brief Initialize the menu manager
 *
 * @param args The arguments for the menu
 * @param menu_instances The array of menu instances
 * @param total_menus The total number of menus
 *
 * @return void
 */
void menu_manager_init(Adafruit_SSD1306* display, void* args, menu_t* menu_instances, uint16_t total_menus);

/**
 * @brief Go to the next menu
 *
 * @param id The id of the menu to go to
 *
 * @return void
 */
void menu__manager_next_menu(uint16_t id);

/*
 * @brief Show the menu
 *
 * @param void
 *
 * @return void
 */
void show_menu(void);

/**
 * @brief Set the items for the menu
 *
 * @param items The items for the menu
 * @param total_items The total number of items
 * @param callback The callback for the menu
 * @param args The arguments for the menu
 *
 * @return void
 */
void menu_set_items(const char** items, uint32_t total_items, menu_callback_t callback, void* args);

/**
 * @brief Set the selected item for the menu
 *
 * @param index The index of the selected item
 *
 * @return void
 */
void menu_set_selected_item(uint32_t index);

/**
 * @brief Clear the menu
 *
 * @param void
 *
 * @return void
 */
void clear_menu(void);

/**
 * @brief Disable the menu manager
 *
 * @param void
 *
 * @return void
 */
void menu_manager_disable(void);

/**
 * @brief Go to the last menu when the user disable the menu manager
 *
 * @param void
 *
 * @return void
 */
void menu_manager_enable(void);

/**
 * @brief Poll the Button2 instances and dispatch menu navigation events.
 *        Call this from loop() (Arduino).
 *
 * @param void
 *
 * @return void
 */
void menu_buttons_update(void);
