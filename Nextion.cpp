/*
HMI Nextion Library
Itead NX4827T043_011
http://imall.itead.cc/nextion-nx2432t043.html

Bentley Born
bentley@crcibernetica.com

Ricardo Mena C
ricardo@crcibernetica.com


http://crcibernetica.com

 License
 **********************************************************************************
 This program is free software; you can redistribute it 
 and/or modify it under the terms of the GNU General    
 Public License as published by the Free Software       
 Foundation; either version 3 of the License, or        
 (at your option) any later version.                    
                                                        
 This program is distributed in the hope that it will   
 be useful, but WITHOUT ANY WARRANTY; without even the  
 implied warranty of MERCHANTABILITY or FITNESS FOR A   
 PARTICULAR PURPOSE. See the GNU General Public        
 License for more details.                              
                                                        
 You should have received a copy of the GNU General    
 Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.
                                                        
 Licence can be viewed at                               
 http://www.gnu.org/licenses/gpl-3.0.txt

 Please maintain this license information along with authorship
 and copyright notices in any redistribution of this code
 **********************************************************************************
 */

#include "Nextion.h"


Nextion::Nextion(SoftwareSerial &next, uint32_t baud): nextion(&next){
  nextion->begin(baud);
}

void Nextion::buttonToogleEvent(boolean &buttonState, String buttonId ,uint8_t picDefualtId, uint8_t picPressedId){
  String temp = "";
  if (buttonState) {
    temp = buttonId + ".picc="+String(picDefualtId);
    sendCommand(temp.c_str());
    temp = "ref "+buttonId;
    sendCommand(temp.c_str());
    buttonState = false;
  } else {
    temp = buttonId + ".picc="+String(picPressedId);
    sendCommand(temp.c_str());
    temp = "ref "+buttonId;
    sendCommand(temp.c_str());
    buttonState = true;
  }
}//end buttonPressed


uint8_t Nextion::buttonOnOff(String find_component, String unknown_component, uint8_t pin, int btn_prev_state){  
  uint8_t btn_state = btn_prev_state;
  if((unknown_component == find_component) && (!btn_state)){
    btn_state = 1;//Led is ON
    digitalWrite(pin, HIGH);
  }else if((unknown_component == find_component) && (btn_state)){
    btn_state = 0;
    digitalWrite(pin, LOW);
  }else{
    //return -1;
  }//end if
  return btn_state;
}

boolean Nextion::setComponentValue(String component, int value){
  String comp_val = component +".val=" + value;
  sendCommand(comp_val.c_str());
  boolean acki = ack();
  return acki;
}//set_component_value

boolean Nextion::ack(void){
  /* TODO cambiar el nombre de esta funcion por uno más apropiado
  y permitir detectar todos los tipos de retornos simples
  CODIGO+END
  */  
  uint8_t bytes[4] = {0};
  nextion->setTimeout(20);
  if (sizeof(bytes) != nextion->readBytes((char *)bytes, sizeof(bytes))){
    return false;
  }//end if  
  if((bytes[0]==0x00)&&(bytes[1]==0xFF)&&(bytes[2]==0xFF)&&(bytes[3]==0xFF)){
    return false;//Somethings goes wrong
  }//end if 
  return true;
}

const char* Nextion::_ack(void){
  /* TODO cambiar el nombre de esta funcio*/
  uint8_t bytes[4] = {0};
  nextion->setTimeout(20);
  if (sizeof(bytes) != nextion->readBytes((char *)bytes, sizeof(bytes))){
    return false;
  }//end if
  if((bytes[1]==0xFF)&&(bytes[2]==0xFF)&&(bytes[3]==0xFF)){
    switch (bytes[0]) {
	case 0x00:
	  return "0"; break;      
	case 0x01:
	  return "1"; break;
	case 0x03:
	  return "3"; break;
	case 0x04:
	  return "4"; break;
	case 0x05:
	  return "5"; break;
	case 0x1A:
	  return "1A"; break;
	case 0x1B:
	  return "1B"; break;
	default: 
	  return "-1";
    }//end switch
  }//end if
}//end *\

unsigned int Nextion::getComponentValue(String component){
  String get_value = "get "+ component +".val";
    unsigned int value = 0;
  sendCommand(get_value.c_str());
  uint8_t temp[8] = {0};
  nextion->setTimeout(20);
  if (sizeof(temp) != nextion->readBytes((char *)temp, sizeof(temp))){
    return 0;
  }//end if
  if((temp[0]==(0x71))&&(temp[5]==0xFF)&&(temp[6]==0xFF)&&(temp[7]==0xFF)){//
    value = (temp[4] << 24) | (temp[3] << 16) | (temp[2] << 8) | (temp[1]);
  }//end if
  return value;
}//get_component_value */

boolean Nextion::setComponentText(const char *component, const char *txt){
  String component_txt = String(component) + ".txt=\"" + String(txt) + "\"";
  sendCommand(component_txt.c_str());
  boolean acki = ack();
  return acki;
}//end set_component_txt */

String Nextion::listenNextion(unsigned long timeOut){
  //TODO separar todos los eventos 0x65 0x66 0x67 0x68
  String cmd="";
  uint8_t ff = 0;
  uint8_t i = 0;
  char buff[10] = {0};
  unsigned long start = millis();
  while((millis()-start < timeOut)){ //millis()-start < timeOut
    if(nextion->available()){
      char b = nextion->read();
      buff[i] = b;
      i++;
      if(String(b, HEX) == "ffff"){ff++;}
      cmd += String(b, HEX);
      if(ff == 3){
        ff = 0;
        break;
      }//end if
      cmd+=" ";
    }//end if
  }//end while
  if(cmd != ""){
#if defined(DEBIG)
	Serial.println(cmd);
    #endif
  }//end if
  flushSerial();
  return cmd;
}//end listen_nextion

void Nextion::sendCommand(const char* cmd){
  while (nextion->available()){
	nextion->read();
  }//end while
  nextion->print(cmd);
  nextion->write(0xFF);
  nextion->write(0xFF);
  nextion->write(0xFF);
}//end sendCommand

boolean Nextion::nextionInit(const char* pageId){
  String page = "page " + String(pageId);
  sendCommand("");
  sendCommand(page.c_str());
  delay(100);
  return ack();
}//end nextion_init

void Nextion::flushSerial(){
  Serial.flush();
  nextion->flush();
}//end flush

 
