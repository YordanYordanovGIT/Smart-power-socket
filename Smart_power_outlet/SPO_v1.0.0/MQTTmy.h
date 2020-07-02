#ifndef MQTTmy_h
#define MQTTmy_h
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "Externalmy.h"

class MQTTmy {
  private:
    Externalmy ext;
  public:
    void init(Externalmy external);
    void cmdt();
    static void *callback (char* topic, unsigned char* payload, unsigned int lenght);
    

};
#endif
