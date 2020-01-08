
//Librerias ESP

//#include <ESP8266WIFI.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
//#include <SPI.h>

//Configuramos la red y servidor
//const char* ssid = "SSID"; //SSID del wifi al que nos conectemos
//const char* password = "contrasenna"; //contrasenna del wifi al que nos conectemos
//WiFiServer server(80);

//Configuramos LM35
int outputpin = A0;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("Conectandose...");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("Aun no se ha conectado");
    }

    Serial.print("");
    Serial.print("Ya se ha conectado al wifi con ip: ");
    Serial.print(WiFi.localIP());
}

void loop() {
  int voltaje = analogRead(outputpin);
  float millivolts = (voltaje / 1024.0) * 3300; //3300 porque es el voltaje que le damos desde el esp
  float celsius = millivolts / 10;
  Serial.print("Temperatura en celsius: ");
  Serial.println(celsius);
}
/*
//Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Prepare your HTTP POST request data
      String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                            + "&location=" + sensorLocation + "&value1=" + String(bme.readTemperature())
                            + "&value2=" + String(bme.readHumidity()) + "&value3=" + String(bme.readPressure()/100.0F) + "";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);

      // You can comment the httpRequestData variable above
      // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");

      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
*/
