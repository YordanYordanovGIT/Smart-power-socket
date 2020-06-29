#include "Externalmy.h"
Adafruit_SSD1306 d(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastPressTime = 0;
const int btnTimeout = 200;

unsigned long stillModeStart = 0;
const int stillModeTime = 3000;
int stillModeEnabled = 0;

unsigned long stillAnimStart = 0;
const int stillAnimTime = 5000;
int stillAnimEnabled = 0;

//========== interrupt routine =============
static Externalmy * instance;
static void ICACHE_RAM_ATTR btnFuncStat() {
  instance->checkBTN();
}
//==========================================

void Externalmy::init(EEPROMmy* _mem) {
  instance = this;
  mem = _mem;
  pinMode(LED, OUTPUT); //Led
  pinMode(REL, OUTPUT); //Relay
  pinMode(BTN, INPUT);  //Button
  attachInterrupt(digitalPinToInterrupt(BTN), btnFuncStat, RISING);
  d.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  d.display();
}

void Externalmy::power(int val)
{
  //TO DO: Turn ON/OFF the led and relay using the private methods
  led(val);
  rel(val);
  _power = val;
}

void Externalmy::loading()
{
  //TO DO: Display the loading screen

}

void Externalmy::dispText(String txt, int x, int y, int size, int scrolling)
{
  //TO DO: Read the text from the EEPROM and display it
  d.clearDisplay();
  d.setTextColor(WHITE); // or BLACK);
  d.setTextWrap(!scrolling);
  d.setTextSize(size);
  d.setCursor(x, y);
  d.print(txt);
  d.display();
}

void Externalmy::update() {
  if (_scrollAllowed && !stillModeEnabled) {
    if (scrollRepsLeft == 0 && !stillAnimEnabled) {
      scrollRepsLeft = 5;
      stillAnimEnabled = 1;
      stillAnimStart = millis();
    }
    if (stillAnimEnabled) {
      if (millis() < stillAnimStart)
        stillAnimStart = millis() - (unsigned long)1 - (unsigned long)stillAnimTime;

      if (millis() - stillAnimStart < stillAnimTime) {
        dispText(mem->text, 0, 0, 1, 0);
      }
      else
        stillAnimEnabled = 0;
    }
    else
      scrollText();
  }
  else {
    if (millis() < stillModeStart)
      stillModeStart = millis() - (unsigned long)1 - (unsigned long)stillModeTime;

    if (millis() - stillModeStart < stillModeTime) {
      dispText(mem->text, 0, 0, 1, 0);
    }
    else {
      if (!_scrollAllowed)
        stillModeStart = millis();
      else
        stillModeEnabled = 0;
    }
  }
}

void Externalmy::scrollText()
{
  //TO DO: Read the text from the EEPROM and scroll it
  cursor -= 1;
  dispText(mem->textNoNL, cursor, 18, 2, 1);
  if (cursor == -127 - mem->text.length() * 11) {
    scrollRepsLeft -= 1;
    cursor = 128;
  }
}

void Externalmy::scrollAllowed(int a) {
  _scrollAllowed = a;
  if (a == 0) {
    stillModeEnabled = 1;
    cursor = 128;
    scrollRepsLeft = 5;
    update();
  }
}

void Externalmy::checkBTN()
{
  //TO DO: Check if the button is pressed or not
  if (millis() < lastPressTime)
    lastPressTime = millis() - (unsigned long)1 - (unsigned long)btnTimeout;

  if (millis() - lastPressTime > btnTimeout)
  {
    if (_power == 1)
      power(0);
    else
      power(1);
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
