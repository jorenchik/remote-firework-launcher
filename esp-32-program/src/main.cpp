#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <uri/UriBraces.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6


WebServer server(80);

void connectToWifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void handleGetDeviceStatus() {
  server.send(200, "text/plain", "{\"status\": \"ready\", \"pinsAvailable\": [TK]}");
}

void handleGetPinStatus() {
  String pinNum = server.pathArg(0);
  server.send(200, "text/plain", "{\"pinNumber\":" + pinNum + ",\"pinStatus:" + "\"STATUS\"}");
}

void handleGetPinsStatus() {
  // for each pin get status of it
  // make a string of JSON object that will indicate status of every pin
  server.send(200, "text/plain", "{\"enabledPins\": [TK]}");
}

void handlePinEnable() {
  String pinNum = server.pathArg(0);
  // getPinStatus(pinNum);
  server.send(200, "text/plain", "Pin status of " + pinNum + " goes here...");
}

void handleResetDeviceConfig() {
  server.send(200, "text/plain", "{\"message\": \"Device has been successfully reset\"}");
}

void handleNotFound() {
  server.send(404, "text/plain", "{\"message\": \"The route hasn't been found\"}");
}

void setup(void) {
  Serial.begin(115200);

  connectToWifi();

  server.on(UriBraces("/status/device"), handleGetDeviceStatus);
  server.on(UriBraces("/status/pin/{}"), handleGetPinStatus);
  server.on(UriBraces("/status/pins"), handleGetPinsStatus);
  server.on(UriBraces("/set/device/defaults"), handleResetDeviceConfig);
  server.on(UriBraces("/pin/enable/{}"), handlePinEnable);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);
}