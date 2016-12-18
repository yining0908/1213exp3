
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
/* Set these to your desired credentials. */
const char *ssid = "hi";
const char *password = "12345678";
ESP8266WebServer server(80);

const int led = 13;
char led_status[25];
String webSite;
byte x = 0;
void buildWeb() {
  webSite+="<html>\n";
  webSite+="<head>\n";
  webSite+="<meta charset='UTF-8'/>\n";
  webSite+="<title>HIHI MOTOR</title>\n";
  webSite+="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
   webSite+="<script>";
  webSite+="<style>\n";
  webSite+="body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n";
  webSite+="div{width: 500px;  text-align: center;margin:50 auto;}\n";
  webSite+="</style>\n";
  webSite+="</head>\n";
  webSite+="<body>\n";
  webSite+="<div>\n";
  webSite+="<h1>LED Control Form ~</h1>\n";
  webSite+="<p id=\"ledstatus\">You can select a LED status ...</p>\n";
  webSite+="<form action=\"/form1\">\n";
  webSite+="<input type=\"radio\" id=\"on\" name=\"led\" value=\"on\"><label for=\"on\"> ON </label>\n";
  webSite+="<input type=\"radio\" id=\"off\" name=\"led\" value=\"off\"><label for=\"off\"> OFF </label><br><br>\n";
  webSite+="<input type=\"submit\" value=\"submit\"></form>\n";
  webSite+="</div>\n";
  webSite+="</body>\n";
  webSite+="</html>\n";      
}
void handleRoot() {
  server.send ( 200, "text/html", webSite ); //send back client a HTML file
}
void handleLEDStatus() {
  if (server.arg("led") == "off") {
  x=0;
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  }
  else{
  x=1;
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  }
  server.send ( 200 , "text/html" , "" );
}

void handleNotFound() {
  server.send ( 404, "text/html", "404 Error!" );  
}
void setup() {
  Serial.begin(115200);
  buildWeb();
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  WiFi.begin(ssid, password); 
  Serial.println("");
  //WiFi.softAP(ssid, password);

  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.on ( "/", handleRoot );
  server.on("/form1",handleLEDStatus);
  server.onNotFound ( handleNotFound );
  Wire.begin(4,5);
  server.begin();
  



}
void loop() {
  server.handleClient();
}

