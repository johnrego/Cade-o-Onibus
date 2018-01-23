#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial gps(2 , 3);
char ch = 0;
String msg = "";

void setup(){
  Serial.begin(9600);
  gps.begin(9600);
}

void loop(){
  if(gps.available()){
    ch = gps.read();
    msg += ch;
    if(ch == 10){
      if(msg.indexOf("GGA,", 2) == 3){
        Serial.print(msg);
        decodifica(msg);
      }
      msg = "";
    }
  }
}

void decodifica(String line){
  /*
   * 0607.7118 E is the DDMM.MMMM format
   * 06 --> degrees
   * 07 --> minutes
   * .7118 --> minutes equals to sec/60
   * decimal = degrees + minutes/60
   * decimal = 06 + (07.7118 / 60)      
   * decimal = 06.12853
   */
  Serial.print("Latitude: ");
  Serial.print(line.substring(17, 27));
  Serial.print(" ");
  Serial.println(line.substring(28, 29));
  /*
   * 03812.3879 E is the DDDMM.MMMM format
   * 038 --> degrees
   * 12 --> minutes
   * .3879 --> minutes equals to sec/60
   * decimal = degrees + minutes/60
   * decimal = 38 + (12.3879 / 60)      
   * decimal = 77.20646
   */
  Serial.print("Longitude: ");
  Serial.print(line.substring(30, 41));
  Serial.print(" ");
  Serial.println(line.substring(42, 43));
  Serial.print("Numero de Satelites: ");
  Serial.println(line.substring(46, 48));
}

