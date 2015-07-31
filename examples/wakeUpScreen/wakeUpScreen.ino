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

boolean screenOff = true;

void setup() {
  Serial.begin(9600);
  myNextion.init(); // send the initialization commands for Page 0

}

void loop() {
  if(screenOff){
    screenOff = false;
    myNextion.sendCommand("sleep=1");
  }
  
  String message = myNextion.listen(); //check for message
  if(message.startsWith("68")){
    myNextion.sendCommand("sleep=0");
  }
}
