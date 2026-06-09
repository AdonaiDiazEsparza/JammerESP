
#include "RF24.h"
#include <SPI.h>
#include "esp_bt.h"
#include "esp_wifi.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
  This code is taken from the following repository
*/

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 

#define SDA_PIN 5
#define SCL_PIN 4

SPIClass *sp = nullptr;
SPIClass *hp = nullptr;

RF24 radio(26, 27, 16000000);   //HSPI CAN SET SPI SPEED TO 16000000 BY DEFAULT ITS 10000000
RF24 radio1(22, 21, 16000000);  //VSPI CAN SET SPI SPEED TO 16000000 BY DEFAULT ITS 10000000

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//HSPI= SCK = 14, MISO = 12, MOSI = 13, CS = 27 , CE = 26

//VSPI= SCK = 18, MISO = 19, MOSI = 23 ,CS =21 ,CE = 22
// SDA= 5  SCL= 4

unsigned int flag = 0;   //HSPI// Flag variable to keep track of direction
unsigned int flagv = 0;  //VSPI// Flag variable to keep track of direction
int ch = 45;    // Variable to store value of ch
int ch1 = 45;   // Variable to store value of ch

char middle_button = 33;
char right_button = 17;
char left_button = 25;

bool attacking = false;

// For the oled
bool clear_display = false;

char show_activated[] = "Activated";
char show_deactivated[] = "Deactivated";

char* message = NULL;


void initSP() {
  sp = new SPIClass(VSPI);
  sp->begin();
  if (radio1.begin(sp)) {
    Serial.println("SP Started !!!");
    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setPALevel(RF24_PA_MAX, true);
    radio1.setDataRate(RF24_2MBPS);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.printPrettyDetails();
    radio1.startConstCarrier(RF24_PA_MAX, ch1);
  } else {
    Serial.println("SP couldn't start !!!");
  }
}

// Function to set the 
void initHP() {
  hp = new SPIClass(HSPI);
  hp->begin();
  if (radio.begin(hp)) {
    Serial.println("HP Started !!!");
    radio.setAutoAck(false);
    radio.stopListening();
    radio.setRetries(0, 0);
    radio.setPALevel(RF24_PA_MAX, true);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.printPrettyDetails();
    radio.startConstCarrier(RF24_PA_MAX, ch);
  } else {
    Serial.println("HP couldn't start !!!");
  }
}

void one() {
  radio1.setChannel(random(80));
  radio.setChannel(random(80));
  delayMicroseconds(random(60));
}

void attack(){

}

void draw_menu(){

}

void setup(){
  // Start Screen
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  while(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.println("Oled Error, no connection");
    delay(1000);
  }

  // Init Radios
  initSP();
  initHP();

  // Buttom
  pinMode(middle_button, INPUT_PULLUP);

  // Set color
  display.setTextColor(SSD1306_WHITE);

  // Clear the oled
  display.clearDisplay();
  display.display();
}

void loop(){

  // When the button is pressed starts the jamming
  if(!digitalRead(middle_button))
  {
    while(!digitalRead(middle_button));

    attacking = !attacking;

    clear_display = true;
    
    if(attacking)
      message = show_activated;
    else
      message = show_deactivated;

  }


  if(attacking)
  {
    one();
  }

  if(clear_display)
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println(F(message));
    display.display();
    clear_display = false;
  }

}
