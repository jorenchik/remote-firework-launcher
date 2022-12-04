#include <Arduino.h>
#include "Pin.h"

#define PIN_STATUS_DISABLED 0
#define PIN_STATUS_ENABLED 1
#define PIN_STATUS_FIRED 2

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
    digitalWrite(number, 1);
    delay(fireTime);
    digitalWrite(number, 0);
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
