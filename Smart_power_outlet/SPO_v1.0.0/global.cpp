#include "global.h"

void global::init()
{
  mem.init();
  ext.init(&mem);
  ext.loading();
  wifi.Setstation();
  ext.wifi(wifi.wifiName, wifi.ip);
  mqtt.init(&ext, &mem);
  http.init(&ext, &mem, wifi.ip);
}
