#include "hardwarelib.h"


SPIClass *sp = nullptr;
SPIClass *hp = nullptr;

RF24 radio(26, 27, 16000000);   //HSPI CAN SET SPI SPEED TO 16000000 BY DEFAULT ITS 10000000
RF24 radio1(22, 21, 16000000);  //VSPI CAN SET SPI SPEED TO 16000000 BY DEFAULT ITS 10000000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Button2 btn_up(PIN_BTN_UP);
Button2 btn_down(PIN_BTN_DOWN);
Button2 btn_left(PIN_BTN_LEFT);
Button2 btn_right(PIN_BTN_RIGHT);

int ch = 45;    // Variable to store value of ch
int ch1 = 45;   // Variable to store value of ch

static void initSP() {
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


/* Function to initilize the hardware */
void initHardware(void)
{

    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);

    while(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
        Serial.println("Oled Error, no connection");
        delay(1000);
    }

    initSP();
    initHP();

    display.clearDisplay();
    display.display();
}