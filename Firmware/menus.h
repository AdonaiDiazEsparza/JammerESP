#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Button2.h>

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
typedef void (*menu_callback_back_t)(void* args);

/**
* New version of menu manager
*/

class Menu_t {
  public:
    MenuManager_t(Adafruit_SSD1306* display, uint16_t total_items, const char** items, menu_callback_t callback, menu_callback_back_t callback_back, void* context);
    void setButtons(Button2* btn_up, Button2* btn_down, Button2* btn_left, Button2* btn_right);
    void setSelectedItem(uint8_t item);
    void buttonsUpdate(void);
    void reset(void);

  private:
    void showMenu(void);
    void clearMenu(void);

    void drawMenuBox(uint8_t pos);
    void drawMenuItems(void);
    void drawMenu(void);

    void menuButtonCallback(uint8_t button, uint8_t event);
    void onButtonReleased(Button2& btn);

    Adafruit_SSD1306* display_oled;

    void* context;
    uint16_t total_items;
    uint16_t current_item;

    // By the moment for this library I will use only the buttons UP, DOWN, LEFT and RIGHT
    Button2* btn_up;
    Button2* btn_down;
    Button2* btn_left;
    Button2* btn_right;
};