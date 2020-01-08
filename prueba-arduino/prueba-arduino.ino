//Arduino code
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <SimpleDHT.h>

int pinDHT11 = 2;
SimpleDHT11 dht11;

SoftwareSerial s(5,6);
int sensorTemp = A0;
int sensorPulso = A1;
 
void setup() {
s.begin(115200);
pinMode(sensorTemp, INPUT);
pinMode(sensorPulso, INPUT);
}

//Creamos un json en el que meter nuestras mediciones
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
 
void loop() {
  
  int lecturaTemp = analogRead(sensorTemp);
  int lecturaPulso = analogRead(sensorPulso);
  
  //--------codigo para leer temperatura y humedad
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess){
    Serial.print("Error al leer el dht");
    Serial.println(err);
    delay(1000);
    return;
  }
 

  //-----codigo para leer la temperatura
  float temp = lecturaTemp * 0.48828125;

  root["temp"] = temp;
  root["pulso"] = lecturaPulso;
  root["humedad"] = ((int)humidity);
  root["temp_dht"] = ((int)temperature);
  
  if(s.available()>0){
    root.printTo(s);
  }

  //delay(1500);
}
