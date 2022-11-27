#include <vector>

class Pin;
class Device
{
  int status;
  int wifiMode;
  std::vector<Pin> enabledPins;
  std::vector<Pin> disabledPins;
  std::vector<int> availablePins{13,16,17,18,19,21,22,23,25,26,27,32,33};

  public:
  Device(int mode);
  ~Device();
  void connectToWifi();
  std::vector<Pin> *getEnabledPins();
  std::vector<Pin> *getDisabledPins();
  std::vector<int> *getAvailablePins();
  int getStatus();
};

class Pin
{
  int status;
  int pinNumber;
  Device *device;
  
  public:
  Pin(int pinNum, Device *device);
  ~Pin();
  void enable();
  void disable();
  void fire();
  int getStatus();
  Device *getDevice();
};