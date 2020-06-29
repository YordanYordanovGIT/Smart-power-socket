#ifndef global_h
#define global_h

#include "WiFimy.h"
#include "Externalmy.h"
#include "HTTPmy.h"
#include "EEPROMmy.h"

class global {
  private:
  public:
    WiFimy wifi;
    HTTPmy http;
    Externalmy ext;
    EEPROMmy mem;
    
    void init();
};
#endif
