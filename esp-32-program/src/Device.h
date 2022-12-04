#include <vector>

class Pin;
class Device
{
  int status;
  int wifiMode;
  int fireTime;
  std::vector<Pin*> pins; // Active/inactive pins on the device
  std::vector<int> availablePinNumbers{13,16,17,18,19,21,22,23,25,26,27,32,33}; // Pin numbers that will be initialized along the device

  public:
  Device(int mode);
  ~Device();
  void setupWifi(char *wifiSsid, char *wifiPassword, int wifiChannel);
  int getStatus();
  void initPins(); // Creates pin object for every available pinNumber
  int getFireTime();
  void getStatusString(String *result);
  Pin *getPin(int pinNumber); // Gets a pin pointer by the pinNumber
  std::vector<Pin*> *getPins();
  std::vector<int> *getAvailablePinNumbers();
};