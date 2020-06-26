#ifndef HTTPmy_h
#define HTTPmy_h

#include "WiFimy.h"
#include "Externalmy.h"

class HTTPmy {
  private:
    String ip;
    Externalmy ext;
    void pageIndex(WiFiClient client, bool refresh);
  public:
    void init(Externalmy external, String _ip);
    void update();
};
#endif