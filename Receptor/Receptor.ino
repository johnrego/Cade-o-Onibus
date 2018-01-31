#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial gps(2 , 3);
char ch;
String msg = "";
int rssi;

void setup(){
  //pinMode(7, OUTPUT); 
  //digitalWrite(7, HIGH); //O pino en (enable) deve estar em nivel alto
  pinMode(9, INPUT); //Pino de leitura do RSSI PWM
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
        decodifica(msg); //latitude;longitude;numero de satelite;potencia de recepção
        rssi = pulseIn(9, LOW, 200);
        Serial.println(((rssi+5928)/41)*(-1));
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
  Serial.print(line.substring(46, 48).toInt());
  Serial.print(';');
}

