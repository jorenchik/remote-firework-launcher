
/* ESP32 running configuration*/
#define WIFI_SSID "ESP32-AP"
#define WIFI_PASSWORD "password"
#define WIFI_CHANNEL 6

// Development - 1 (Serial monitor logs, actuators doesn't act)
// Production - 2 (No serial monitor logs, actuators act)
// Testing - 3 (Serial monitor logs, atuator act)
#define CURRENT_ENVIRONMENT 1

// Soft AP - 1
// Station - 2
#define CURRENT_WIFI_MODE 1

