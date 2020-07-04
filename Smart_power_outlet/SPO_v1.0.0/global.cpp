#include "global.h"

void global::init()
{
  mem.init();
  ext.init(&mem);
  ext.loading();
  //wifi.Setstation("milmar","70000000");
  //wifi.Setstation("Students","sedniuchi");
  //wifi.Setstation("Redmi","70000000");
  wifi.Setstation("Teachers", "1020304050");
  http.init(&ext, &mem, wifi.ip);
}
