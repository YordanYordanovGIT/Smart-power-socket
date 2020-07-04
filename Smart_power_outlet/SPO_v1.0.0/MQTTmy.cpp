#include "MQTTmy.h"

IPAddress ip (109, 121, 141, 188);
WiFiClient espClient;
PubSubClient mqttClient(espClient);
static MQTTmy * instance;
void MQTTmy::init(Externalmy external) {
  ext = external;
   mqttClient.setServer(ip, 1884);
  instance = this;

  if (mqttClient.connect("SmartSocketID"))
  {
    Serial.println("Success");
     mqttClient.setCallback(callback);
  }
  else
  {
    Serial.println("Fail");
  }
 }

int wifiConnected = 1;
unsigned int previousWifiTime = 0;
String message;
int cmd;


void MQTTmy::cmdt() {
 
    if (mqttClient.subscribe("/smartsocket1/ctrl")) {
      Serial.println("Subscribed");
      
    }
    else {
      Serial.println("Not subscribed");
    }
    cmd = (int)message[0];
    switch (cmd) {
      case 'N': {
          ext.power(1);
          break;
        }
      case 'F': {
          ext.power(0);
          break;
        }
      case 'D': {
       message = message.substring(1,message.length());
        }
        }


  

}


static void callback (char* topic, unsigned char* payload, unsigned int lenght) {
  Serial.print("Command: ");
  for (int i = 0; i < lenght; i++)
  {
    message += char(payload[i]);
  }
 
  Serial.println("");

}
