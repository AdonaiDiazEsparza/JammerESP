#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "RF24.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Button2.h>

#define SDA_PIN 5
#define SCL_PIN 4

#define SCREEN_ADDRESS 0x3C

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1

#define PIN_BTN_UP    32
#define PIN_BTN_DOWN  25
#define PIN_BTN_LEFT  33
#define PIN_BTN_RIGHT 2

extern Adafruit_SSD1306 display;
extern Button2 btn_up;
extern Button2 btn_down;
extern Button2 btn_left;
extern Button2 btn_right;

extern RF24 radio;
extern RF24 radio1;


void initHardware(void);