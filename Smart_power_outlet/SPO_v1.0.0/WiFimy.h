#ifndef WiFimy_h
#define WiFimy_h

#include <ESP8266WiFi.h>

class WiFimy {
  private:
    unsigned int previousWifiTime = 0;
  public:
    int wifiConnected = 1;
    String ip = "";
    String wifiName = "";

    void Setstation();
};
#endif
