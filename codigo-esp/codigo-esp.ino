#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESPDateTime.h>

#define WIFI_SSID "Wifidavid"
#define WIFI_PASS "david123"

char server[] = "192.168.43.118";

WiFiClient client;

SoftwareSerial s(D6,D5);
int data;
void setup() {
  s.begin(115200);
  Serial.begin(115200);
  setupWifi();
  setupDate();
  while (!Serial) continue;
}

void setupWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("WiFi Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
}

void setupDate(){
  DateTime.setTimeZone(1);
  DateTime.begin();
  if (!DateTime.isTimeValid()) {
    Serial.println("Failed to get time from server.");
  }
}

 
void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  s.write("s");

  if (root == JsonObject::invalid())
  {
    return;
  }
  if (s.available()>0)
  {
    data=s.read();
  }
  else{
    Serial.println("No va");
  }

  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  int data1=root["temp"];
  int data2=root["pulso"];
  int data3=root["humedad"];
  int data4=root["temp_dht"];
  
  Serial.println("");
  Serial.print("Temperatura ");
  Serial.println(data1);
  Serial.print("Pulso ");
  Serial.println(data2);
  Serial.print("Humedad ");
  Serial.println(data3);
  Serial.print("Temperatura del DHT ");
  Serial.println(data4);

  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");

    if (!DateTime.isTimeValid()) {
      Serial.println("Failed to get time from server, retry.");
      DateTime.begin();
    }else {
   DateTimeParts p = DateTime.getParts();

   char dia = p.getMonthDay();
   char horas = p.getHours();
   char minutos = p.getMinutes();
   char segundos = p.getSeconds();

   //String fecha = DateTime.toString().c_str();
   time_t t = DateTime.now();
   String fecha = DateFormatter::format("%d-%H-%M-%S", t);

   
   //String fecha = String(horas) + String(minutos) + String(segundos);
  Serial.printf("%02d %02d:%02d:%02d\n",dia, horas,minutos,segundos);
  
  String valores = "https://192.168.43.118:8080/v1.0obi/Servlet_arduino_medicion1_in?" + String(data4) + "-" + String(data3) + "-" + String(data1) + "-" + String(data2) + "-" + fecha;
  Serial.print(valores);
  Serial.println("");

  if(client.connect(server, 8080)){
      Serial.println("- connected");
      Serial.println("Me conecto al servidor");
      client.println("POST "+ valores +" HTTP/1.1");
      client.print("Host: 192.168.43.118");
      client.print("User-Agent: Arduino/1.0");
      client.print("Connection: close");
      client.print("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(valores.length());
      client.println();
      client.print(valores);
      Serial.println("- done");
    }else{
      Serial.print("No se ha podido conectar con el sevidor");
    }
    Serial.println("Disconnecting from server...");
    client.stop();
    Serial.println("- bye!");
  }
  
   

    delay(10000);
}
 
