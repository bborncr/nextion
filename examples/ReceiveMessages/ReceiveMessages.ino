/*

Ricardo Mena C
ricardo@crcibernetica.com
http://crcibernetica.com

  This example code is in public domain

*/

#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial nextion(2, 3);//ARDUINO(RX, TX)->NEXTION LCD(TX, RX)

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

void setup() {
  Serial.begin(9600);
  nextion.begin(9600);
  myNextion.nextionInit("0"); // send the initialization commands for Page 0

}

void loop() {
  String message = myNextion.listenNextion(100); //check for message, timeout is 100mS
  if(message != ""){ // if a message is received...
    Serial.println(message); //...print it out
  }
}
