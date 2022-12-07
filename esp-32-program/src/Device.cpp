#include <WiFi.h>
#include <vector>
#include "Device.h"
#include "Pin.h"

#define DEVICE_STATUS_NOT_READY 0
#define DEVICE_STATUS_READY 1

#define DEVICE_WIFI_MODE_SOFT_AP 1
#define DEVICE_WIFI_MODE_STATION 2

#define DEVICE_FIRETIME 2000

Device::Device(int mode) {
    status = DEVICE_STATUS_NOT_READY;
    fireTime = DEVICE_FIRETIME;
    wifiMode = mode;
    this->initPins();
}
Device::~Device() {}
std::vector<Pin*> *Device::getPins() {return &pins;}
std::vector<int> *Device::getAvailablePinNumbers() {return &availablePinNumbers;}
void Device::setupWifi(char *wifiSsid, char *wifiPassword, int wifiChannel)
{
    if (wifiMode == DEVICE_WIFI_MODE_SOFT_AP)
    {
        Serial.print("Setting AP (Access Point)…");
        WiFi.softAP(wifiSsid, wifiPassword, wifiChannel);
        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
    }
    else if (wifiMode == DEVICE_WIFI_MODE_STATION)
    {
        WiFi.begin(wifiSsid,wifiPassword,wifiChannel);
        Serial.print("Connecting to WiFi ");
        Serial.print(wifiSsid);
        while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
        }
        Serial.println(" Connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else
    {
        Serial.println("Failed to setup WiFi: invalid WiFi mode.");
        Serial.println("Halting the setup...");
        exit(0);  
    }
    status = DEVICE_STATUS_READY;
}
int Device::getStatus() {return status;}
int Device::getFireTime() {return fireTime;}
void Device::initPins() {
    std::vector<int>::iterator pinNumPtr = availablePinNumbers.begin();
    while(pinNumPtr != availablePinNumbers.end())
    {
        Pin *newPinPtr = new Pin(*pinNumPtr, this);
        pinMode(*pinNumPtr, OUTPUT);
        this->pins.push_back(newPinPtr);
        pinNumPtr++;
    }
}
Pin *Device::getPin(int pinNumber)
{
    std::vector<Pin*>::iterator iter = pins.begin();
    Pin *foundPin;
    while(iter != pins.end())
    {
        if ((*iter)->getNumber() == pinNumber)
        {
            return (*iter);
        }
        iter++;
    }
    return NULL;
}
void Device::getStatusString(String *result)
{
    *result = "";
    (*result).concat("{\"status\":\"");
    switch(status)
    {
        case DEVICE_STATUS_NOT_READY:
            (*result).concat("not-ready");
            break;
        case DEVICE_STATUS_READY:
            (*result).concat("ready");
            break;
        default:
            *result = "";
            return;
            break;
    }
    (*result).concat("\"}");
}
