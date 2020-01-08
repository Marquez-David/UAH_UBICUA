#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(3,1);


void setup() {
  Serial.begin(115200);
  s.begin(115200);
  while (!Serial) continue;
}
 
void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
 
  if (root == JsonObject::invalid())
  {
    return;
  }
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Temperature ");
  int data1=root["temp"];
  Serial.println(data1);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");
}
