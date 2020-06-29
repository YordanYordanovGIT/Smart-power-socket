//Board => ESP8266
//LED => D5(14)
//BTN => D6(12)
//Relay => D7(13)

#include "global.h"
global g;

void setup() {
  Serial.begin(115200);
  g.init();
  g.ext.power(0);
  //g.ext.dispText(g.mem.text, 0, 0, 1);
}

void loop() {
  if(g.wifi.wifiConnected == 1)
    g.http.update();
  if(g.ext._scrollAllowed)
    g.ext.update();
}
