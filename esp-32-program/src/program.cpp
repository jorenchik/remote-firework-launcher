#include "classes.h"
#include <WiFi.h>
#include <vector>

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
        Serial.print(WIFI_SSID);
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


void Pin::enable() {
    status = PIN_STATUS_ENABLED;
}
void Pin::disable() {
    status = PIN_STATUS_DISABLED;
}
void Pin::fire() {
    if(status == PIN_STATUS_DISABLED)
    {
        Serial.println("Cannot fire disabled pin...");
        return;
    }
    if(status != PIN_STATUS_ENABLED)
    {
        Serial.println("Pin has already been fired...");
        return;
    }
    if(status != PIN_STATUS_ENABLED)
    {
        Serial.println("Invalid pin status - cannot fire...");
        return;
    }
    int fireTime = device->getFireTime();
    if(!fireTime) return;
    digitalWrite(pinNumber, 1);
    delay(fireTime);
    digitalWrite(pinNumber, 0);
    status = PIN_STATUS_FIRED;
}
int Pin::getStatus() {return status;}
Device *Pin::getDevice() {return device;}
Pin::Pin(int pinNum, Device *dev) {
    status = PIN_STATUS_DISABLED;
    pinNumber = pinNum;
    device = dev;
}
Pin::~Pin() {
}

int Pin::getPinNumber() {
    return pinNumber;
}
