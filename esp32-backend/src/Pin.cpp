#include <Arduino.h>
#include "Device.h"
#include "Pin.h"

#define PIN_STATUS_DISABLED 0
#define PIN_STATUS_ENABLED 1
#define PIN_STATUS_FIRED 2

#define DEVICE_ENVIRONMENT_DEVELOPMENT 1
#define DEVICE_ENVIRONMENT_PRODUCTION 2
#define DEVICE_ENVIRONMENT_TESTING 3

void Pin::enable() {
    if (device->getEnvironment() == DEVICE_ENVIRONMENT_DEVELOPMENT || device->getEnvironment() == DEVICE_ENVIRONMENT_TESTING)
    {
        String log = "";
        log.concat("Pin ");
        log.concat(number);
        log.concat(" has been enabled...");
        Serial.println(log);
    }
    status = PIN_STATUS_ENABLED;
}
void Pin::disable() {
    if (device->getEnvironment() == DEVICE_ENVIRONMENT_DEVELOPMENT || device->getEnvironment() == DEVICE_ENVIRONMENT_TESTING)
    {
        String log = "";
        log.concat("Pin ");
        log.concat(number);
        log.concat(" has been disabled...");
        Serial.println(log);

    }
    status = PIN_STATUS_DISABLED;
}
void Pin::fire() {
    if(status == PIN_STATUS_DISABLED)
    {
        if (device->getEnvironment() == DEVICE_ENVIRONMENT_DEVELOPMENT || device->getEnvironment() == DEVICE_ENVIRONMENT_TESTING)
        {
        Serial.println("Cannot fire disabled pin...");
        }
        return;
    }
    if(status != PIN_STATUS_ENABLED)
    {
        if (device->getEnvironment() == DEVICE_ENVIRONMENT_DEVELOPMENT || device->getEnvironment() == DEVICE_ENVIRONMENT_TESTING)
        {
        Serial.println("Pin has already been fired...");
        }
        return;
    }
    if(status != PIN_STATUS_ENABLED)
    {
        if (device->getEnvironment() == DEVICE_ENVIRONMENT_DEVELOPMENT || device->getEnvironment() == DEVICE_ENVIRONMENT_TESTING)
        {
        Serial.println("Invalid pin status - cannot fire...");
        }
        return;
    }
    int fireTime = device->getFireTime();
    if(!fireTime) return;
    if (device->getEnvironment() == DEVICE_ENVIRONMENT_PRODUCTION || device->getEnvironment() == DEVICE_ENVIRONMENT_TESTING)
    {
    digitalWrite(number, 1);
    }
    delay(fireTime);
    if (device->getEnvironment() == DEVICE_ENVIRONMENT_PRODUCTION || device->getEnvironment() == DEVICE_ENVIRONMENT_TESTING)
    {
    digitalWrite(number, 0);
    }
    if (device->getEnvironment() == DEVICE_ENVIRONMENT_DEVELOPMENT || device->getEnvironment() == DEVICE_ENVIRONMENT_TESTING)
    {
        String log = "";
        log.concat("Pin ");
        log.concat(number);
        log.concat(" has been fired...");
        Serial.println(log);
    }
    status = PIN_STATUS_FIRED;
}
int Pin::getStatus() {return status;}

void Pin::getStatusString(String *result) {
    *result = "";
    (*result).concat("{\"pinNumber\":\"");
    (*result).concat(String(number));
    (*result).concat("\",\"status\":\"");
    switch(status)
    {
        case PIN_STATUS_DISABLED:
            (*result).concat("disabled");
            break;
        case PIN_STATUS_ENABLED:
            (*result).concat("enabled");
            break;
        case PIN_STATUS_FIRED:
            (*result).concat("fired");
            break;
        default:
            *result = ""; 
            return;
            break;
    }
    (*result).concat("\"}");
}

Device *Pin::getDevice() {return device;}
Pin::Pin(int pinNumber, Device *dev) {
    status = PIN_STATUS_DISABLED;
    number = pinNumber;
    device = dev;
}
Pin::~Pin() {
}

int Pin::getNumber() {
    return number;
}
