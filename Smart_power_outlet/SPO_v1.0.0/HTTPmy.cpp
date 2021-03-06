#include "HTTPmy.h"

unsigned long currentTime = millis();
const long timeoutTime = 5000;
bool refresh;

String blue =  "#0d68bf";
String grey =  "#7e8187";
String white = "#ffffff";
String black = "#000000";

WiFiServer server(80);

void HTTPmy::init(Externalmy* external, EEPROMmy* _mem, String _ip)
{
  ext = external;
  ip = _ip;
  mem = _mem;
  server.begin();
}

void HTTPmy::update()
{
  unsigned long previousTime = 0;
  String header;
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,    
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            ext->scrollAllowed(0); // Forbid text scrolling animation
            
            if(header.indexOf("GET /set?OFF=") != -1)
            {
              refresh = true;
              ext->power(0);
              //Turn off
            }
            else if(header.indexOf("GET /set?ON=") != -1)
            {
              refresh = true;
              ext->power(1);
              //Turn on
            }
            else if(header.indexOf("GET /set?textarea=") != -1)
            {
              refresh = true;
              int charTxt = header.indexOf("GET /set?textarea=");
              int charTxtEnd = header.indexOf("HTTP/1.1");
              String txt = header.substring(charTxt + 18, charTxtEnd - 1);
              txt = UrlDecode(txt);
              mem->saveToMem(txt);
              //ext->dispText(txt, 0, 0, 1, 0);
            }
            else
            {
              refresh = false;
            }

            //========================================================================================
            // Display the HTML web page

            pageIndex(client, refresh);

            //========================================================================================
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    
    ext->scrollAllowed(1); // Allow text scrolling animation
    
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void HTTPmy::pageIndex(WiFiClient client, bool refresh)
{
  String request = "";
  request += "<!DOCTYPE html><html><head>";
  request += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  if(refresh)
    request += "<meta http-equiv=\"refresh\" content=\"0.5;URL=http://" + ip + "\"/>";
  request += "<style>";
  request += "html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  request += ".btnSet { background-color: " + blue + "; border: none; color: " + white + "; padding: 10px 40px;";
  request += "text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}";
  if(ext->_power == 1)
    request += ".button { background-color:" + blue + "; border: none; color:" + white + "; padding: 10px 40px;";
  else
    request += ".button { background-color: " + grey + "; border: none; color: " + black + "; padding: 10px 40px;";
  request += "text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}";
  request += ".centered { vertical-align: middle; margin-right: 50px; }.displayText { vertical-align: middle; resize: none;}</style></head> ";    
  request += "<body style=\"background-color:#F4F6F6;\"><h1 style=\"color:#c47724;\">Smart power socket</h1>";
  request += "<form action=\"/set\" method=\"get\"><img src=\"https://image.flaticon.com/icons/svg/2922/2922379.svg\" alt=\"Socket image\" class=\"centered\" width=\"120\" height=\"120\">";
  if(ext->_power == 1)
    request += "<button type=\"submit\" name=\"OFF\" class=\"button\">ON</button><br><br></form><form action=\"/set\" method=\"get\">";
  else
    request += "<button type=\"submit\" name=\"ON\" class=\"button\">OFF</button><br><br></form><form action=\"/set\" method=\"get\">";
  request += "<textarea name=\"textarea\" class=\"displayText\" style=\"width:250px;height:150px;\">" + mem->text +"</textarea>";
  request += "<button type=\"submit\" class=\"btnSet\">Set</button></form></body></html>";
  client.println(request);
}

String HTTPmy::UrlDecode(String str)
{
    
    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++){
        c=str.charAt(i);
      if (c == '+'){
        encodedString+=' ';  
      }else if (c == '%') {
        i++;
        code0=str.charAt(i);
        i++;
        code1=str.charAt(i);
        c = (h2int(code0) << 4) | h2int(code1);
        encodedString+=c;
      } else{
        
        encodedString+=c;  
      }
      
      yield();
    }
    
   return encodedString;
}

unsigned char HTTPmy::h2int(char c)
{
    if (c >= '0' && c <='9'){
        return((unsigned char)c - '0');
    }
    if (c >= 'a' && c <='f'){
        return((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <='F'){
        return((unsigned char)c - 'A' + 10);
    }
    return(0);
}
