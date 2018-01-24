#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial xbee(2 , 3);

void setup(){
  Serial.begin(9600);
  xbee.begin(9600); //AT+RST
}

void loop(){ 
  Serial.println("Teste");
  xbee.println("Teste");
  delay(2000);
}
