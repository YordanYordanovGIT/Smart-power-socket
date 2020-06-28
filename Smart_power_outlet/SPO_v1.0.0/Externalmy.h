#ifndef Externalmy_h
#define Externalmy_h

#include <Adafruit_SSD1306.h>

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
    int _btn = 0;
    static Externalmy * instance;
    
    void led(int val);
    void rel(int val);

    void attachTheInterrupt() {
      attachInterrupt(digitalPinToInterrupt(BTN), btnFuncStat, FALLING);
    }

    static void btnFuncStat() {
      instance->checkBTN();
    }
  public:
    int _power;

    void init();
    void power(int val);
    void loading();
    void dispText();
    void checkBTN();
    void scrollText();
    void test(String txt);
};
#endif
