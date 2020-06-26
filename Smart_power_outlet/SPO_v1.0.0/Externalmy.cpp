#include "Externalmy.h"
Adafruit_SSD1306 d(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void Externalmy::init() {
  pinMode(LED, OUTPUT);
  pinMode(REL, OUTPUT);
  pinMode(BTN, INPUT);
  d.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  d.display();
}

void Externalmy::power(int val)
{
  //TO DO: Turn ON/OFF the led and relay using the private methods
  led(val);
  rel(val);
}

void Externalmy::loading()
{
  //TO DO: Display the loading screen
}

void Externalmy::dispText()
{
  //TO DO: Read the text from the EEPROM and display it
}

void Externalmy::scrollText()
{
  //TO DO: Read the text from the EEPROM and scroll it
}

void Externalmy::checkBTN()
{
  //TO DO: Check if the button is pressed or not
}

void Externalmy::led(int val)
{
  //TO DO: Turn on/off the led
  digitalWrite(LED,val);
  _led = val;
}

void Externalmy::rel(int val)
{
  //TO DO: Turn on/off the relay
  digitalWrite(REL,val);
  _rel = val;
}
