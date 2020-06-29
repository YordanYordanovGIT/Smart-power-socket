#include "Externalmy.h"
Adafruit_SSD1306 d(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastPressTime = 0;
const int btnTimeout = 200;

//========== interrupt routine =============
static Externalmy * instance;
static void ICACHE_RAM_ATTR btnFuncStat() {
  instance->checkBTN();
}
//==========================================

void Externalmy::init() {
  instance = this;
  pinMode(LED, OUTPUT); //Led
  pinMode(REL, OUTPUT); //Relay
  pinMode(BTN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN), btnFuncStat, RISING);
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
  if (millis() < lastPressTime)
    lastPressTime = millis() - (unsigned long)1 - (unsigned long)btnTimeout;

  if (millis() - lastPressTime > btnTimeout)
  {
    if (_power == 1) {
      power(0);
      _power = 0;
    }
    else {
      power(1);
      _power = 1;
    }
    lastPressTime = millis();
  }
}

void Externalmy::led(int val)
{
  //TO DO: Turn on/off the led
  digitalWrite(LED, val);
  _led = val;
}

void Externalmy::rel(int val)
{
  //TO DO: Turn on/off the relay
  digitalWrite(REL, val);
  _rel = val;
}

void Externalmy::test(String txt)
{
  d.clearDisplay();
  d.setTextColor(WHITE); // or BLACK);
  d.setTextSize(1);
  d.setCursor(0, 0);
  d.print(txt);
  d.display();
}
