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
  myNextion.init();

}

void loop() {

  myNextion.setComponentText("t0", "Hello");
  delay(1000);
  int value = 1234;
  myNextion.setComponentText("t0", String(value));
  delay(1000);
  
}

