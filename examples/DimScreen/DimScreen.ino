/*

Ricardo Mena C
ricardo@crcibernetica.com
http://crcibernetica.com

  This example code is in public domain

*/

#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial nextion(2, 3);// Nextion TX to pin 2 and RX to pin 3 of Arduino

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

void setup() {
  Serial.begin(9600);
  myNextion.init(); // send the initialization commands for Page 0
}

void loop() {
  int brightness = analogRead(A0);
  int bright = map(brightness, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
  
}
