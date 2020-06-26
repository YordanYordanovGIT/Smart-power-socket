#ifndef WiFimy_h
#define WiFimy_h

#include <ESP8266WiFi.h>

class WiFimy {
  private:
    unsigned int previousWifiTime = 0;
  public:
    int wifiConnected = 1;
    String ip = "";

    void Setstation(char* wifi_Name, char* wifi_Pass);
};
#endif
