#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESPDMX.h>

#define SSID ""
#define PW ""

ESP8266WebServer server(80);
DMXESPSerial dmx;

void setup(void){
  // serial is optional, but helpful to get the wifi IP
  Serial.begin(115200);
  Serial.println(F("Starting DMX Init"));
  // this initializes DMX is 512 channels.
  dmx.init(512);
  Serial.println(F("DMX initialization complete"));

  WiFi.begin(SSID, PW);

  Serial.println("Connecting to wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(F("."));
  }
  Serial.print(F("\nWifi connected. IP: "));
  Serial.println(WiFi.localIP());

  server.on("/update", update);
  server.begin();
  Serial.println(F("HTTP server started"));
}

void loop(void){
  server.handleClient();
}

void update() {
  // this is the main method that sends data to dmx
  // the next lines create a JSON output that is send back on success
  String message = "{\n";
  for (int i = 0; i < server.args(); i++) {
    message += "  \"channel" + server.argName(i) + "\": " + server.arg(i) + ",\n";
    // this sets the value of a channel but does not send the data
    dmx.write(server.argName(i).toInt(), server.arg(i).toInt());
  }
  // remove trailing ,
  int commaIndex = message.length() - 2;
  message.remove(commaIndex);
  message += "\n}\n";
  server.send(200, "text/json", message);
  // this actually sends out the data
  dmx.update();
}