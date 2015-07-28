/*

Find your touch events name

Fist of all you need to know what is your button name(ID in ASCII)

Itead NX4827T043_011
Similar http://imall.itead.cc/nextion-nx2432t043.html

Ricardo Mena C
ricardo@crcibernetica.com
http://crcibernetica.com

  This example code is in public domain

*/

#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial nextion(2, 3);//ARDUINO(RX, TX)->NEXTION LCD(TX, RX)

Nextion myNextion(nextion, 9600);



void setup() {
  Serial.begin(9600);
  nextion.begin(9600);

}

void loop() {
  String touchComponent = myNextion.listenNextion(100);//Set a time out to listen in serial port
  if(touchComponent != ""){//Ensure that your commponnet have someting
    Serial.println(touchComponent);    
  }
  delay(1000);//Just for an easy read

  /*
  When you know your touch Event name(Touch Press Event, Touch Release Event)
  save them, for example: #define BUTTON "65 0 1 1 ffff ffff ffff"

  What means all that number?
  65 PageID ComponentID TouchEvent End 
  */

}
