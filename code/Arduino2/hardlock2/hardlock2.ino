#include <SD.h>
#include <SPI.h>
#include <Wire.h> 

const int led1 = 5;
const int led2 = 8;
const int btn1 = 7;
const int sd = 10;

int i = -1;
bool b = false;

String cache[] = {
  "1" ,
  "2" ,
  "3" ,
  "4" ,
  "5" ,
  "6" ,
  "7" ,
  "8" ,
  "9" ,
  "10"
};

File pfs;
 
void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(btn1,INPUT);
}
 
void loop(){

  if(i==10) i=0;
 if(SD.begin(sd))
   {
    ShowProcess();
   }
  if(digitalRead(btn1) == HIGH && !b){
    b = true;
    i++;
    digitalWrite(led2,LOW);
    digitalWrite(led1,LOW);
    delay(500);
    CheckPass();
    delay(1500);
    b=false;
  }
}

void ShowProcess()
{
    digitalWrite(led1,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
    delay(200);
    digitalWrite(led2,HIGH);
    delay(500);
    digitalWrite(led2,LOW);
}

void CheckPass()
{
      String pasik = cache[i];
      SendPass(pasik);
}

void SendPass(String pasik){
  pfs = SD.open("DAT1.txt");
  delay(100);
  if(pfs)
  {
    String pasik2 = "";
    while (pfs.available()) {
           pasik2 = Serial.write(pfs.read());
          }
        CheckRes(pasik2);
  delay(100);
  pfs.close();
  }
}

void CheckRes(String pasik){
  Serial.println(pasik);
  Serial.println(cache[i]);
  if(cache[i]==pasik) digitalWrite(led2,HIGH);
  else digitalWrite(led1,HIGH);
}

