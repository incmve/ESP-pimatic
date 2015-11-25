// Import required libraries
#include "ESP8266WiFi.h"

#include <dht.h>

// Define pins
#define DHT11_PIN 4  // DHT11 pin



// WiFi parameters
const char* ssid = "SSID";
const char* password = "PASSWORD";

// pimatic parameters
const char* PimaticUser = "admin";
const char* PimaticPassword = "admin";
const char* PimaticHost = "192.168.0.20";
const int PimaticPort = 8080;


dht DHT;

void setup() {
  // Start Serial
  Serial.begin(115200);
  delay(10);
  

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
int  chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
                  float h = DHT.humidity;
                float t = DHT.temperature;
                Serial.println("temp");
                Serial.println(t);
                Serial.println("Hum");
                Serial.println(h);
  
                Serial.print("Connecting to ");
                Serial.println(PimaticHost);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(PimaticHost, PimaticPort)) {
    Serial.println("connection failed");
    return;
  }
  
  
  // This will send the request to the server

// YWRtaW46WndlbWJAZA==
String yourdata;
yourdata = "{\"type\": \"value\", \"valueOrExpression\": \"" + String(h) + "\"}";
  
  
    client.print("PATCH /api/variables/test1");
    client.print(" HTTP/1.1\r\n");
    client.print("Authorization: Basic ");
    client.print("YWRtaW46YWRtaW4=");
    client.print("\r\n");
    client.print("PimaticHost: mvegte.myqnapcloud.com\r\n");
    client.print("Content-Type:application/json\r\n");
    client.print("Content-Length: ");
    client.print(yourdata.length());
    client.print("\r\n\r\n");
    client.print(yourdata);
    

   delay(500);

  
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
  // Repeat every 10 seconds
  delay(10000);
 
}
