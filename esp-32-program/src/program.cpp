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
    if (mode != DEVICE_WIFI_MODE_SOFT_AP || mode != DEVICE_WIFI_MODE_SOFT_AP)
    {
        wifiMode = DEVICE_WIFI_MODE_STATION;
    }
}
Device::~Device() {}
std::vector<Pin*> *Device::getPins() {return &pins;}
std::vector<int> *Device::getAvailablePinNumbers() {return &availablePinNumbers;}
void Device::connectToWifi()
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
    this->initPins();
    status = DEVICE_STATUS_READY;
}
int Device::getStatus() {return status;}
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
    // if enabled if not fired....
    String log = "Pin " + pinNumber;
    Serial.println(log);
    status = PIN_STATUS_FIRED;
}
int Pin::getStatus() {return status;}
Device *Pin::getDevice() {return device;}
Pin::Pin(int pinNum, Device *device) {
    status = PIN_STATUS_DISABLED;
    pinNumber = pinNum;
    device = device;
}
Pin::~Pin() {
}

int Pin::getPinNumber() {
    return pinNumber;
}
