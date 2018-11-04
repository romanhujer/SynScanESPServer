# SynScanESPServer


Wireless control SynScan EQ mount   (example SkyWatcher EQ6 Pro, HEQ5 ...) in SkySafari Apps
 

*  Wiring diagram and PCB on [EasyEDA](https://easyeda.com/hujer.roman/wifi-for-synscan)
*  SynScanFreeCad     -  FreeCAD and stl models for 3D printing


## Basic version:

*  SynScanESPbasic  -  Only WiFi AP mode and Uart bridge 
<pre>
	SSID:  SynScan
	Pass:  SynScanESP
	IP:  192.168.4.1
	TcpPort: 11880 
</pre>

## Advance version:

*  SynScanESPv1_0  -  Satus/config WWW Server (now in progress)


## NOTE:

For an ESP8266 ESP-01 module use the wiring as shown in numerous places on the internet to get the module in firmware upload mode. To send the firmware I use the Arduino IDE with the add-on for the ESP8266. To get this setup...

Look in the Arduino Preferences menu and place this line in the additional "Boards Manager" area: http://arduino.esp8266.com/staging/package_esp8266com_index.json Then from the "Tools->Boards->Boards Manager" menu select the ESP8266 add-on.

Then pick "Tools->Boards->Generic 8266 Module" (for an ESP-01) or select your device from the list.

More info about flash programing ESP-01 on https://www.diyhobi.com/flash-program-esp-01-using-usb-serial-adapter/


