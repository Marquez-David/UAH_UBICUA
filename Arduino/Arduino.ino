//Arduino code
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
 
void setup() {
  s.begin(115200);
  pinMode(A0, INPUT);
}

StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

void loop() {
  int lecturaTemp = analogRead(A0);
  
  float volt = (lecturaTemp /1024.00) * 5000;
  float temp = volt/10;
  s.print(temp);
  
  if (isnan(lecturaTemp) /*|| isnan(t) || isnan(f)*/) {
    return;
  }
  root["temp"] = temp;

  if(s.available()>0){
    root.printTo(s);
    }
}
