#ifndef global_h
#define global_h

#include "WiFimy.h"
#include "Externalmy.h"
#include "HTTPmy.h"
#include "MQTTmy.h"

class global {
  private:
  public:
    WiFimy wifi;
    HTTPmy http;
    Externalmy ext;
    MQTTmy mqtt;
    
    void init();
};
#endif
