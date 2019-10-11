/*
 * OBJ: Script que se encraga de leer los datos de un sensor de temperatura y enciende un LED cuando pasa una cierta temperatura
 * Autor: David Márquez 
 * Version: 1.0.0
 */

 int sensor = 0;
 int umbral = 25; //

//Se hace solo la primera vez
void setup() {
  Serial.begin(9600);
  pinMode(11,OUTPUT);
}

//Se hace todo el rato
void loop() {
  int lectura = analogRead(sensor);
  float volt = 5.0 / 1024 * lectura;
  float temp = volt * 100 - 50

}
