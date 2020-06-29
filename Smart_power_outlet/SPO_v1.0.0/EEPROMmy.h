#ifndef EEPROMmy_h
#define EEPROMmy_h

#include <EEPROM.h>
#include <Arduino.h>

class EEPROMmy {
  private:
    void clear();
  public:
    String text = "";
    String textNoNL = "";

    void init();
    void readMem();
    void saveToMem(String txt);
    void erase();
};
#endif
