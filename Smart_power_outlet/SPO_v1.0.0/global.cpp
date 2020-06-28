#include "global.h"

void global::init()
{
  ext.init();
  //wifi.Setstation("milmar","70000000");
  //wifi.Setstation("Students","sedniuchi");
  wifi.Setstation("Teachers","1020304050");
  http.init(ext, wifi.ip);
}
