#include <vector>

class Pin;
class Device
{
  int status;
  int wifiMode;
  std::vector<Pin*> pins; // Active/inactive pins on the device
  std::vector<int> availablePinNumbers{13,16,17,18,19,21,22,23,25,26,27,32,33}; // Pin numbers that will be initialized along the device

  public:
  Device(int mode);
  ~Device();
  void connectToWifi();
  int getStatus();
  void initPins(); // Creates pin object for every available pinNumber
  std::vector<Pin*> *getPins();
  std::vector<int> *getAvailablePinNumbers();
};


class Pin
{
  int status;
  int pinNumber;
  Device *device;
  
  public:
  Pin(int pinNum, Device *device);
  ~Pin();
  void enable(); // Makes the pin available for it to be fired
  void disable(); // Makes the pin unavailable for it to be fired
  void fire(); 
  int getStatus();
  int getPinNumber();
  Device *getDevice();
};