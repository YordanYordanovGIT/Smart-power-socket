#ifndef global_h
#define global_h

#include "WiFimy.h"
#include "Externalmy.h"
#include "HTTPmy.h"
#include "EEPROMmy.h"
#include "MQTTmy.h"

//#define MQTT_ON

class global {
  private:
  public:
    WiFimy wifi;
    HTTPmy http;
    Externalmy ext;
    EEPROMmy mem;
    #ifdef MQTT_ON
    MQTTmy mqtt;
    #endif
    
    void init();
};
#endif
