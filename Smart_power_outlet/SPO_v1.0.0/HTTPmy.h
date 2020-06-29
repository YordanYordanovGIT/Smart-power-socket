#ifndef HTTPmy_h
#define HTTPmy_h

#include "WiFimy.h"
#include "Externalmy.h"
#include "EEPROMmy.h"

class HTTPmy {
  private:
    String ip;
    Externalmy* ext;
    EEPROMmy* mem;

    unsigned char h2int(char c);
    String UrlDecode(String input);
    void pageIndex(WiFiClient client, bool refresh);
  public:
    void init(Externalmy* external, EEPROMmy* _mem, String _ip);
    void update();
};
#endif
