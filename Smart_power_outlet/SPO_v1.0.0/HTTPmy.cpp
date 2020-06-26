#include "HTTPmy.h"

unsigned long currentTime = millis();
const long timeoutTime = 5000;
bool refresh;

WiFiServer server(80);

void HTTPmy::init(Externalmy external, String _ip)
{
  ext = external;
  ip = _ip;
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


            
            if(header.indexOf("GET /set?OFF=") != -1)
            {
              refresh = true;
              ext.power(0);
              //Turn off
            }
            else if(header.indexOf("GET /set?ON=") != -1)
            {
              refresh = true;
              //Turn on
            }
            else if(header.indexOf("GET /set?textarea=") != -1)
            {
              refresh = true;
              int charTxt = header.indexOf("GET /set?textarea=");
              int charTxtEnd = header.indexOf("HTTP/1.1");
              String txt = header.substring(charTxt + 18, charTxtEnd);
              Serial.println(UrlDecode(txt));
              ext.test(UrlDecode(txt));
            }
            else
            {
              refresh = false;
            }
            /*int charWifi = 0, charPass = 0;
            charWifi = header.indexOf("GET /set?wifi=");
            if ( charWifi >= 0) {
              charWifi += 14;
              pageNum = 1;
            }
            else
              pageNum = 0;


            charPass = header.indexOf("&pass=");
            wifiNum = header.substring(charWifi, charPass).toInt();
            wifiNum -= 1;

            charPass += 6;
            int endIndexPass = header.indexOf(" HTTP/1");
            pass = header.substring(charPass, endIndexPass);
            //Serial.println("<Wifi creds:" + String(wifiNum) + "#" + pass + ">");*/

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
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

/*void HTTPmy::update()
{
  //Serial.println("site");
  unsigned long previousTime = 0;
  String header;
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      yield();
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

            if(header.indexOf("GET /set?OFF=") != -1)
            {
              refresh = true;
              ext.power(0);
              //Turn off
            }
            else if(header.indexOf("GET /set?ON=") != -1)
            {
              refresh = true;
              //Turn on
            }
            else if(header.indexOf("GET /set?textarea=") != -1)
            {
              refresh = true;
              int charTxt = header.indexOf("GET /set?textarea=");
              int charTxtEnd = header.indexOf("HTTP/1.1");
              String txt = header.substring(charTxt + 18, charTxtEnd - charTxt - 18);
              Serial.println(UrlDecode(txt));
              ext.test(UrlDecode(txt));
            }
            else
            {
              refresh = false;
            }
            /*int charWifi = 0, charPass = 0;
            charWifi = header.indexOf("GET /set?wifi=");
            if ( charWifi >= 0) {
              charWifi += 14;
              pageNum = 1;
            }
            else
              pageNum = 0;


            charPass = header.indexOf("&pass=");
            wifiNum = header.substring(charWifi, charPass).toInt();
            wifiNum -= 1;

            charPass += 6;
            int endIndexPass = header.indexOf(" HTTP/1");
            pass = header.substring(charPass, endIndexPass);
            //Serial.println("<Wifi creds:" + String(wifiNum) + "#" + pass + ">");*/

 /*           //========================================================================================
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
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  yield();
} */

void HTTPmy::pageIndex(WiFiClient client, bool refresh)
{
  client.println("<!DOCTYPE html><html><head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  if(refresh)
    client.println("<meta http-equiv=\"refresh\" content=\"2;URL=http://" + ip + "\"/>");
  client.println("<style>");
  client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #0d68bf; border: none; color: #ffffff; padding: 10px 40px;");
  client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
  client.println(".centered { vertical-align: middle; margin-right: 50px; }.displayText { vertical-align: middle; resize: none;}</style></head> ");    
  client.println("<body style=\"background-color:#F4F6F6;\"><h1 style=\"color:#c47724;\">Smart power socket</h1>");
  client.println("<form action=\"/set\" method=\"get\"><img src=\"https://image.flaticon.com/icons/svg/2922/2922379.svg\" alt=\"Socket image\" class=\"centered\" width=\"120\" height=\"120\">");
  client.println("<button type=\"submit\" name=\"OFF\" class=\"button\">ON</button><br><br></form><form action=\"/set\" method=\"get\">");
  client.println("<textarea name=\"textarea\" class=\"displayText\" style=\"width:250px;height:150px;\">Pesho</textarea>");
  client.println("<button type=\"submit\" class=\"button\">Set</button></form></body></html>");
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
