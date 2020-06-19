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
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#endif
#include <algorithm> // std::min

#define MAX_SRV_CLIENTS 3

WiFiServer server(port);
WiFiClient serverClient[MAX_SRV_CLIENTS];


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
  Serial.setRxBufferSize(RXBUFFERSIZE);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask); 
  WiFi.softAP(ssid, pw);
  

  Serial.println("Ready...K1");  //SynScan ECHO
  server.begin(); // start TCP server 

}

void loop() {

//check if there are any new clients
  if (server.hasClient()) {
    //find free/disconnected spot
    int i;
    for (i = 0; i < MAX_SRV_CLIENTS; i++)
      if (!serverClient[i]) { // equivalent to !serverClient[i].connected()
        serverClient[i] = server.available();
        break;
      }

  if (i == MAX_SRV_CLIENTS) {
      server.available().println("busy");
     }
  }



  // here we have a connected serverClient

  for (int i = 0; i < MAX_SRV_CLIENTS; i++)
    while (serverClient[i].available() && Serial.availableForWrite() > 0) {
       buf1[i1] = (uint8_t)serverClient[i].read(); // read char from serverClient 
       if(i1<bufferSize-1) i1++;
    }
    Serial.write(buf1, i1);
    i1 = 0;
  
  if(Serial.available()) {

    // read the data until pause:
    
    while(1) {
      if(Serial.available()) {
        buf2[i2] = (char)Serial.read(); // read char from UART
        if(i2<bufferSize-1) i2++;
      } else {
        //delayMicroseconds(packTimeoutMicros);
        delay(packTimeout);
        if(!Serial.available()) {
          break;
        }
      }
    }
    
    // now send to WiFi:
    for (int i = 0; i < MAX_SRV_CLIENTS; i++) {
    serverClient[i].write((char*)buf2, i2);
    }
    i2 = 0;
  }
  
}
