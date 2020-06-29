#ifndef Externalmy_h
#define Externalmy_h

#include <Adafruit_SSD1306.h>
#include "EEPROMmy.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define LED 14
#define BTN 12
#define REL 13

class Externalmy {
  private:
    int _led = 0;
    int _rel = 0;
    int cursor = 128;
    int scrollRepsLeft = 5;
    EEPROMmy* mem;
    
    void led(int val);
    void rel(int val);
  public:
    int _power;
    int _scrollAllowed = 1;
    
    void init(EEPROMmy* _mem);
    void update();
    void power(int val);
    void loading();
    void dispText(String txt, int x, int y, int size, int scrolling);
    void scrollAllowed(int a);
    void checkBTN();
    void scrollText();
    void test(String txt);
};
#endif
