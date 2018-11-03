// Config.h 
// User specific configuration for SynScanESPServer
// 
// Copyright (c) 2018 Roman Hujer   http://hujer.net
//


//#define MODE_AP // phone connects directly to ESP
#define MODE_STA // ESP connects to WiFi router


#ifdef MODE_AP
// For AP mode:
const char *ssid = "SynScan";  // You will connect your phone to this Access Point
const char *pw = "SynScanESP"; // and this is the password
IPAddress ip(192, 168, 4, 1); // From RoboRemo app, connect to this IP
IPAddress netmask(255, 255, 255, 0);

#endif


#ifdef MODE_STA
// For STATION mode:
const char *ssid = "EQ6ProHR";  // Your ROUTER SSID
const char *pw = "OnStepHR"; // and WiFi PASSWORD

#endif
