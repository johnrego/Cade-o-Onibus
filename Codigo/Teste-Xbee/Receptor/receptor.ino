#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial xbee(2 , 3);
char ch;

void setup(){
  Serial.begin(9600);
  xbee.begin(9600);
}

void loop(){ 
  if (xbee.available() > 0) {
    //delay(2);
    ch = xbee.read();  
    Serial.print(ch);
  }
}
