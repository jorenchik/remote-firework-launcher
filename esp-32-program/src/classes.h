#include <vector>

class Pin;
class Device
{
  int status;
  int wifiMode;
  std::vector<Pin> pins;
  std::vector<int> availablePinNumbers{13,16,17,18,19,21,22,23,25,26,27,32,33};

  public:
  Device(int mode);
  ~Device();
  void connectToWifi();
  int getStatus();
  std::vector<Pin> *getPins();
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
  int getStatus();
  void enable();
  void disable();
  void fire();
  Device *getDevice();
};