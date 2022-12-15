class Pin
{
  int status;
  int number;
  Device *device;
  
  public:
  Pin(int pinNumber, Device *device);
  ~Pin();
  void enable(); // Makes the pin available for it to be fired
  void disable(); // Makes the pin unavailable for it to be fired
  void fire(); 
  int getStatus();
  void getStatusString(String *result);
  int getNumber();
  Device *getDevice();
};