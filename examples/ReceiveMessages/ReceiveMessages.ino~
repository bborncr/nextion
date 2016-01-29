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
  String message = myNextion.listen(); //check for message
  if(message != ""){ // if a message is received...
    Serial.println(message); //...print it out
  }
  int value = analogRead(A0);
  String data = "add 3,0," + String(value);
  myNextion.sendCommand(data.c_str());
 // myNextion.sendCommand("ref S0");
  delay(1000);
  
}
