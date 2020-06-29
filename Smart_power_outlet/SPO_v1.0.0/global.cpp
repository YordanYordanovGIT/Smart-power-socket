#include "global.h"

void global::init()
{
  ext.init();
  //wifi.Setstation("milmar","70000000");
  //wifi.Setstation("Students","sedniuchi");
  wifi.Setstation("Redmi","70000000");
  http.init(ext, wifi.ip);
}
