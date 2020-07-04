#ifndef MQTTmy_h
#define MQTTmy_h
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "Externalmy.h"
#include "EEPROMmy.h"

class MQTTmy {
  private:
    Externalmy* ext;
    EEPROMmy* eep;
  public:
    void init(Externalmy* external, EEPROMmy* eeprom);
    void sub();
    void update();
    void callback (char* topic, unsigned char* payload, unsigned int lenght);
};
#endif
