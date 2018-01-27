#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial gps(2 , 3);
char ch = 0;
String msg = "";

void setup(){
  //pinMode(7, OUTPUT); 
  //digitalWrite(7, HIGH); //O pino en (enable) deve estar em nivel alto
  Serial.begin(9600);
  gps.begin(9600);
}

void loop(){
  if(gps.available()){
    ch = gps.read();
    msg += ch;
    if(ch == 10){
      if(msg.indexOf("GGA,", 2) == 3){
        //Serial.print(msg);
        decodifica(msg); //latitude;longitude;numero de satelite
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
  char hlat = line.charAt(28);
  float lat = (line.substring(17, 19).toInt())+((line.substring(19, 27).toFloat())/60);
  if(hlat == 'S'){
    Serial.print(lat*(-1), 5);
  }
  else{
    Serial.print(lat, 5); 
  }
  Serial.print(';');
  /*
   * 03812.3879 E is the DDDMM.MMMM format
   * 038 --> degrees
   * 12 --> minutes
   * .3879 --> minutes equals to sec/60
   * decimal = degrees + minutes/60
   * decimal = 38 + (12.3879 / 60)      
   * decimal = 77.20646
   */
  char hlon = line.charAt(42);
  float lon = (line.substring(30, 33).toInt())+((line.substring(33, 41).toFloat())/60);
  if(hlon == 'W'){
    Serial.print(lon*(-1), 5);
  }
  else{
    Serial.print(lon, 5); 
  }
  Serial.print(';');
  Serial.println(line.substring(46, 48).toInt());
  /*
  //Medindo distancia até a UFERSA (-6.1066548,-38.1840574). Distancia = 3540
  double dist = ((acos(cos((90-lat)*M_PI/180)*cos((90-(-6.1066548))*M_PI/180)+sin((90-lat)*M_PI/180)*sin((90-(-6.1066548))*M_PI/180)*cos(fabs(((360+lon)*M_PI/180)-((360+(-38.1840574))*M_PI/180)))))*6371.004)*1000;
  Serial.print("Distancia ate a UFERSA: ");
  Serial.println(dist, 2);
  */
}

