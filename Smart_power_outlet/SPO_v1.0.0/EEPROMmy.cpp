#include "EEPROMmy.h"

void EEPROMmy::init() {
  EEPROM.begin(4096);
  //erase(); //used for servicе purposes
  readMem();
}

void EEPROMmy::readMem() {
  for (int i = 0; i < 4096; i++) {
    byte b = EEPROM.read(i);
    if (b == 0)
      break;
    else {
      if ((char)b == '\n')
        textNoNL += ' ';
      else
        textNoNL += (char)b;
      text += (char)b;
    }
  }
}

void EEPROMmy::saveToMem(String txt) {
  text = "";
  textNoNL = "";
  clear();
  for (int i = 0; i < txt.length(); i++) {
    if (i == 4096)
      break;
    char ch = txt[i];
      
    EEPROM.write(i, (byte)ch);
    text += ch;
    if (ch == '\n')
      textNoNL += ' ';
    else
      textNoNL += ch;
  }
  EEPROM.commit();
}

void EEPROMmy::erase() {
  for (int adress = 0; adress < 4096; adress++)
    EEPROM.write(adress, 0);
  EEPROM.commit();
}

void EEPROMmy::clear() {
  for (int i = 0; i < 4096; i++) {
    if (EEPROM.read(i) == 0)
      break;
    else
      EEPROM.write(i, 0);
  }
  EEPROM.commit();
}
