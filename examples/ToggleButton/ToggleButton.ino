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

boolean button1State;
boolean button2State;

void setup() {
  Serial.begin(9600);
  myNextion.init(); // send the initialization commands for Page 0

}

void loop() {
  String message = myNextion.listen(); //check for message
  if (message == "65 0 2 0 ffff ffff ffff") {
    myNextion.buttonToggle(button1State, "b0", 0, 2);
  }
  if (message == "65 0 3 0 ffff ffff ffff") {
    myNextion.buttonToggle(button2State, "b1", 0, 2);
  }

}
