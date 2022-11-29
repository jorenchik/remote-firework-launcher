#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <uri/UriBraces.h>

#include "classes.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

#define DEVICE_STATUS_NOT_READY 0
#define DEVICE_STATUS_READY 1

#define PIN_STATUS_DISABLED 0
#define PIN_STATUS_ENABLED 1
#define PIN_STATUS_FIRED 2

#define DEVICE_WIFI_MODE_SOFT_AP 1
#define DEVICE_WIFI_MODE_STATION 2

WebServer server(80);
Device *device;

void handleGetDeviceStatus();
void handleGetPinStatus();
void handleGetPinsStatus();
void handlePinEnable();
void handleResetDeviceConfig();
void handleNotFound();

void setup(void) {
  Serial.begin(115200);
  device = new Device(DEVICE_WIFI_MODE_STATION);
  device->setupWifi(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);

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

void handleGetDeviceStatus() {
  int deviceStatus = device->getStatus();
  String deviceStatusStr;
  switch(deviceStatus)
  {
    case DEVICE_STATUS_NOT_READY:
      deviceStatusStr = "not-ready";
      break;
    case DEVICE_STATUS_READY:
      deviceStatusStr = "ready";
      break;
    default:
      server.send(500, "text/plain", "{\"message\":\"Internal server error.\"}");
      return;
      break;
  }
  server.send(200, "text/plain", "{\"status\":\"" + deviceStatusStr + "\"}");
  return;
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