#ifndef WiFimy_h
#define WiFimy_h

#include <ESP8266WiFi.h>

#define wifi_Name "TP-LINK_E42E"
#define wifi_Pass "70893519"

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
