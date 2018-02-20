#include <SD.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

const int led1 = 2; 
const int sd = 10;
const int btn1 = 3;

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

String cache2[] = {
  "632a56afh" ,
  "7dsf32c57" ,
  "ds5gb2n21" ,
  "kzb2345sf" ,
  "532b55654" ,
  "ast5435nw" ,
  "ds453b52fg" ,
  "msr46ma245" ,
  "sda4b35ygw" ,
  "asd52una24"
};

LiquidCrystal_I2C lcd(0x27,16,2);
File pfs;
 
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(led1,OUTPUT);
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
    delay(500);
    RemoveCache();
    delay(500);
    GeneratePass();
    delay(3100);
    b=false;
  }
}

void ShowProcess()
{
    digitalWrite(led1,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
    delay(500);
    digitalWrite(led1,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
}

void GeneratePass()
{
      String pasik = cache[i];
      SendPass(pasik);
}
void RemoveCache()
{
  if(SD.exists("DAT1.txt"))
  SD.remove("DAT1.txt");
}

void SendPass(String pasik){
  pfs = SD.open("dat1.txt",FILE_WRITE);
  delay(100);
  if(pfs)
  {
  ShowProcess();
  pfs.print(pasik);
    delay(500);
  ShowProcess();
  pfs.close();
  }
  delay(500);
  ShowProcess();
  lcd.setCursor(3,0);
  lcd.print("Password: ");
  lcd.setCursor(3,1);
  lcd.print(cache2[i]);
}

