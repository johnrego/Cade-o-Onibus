#include "math.h"
#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial gps(2 , 3);

char ch;
boolean mode;
unsigned int pwm;
void setup(){
  Serial.begin(9600);
  gps.begin(9600);
  pinMode(6, INPUT);
  mode = false;
}

void loop(){
  /*
  if(Serial.available()){
    delay(2);
    ch = Serial.read();    
    gps.print(ch);
  }
  if(gps.available()){
    ch = gps.read();    
    Serial.print(ch);
  }
  */
  
  if(Serial.available()){
    delay(2);
    ch = Serial.read();    
    if(ch == 'a'){
      if(!mode){
        gps.print("+++");
        delay(1200); 
      }
      amostra(1);
      pwm = pulseIn(6, HIGH, 200);
      Serial.println(pwm);
    }
    if(ch == 'b'){
      mode = !mode;
    }
  }
  if(gps.available()){
    ch = gps.read();
  }
  if(mode){
    gps.println("AT");
    delay(30);
    descarta();
  }
}

void amostra(int qnt){
  char dbm[2];
  unsigned int parcial[qnt];
  descarta();
  for(int i=0;i<qnt;i++){
    parcial[i] = 1;
    gps.println("ATDB");
    delay(25);
    if(gps.available()){
      for(int j=0;j<2;j++){
        dbm[j] = gps.read();
        switch(dbm[j]){
          case '0':
            parcial[i] += 0;
          break;
          case '1':
            parcial[i] += pow(16, abs(j-1));
          break;
          case '2':
            parcial[i] += 2*pow(16, abs(j-1));
          break;
          case '3':
            parcial[i] += 3*pow(16, abs(j-1));
          break;
          case '4':
            parcial[i] += 4*pow(16, abs(j-1));
          break;
          case '5':
            parcial[i] += 5*pow(16, abs(j-1));
          break;
          case '6':
            parcial[i] += 6*pow(16, abs(j-1));
          break;
          case '7':
            parcial[i] += 7*pow(16, abs(j-1));
          break;
          case '8':
            parcial[i] += 8*pow(16, abs(j-1));
          break;
          case '9':
            parcial[i] += 9*pow(16, abs(j-1));
          break;
          case 'A':
            parcial[i] += 10*pow(16, abs(j-1));
          break;
          case 'B':
            parcial[i] += 11*pow(16, abs(j-1));
          break;
          case 'C':
            parcial[i] += 12*pow(16, abs(j-1));
          break;
          case 'D':
            parcial[i] += 13*pow(16, abs(j-1));
          break;
          case 'E':
            parcial[i] += 14*pow(16, abs(j-1));
          break;
          case 'F':
            parcial[i] += 15*pow(16, abs(j-1));
          break;
          default:
            //dbm[0] = '0';
            //dbm[1] = '0';
            parcial[i] = 0;
          break;                  
        }
      }
      descarta();
      for(int k=0;k<2;k++){
        Serial.print(dbm[k]);
      }
      Serial.print(';');
      Serial.print(parcial[i]);
      Serial.print(';');
    }    
  }
}

void descarta(){
  char ch;
  while(gps.available()){
    ch = gps.read();
  }  
}

