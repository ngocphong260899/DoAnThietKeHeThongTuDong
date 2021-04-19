#include <Arduino.h>
#include "BluetoothSerial.h"
#include "ArduinoJson.h"
#include <string.h>

BluetoothSerial bleSerial;
StaticJsonBuffer<300> doc;
//String json = "{\"name\":\"phong\", \"age\": 15, \"add\": \"this is add\"}";

enum
{
  CH1_ON = 1,
  CH1_OFF = 2,
  CH2_ON = 3,
  CH2_OFF = 4
};

void control_IO(int cmd);

void parseJson(char *cmd)
{
  JsonObject &data = doc.parseObject(cmd);
  if (!data.success())
  {
    Serial.print("Phong_hg56 : Faild");
    return;
  }
  String name = data["name"].as<String>();
  Serial.println(name);
  int cmds = data["cmd"];
  Serial.println(cmds);
  control_IO(cmds);
  doc.clear();
}

char data[200];
void setup()
{
  Serial.begin(115200);
  bleSerial.begin("BLE_PHONG");
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(GPIO_NUM_14, OUTPUT);
  pinMode(GPIO_NUM_27, OUTPUT);
}

void loop()
{

  if (bleSerial.available())
  {
    bleSerial.setTimeout(10);
    String msg = bleSerial.readString();
    //Serial.println(msg.c_str());
    parseJson((char *)msg.c_str());
  }
}

void control_IO(int cmd)
{
  switch (cmd)
  {
  case CH1_ON:
  {
    Serial.println("relay 1 on");
    digitalWrite(GPIO_NUM_14, HIGH);
  }
  break;
  case CH1_OFF:
  {
    Serial.println("relay 1 off");
    digitalWrite(GPIO_NUM_14, LOW);
  }
  break;
  case CH2_ON:
  {
    Serial.println("relay 2 on");
    digitalWrite(GPIO_NUM_27, HIGH);
  }
  break;
  case CH2_OFF:
  {
    Serial.println("relay 2 off");
     digitalWrite(GPIO_NUM_27, LOW);
  }
  break;
  }
}
