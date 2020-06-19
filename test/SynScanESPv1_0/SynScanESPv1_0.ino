/* 
   SynScanESPBasic.ino

   SynScan ESP Server basic version

   Copyright (c) 2018 Roman Hujer   http://hujer.net

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,ss
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Description:
   SynScanESPServer 
   
   Wiring and PCB on  https://easyeda.com/hujer.roman/wifi-for-synscan

*/

#define Version "1.0"
#include "Config.h"
#include "Setup.h"


const int port = tcp_port; 

#ifdef ESP32
#include "WiFi.h"
#else
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#endif
#include <algorithm> // std::min

WiFiServer server(port);
WiFiClient serverClient[MaxClient];

uint8_t buf1[bufferSize];
uint8_t i1=0;

uint8_t buf2[bufferSize];
uint8_t i2=0;

// For AP mode:
const char *ssid = MY_SSID;  
const char *pw = MY_PASS; 

IPAddress ip(192, 168, 4, 1); 
IPAddress netmask(255, 255, 255, 0);


void setup() {

  delay(500);
  
  Serial.begin(UART_BAUD);
//  Serial.setRxBufferSize(RXBUFFERSIZE);

    
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask); 
  WiFi.softAP(ssid, pw);
  

  Serial.println("#");  //SynScan ECHO
  server.begin(); // start TCP server 

}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // as long as there are bytes in the serial queue,
  // read them and send them out the socket if it's open:
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    if (client.connected()) {
      client.print(inChar);
    }
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // do nothing:
    while (true);
  }
}
