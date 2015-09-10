// Import required libraries
#include "ESP8266WiFi.h"

// WiFi parameters
const char* ssid = "SSID";
const char* password = "WIFIPASS";

// pimatic parameters
const char* PimaticUser = "admin";
const char* PimaticPassword = "admin";
const char* PimaticHost = "192.168.0.x";
const int PimaticPort = 80;


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
yourdata = "{\"type\": \"value\", \"valueOrExpression\": \"777\"}";
  
  
    client.print("PATCH /api/variables/test");
    client.print(" HTTP/1.1\r\n");
    client.print("Authorization: Basic ");
    client.print("YWRtaW46bWFyY2VsOTk="); //user:password encoded to base64 via https://www.base64encode.org/
    client.print("\r\n");
    client.print("PimaticHost: 192.168.0.x\r\n");
    client.print("Content-Type:application/json\r\n");
    client.print("Content-Length: ");
    client.print(yourdata.length());
    client.print("\r\n\r\n");
    client.print(yourdata);
    

   delay(500);

const char* status = "true";

   client.print("GET /api/device/aqua4/changeStateTo?state=");
    client.print(status);
    client.print(" HTTP/1.1\r\n");
    client.print("Authorization: Basic "); //user:password encoded to base64 via https://www.base64encode.org/
    client.print("YWRtaW46bWFyY2VsOTk=");
    client.print("\r\n");
    client.print("PimaticHost: 192.168.0.x\r\n");
    client.print("Content-Type:application/json\r\n");
    client.print("Content-Length: ");
    client.print(yourdata.length());
    client.print("\r\n\r\n");
    client.print(yourdata);   
  
  
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

