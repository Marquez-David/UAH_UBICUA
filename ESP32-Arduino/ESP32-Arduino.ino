#include <SimpleDHT.h>

int pinDHT11 = 2;
SimpleDHT11 dht11;

void setup(){
  Serial.println("Temperatura y humedad");
  Serial.begin(115200);
}

void loop(){
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess){
    Serial.print("Error al leer el dht");
    Serial.println(err);
    delay(1000);
    return;
  }

  Serial.println((int)temperature);
  Serial.println((int)humidity);
  //delay(1500);
}
