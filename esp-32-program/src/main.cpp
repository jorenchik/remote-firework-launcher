#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include "Device.h"
#include "Pin.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

#define DEVICE_WIFI_MODE_SOFT_AP 1
#define DEVICE_WIFI_MODE_STATION 2

WebServer server(80);
Device *device;

void handleGetDeviceStatus();
void handleGetPinStatus();
void handleGetPinsStatus();
void handlePinEnable();
void handlePinDisable();
void handleResetDeviceConfig();
void handleNotFound();
void handlePinFire();
void handleSaveSettings();
Pin *getPinByNumber(String pinNumberStr);

void setup(void) {
  Serial.begin(115200);
  device = new Device(DEVICE_WIFI_MODE_STATION);
  device->setupWifi(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);

  server.on(UriBraces("/device/status"), handleGetDeviceStatus);
  server.on(UriBraces("/pin/status/{}"), handleGetPinStatus);
  server.on(UriBraces("/device/pins/status"), handleGetPinsStatus);
  server.on(UriBraces("/device/reset"), handleResetDevice);
  server.on(UriBraces("/pin/enable/{}"), handlePinEnable);
  server.on(UriBraces("/pin/disable/{}"), handlePinDisable);
  server.on(UriBraces("/pin/fire/{}"), handlePinFire);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);
}
 
void sendInvalidArguments() {
  server.send(400, "text/plain", "{\"message\":\"Invalid arguments.\"}");
}

void sendItemNotFound() {
  server.send(404, "text/plain", "{\"message\": \"The requested item hasn't been found.\"}");
}

void sendInternalServerError() {
  server.send(500, "text/plain", "{\"message\":\"Internal server error.\"}");
}

Pin *getPinByNumber(String pinNumberStr)
{
  int pinNumber;
  try
  {
    pinNumber = pinNumberStr.toInt();
  }
  catch (std::exception e) 
  {
    sendInvalidArguments();
    return NULL;
  }
  if(!pinNumber)
  {
    sendInvalidArguments();
    return NULL;
  }
  Pin *pin = device->getPin(pinNumber);
  if (!pin)
  {
    sendItemNotFound();
    return NULL;
  }
  return pin;
}

void handleGetDeviceStatus() {
  String response;
  device->getStatusString(&response);
  if(response == "")
  {
    sendInternalServerError();
    return;
  }
  server.send(200, "text/plain", response);
  return;
}

void handleGetPinStatus() {
  String pinNumberStr = server.pathArg(0), response;
  Pin *pin;
  pin = getPinByNumber(pinNumberStr);
  if(!pin)
  {
    return;
  }
  pin->getStatusString(&response);
  server.send(200, "text/plain", response);
}

void handleGetPinsStatus() {
  // for each pin get status of it
  // make a string of JSON object that will indicate status of every pin
  String response;
  response.concat("{\"enabledPins\": [");
  std::vector<Pin*> *devicePins = device->getPins();
  std::vector<Pin*>::iterator devicePinsIterator = devicePins->begin();
  while(devicePinsIterator != devicePins->end())
  {
    String pinStatusString = "";
    (*devicePinsIterator)->getStatusString(&pinStatusString);
    if(pinStatusString == "")
    {
      sendInternalServerError();
      return;
    }
    if(devicePinsIterator - devicePins->begin() != 0)
    {
      response.concat(",");
    }
    response.concat(pinStatusString);
    devicePinsIterator++;
  }
  response.concat("]}");
  server.send(200, "text/plain", response);
}

void handlePinEnable() {
  String pinNumberStr = server.pathArg(0), response;
  Pin *pin;
  pin = getPinByNumber(pinNumberStr);
  if(!pin)
  {
    return;
  }
  pin->enable();
  pin->getStatusString(&response);
  server.send(200, "text/plain", response);
}

void handlePinDisable() {
  String pinNumberStr = server.pathArg(0), response;
  Pin *pin;
  pin = getPinByNumber(pinNumberStr);
  if(!pin)
  {
    return;
  }
  pin->disable();
  pin->getStatusString(&response);
  server.send(200, "text/plain", response);
}

void handlePinFire() {
  String pinNumberStr = server.pathArg(0), response;
  Pin *pin;
  pin = getPinByNumber(pinNumberStr);
  if(!pin)
  {
    return;
  }
  pin->fire();
  pin->getStatusString(&response);
  server.send(200, "text/plain", response);
}

void handleResetDevice() {
  String response;
  response.concat("{\"enabledPins\": [");
  std::vector<Pin*> *devicePins = device->getPins();
  std::vector<Pin*>::iterator devicePinsIterator = devicePins->begin();
  while(devicePinsIterator != devicePins->end())
  {
    String pinStatusString = "";
    (*devicePinsIterator)->disable();
    (*devicePinsIterator)->getStatusString(&pinStatusString);
    if(pinStatusString == "")
    {
      sendInternalServerError();
      return;
    }
    if(devicePinsIterator - devicePins->begin() != 0)
    {
      response.concat(",");
    }
    response.concat(pinStatusString);
    devicePinsIterator++;
  }
  response.concat("]}");
  server.send(200, "text/plain", response);
}

void handleNotFound() {
  server.send(404, "text/plain", "{\"message\": \"The route hasn't been found\"}");
}