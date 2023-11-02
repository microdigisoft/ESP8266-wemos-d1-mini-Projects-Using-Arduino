#include "DHT.h"// import DHT11 sensor
#include <ESP8266WiFi.h> //import ESP8266 WiFi library
#include <ESP8266HTTPClient.h>//import ESP8266 HTTP Client library
#include <WiFiClient.h> // Add Wifi Client
#define DHTTYPE DHT11     //Deine DHT 11 
#define DHTPIN  D3  
#define RETRY_LIMIT  20
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "--Your WIFI SSID--"; // Enter your local network SSID
const char* password ="--Your WIFI Password--";// Enter your local network Password
String SensorName = "DHT11"; // Define Sensor name to enter in database
String sensorLocation = "Wemos";// Define Sensor location name to enter in database
void setup()
{ 
    dht.begin();// Start DHT11 Sensor 
    Serial.begin(115200);// Open Serial monitor at baud rate 115200
    WiFi.begin(ssid,password);// Pass the credential for local wifi network to connect ESP8266 board
    while (WiFi.status()!= WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP Address");
    Serial.println(WiFi.localIP()); 
}
void loop()
{
    int rtl = RETRY_LIMIT;
    float h =  dht.readHumidity();// Read Humidity from DHT11 sensor
    float t= dht.readTemperature();// Read Temperature from DHT11 sensor
    delay(500);
    while (isnan(t) || isnan(h)){
      Serial.println("Check sensor again - " + rtl);
       h =  dht.readHumidity();
       t= dht.readTemperature();
      delay(500);
      if (--rtl < 1){
        ESP.restart(); // At times the DHT11 just kept returning NAN. A Restart fixed this.
      }
    }  
    //Open a connection to the server
      HTTPClient http;
      http.begin("http://domain.com/wemos/writedata.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //format your POST request.
    //SensorName,location,Tempraure,Humidity,
      int httpResponseCode = http.POST("&SensorName=" + SensorName
                          + "&location=" + sensorLocation + "&Temprature=" + String(t)
                          + "&Humidity=" + String(h) + "");

      if (httpResponseCode >0){
          //check for a return code - This is more for debugging.
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      }
      else{
        Serial.print("Error on sending post");
        Serial.println(httpResponseCode);
      }
    //closde the HTTP request.
      http.end(); 
    //Monitor values in console for debugging.
      Serial.println("Temp = " + String(t));#include <ESP8266WiFi.h>//Import ESP8266 WiFi library
#include <WiFiClient.h>//Import WiFi library
#include <ESP8266WebServer.h> //Import ESP8266 WiFi Webserver

#ifndef APSSID
#define APSSID "microdigisoft"
#define APPSK  "microdigisoft"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", "< h1 >You are connected");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

      Serial.println("humidity = " + String(h));  
   //wait 2 minutes for next reading
    delay(30000);
}
