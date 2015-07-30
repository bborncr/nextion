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

// sensor "progress" bar
int x = 56;
int y = 321;
int width = 195;
int height = 8;

int old_sensor_value = 0;

void setup() {
  Serial.begin(9600);
  myNextion.init();

}

void loop() {
  int sensor = analogRead(A0);
  if (abs(sensor - old_sensor_value) > 20) {
  old_sensor_value = sensor;
  
  int scaled_value = map(sensor, 0, 1023, 0, 100); // always map value from 0 to 100
  
  myNextion.updateProgressBar(x,y,width,height,scaled_value,0,2); // update the progress bar
  myNextion.setComponentText("t0", String(sensor));  // update text using original sensor value
  
  }
  delay(100);
}
