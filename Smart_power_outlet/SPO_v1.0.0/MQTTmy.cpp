#include "MQTTmy.h"

IPAddress ip (109, 121, 141, 188);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

static MQTTmy * instance;
static void _callback (char* topic, unsigned char* payload, unsigned int lenght) {
  instance->callback(topic, payload, lenght);
}

void MQTTmy::init(Externalmy* external, EEPROMmy* eeprom) {
  ext = external;
  eep = eeprom;
  mqttClient.setServer(ip, 1884);
  instance = this;

  if (mqttClient.connect("SmartSocketID"))
  {
    Serial.println("Success");
    mqttClient.setCallback(_callback);
  }
  else
  {
    Serial.println("Fail");
  }

  sub();
}

void MQTTmy::sub() {
  if (mqttClient.subscribe("/smartsocket1/ctrl"))
    Serial.println("Subscribed");
  else
    Serial.println("Not subscribed");
}

void MQTTmy::update() {
  mqttClient.loop();
}

void MQTTmy::callback (char* topic, unsigned char* payload, unsigned int length) {
  Serial.print("Command: ");

  char cmd;
  String message;

  for (int i = 0; i < length; i++)
  {
    message += char(payload[i]);
  }

  cmd = message[0];
  switch (cmd) {
    case 'N': {
        ext -> power(1);
        break;
      }
    case 'F': {
        ext -> power(0);
        break;
      }
    case 'D': {
        message = message.substring(1, message.length() - 1);
        eep -> saveToMem(message);
      }
  }

  Serial.println(cmd);
}
