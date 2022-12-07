#include <vector>

class Pin;
class Device
{
  int status;
  int wifiMode;
  int fireTime;
  int environment;
  std::vector<Pin*> pins; // Active/inactive pins on the device
  std::vector<int> availablePinNumbers{13,16,17,18,19,21,22,23,25,26,27,32,33}; // Pin numbers that will be initialized along the device

  public:
  Device(int mode, int environment_);
  ~Device();
  void setupWifi(char *wifiSsid, char *wifiPassword, int wifiChannel);
  int getStatus();
  int getEnvironment();
  void initPins(); // Creates pin object for every available pinNumber
  int getFireTime();
  void getStatusString(String *result);
  Pin *getPin(int pinNumber); // Gets a pin pointer by the pinNumber
  std::vector<Pin*> *getPins();
  std::vector<int> *getAvailablePinNumbers();
};