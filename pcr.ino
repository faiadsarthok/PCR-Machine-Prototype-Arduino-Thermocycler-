#include "max6675.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);
int sO = 7;
int thermoCS = 5;
int thermoCLK = 6;
int c;

int i=1;
int j=0;
int k=0;

MAX6675 thermocouple(thermoCLK, thermoCS, sO);
unsigned long start, final, elapsed;

void setup() {
  Serial.begin(9600);

  //Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
  lcd.init();
  lcd.backlight();

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(12,HIGH);


}

void loop() {

  if(i==1){
    //Serial.println("start");
    lcd.setCursor(0, 0);
    lcd.print("initial   ");
    temp(50,30);
    while(k<3){
      /*Serial.print("cycle no.");
      Serial.println(k);*/
      lcd.setCursor(0, 0);
      lcd.print("cycle no, " + String(k));
      temp(50,10);
      temp(45,10);
      k=k+1;
    }
    //Serial.println("final");
    lcd.setCursor(0, 0);
    lcd.print("final    ");
    temp(45,30);
    i=0;
  }

  else if(i==0){
    /*Serial.print("C = "); 
    Serial.print(thermocouple.readCelsius());
    Serial.print(" F = ");
    Serial.println(thermocouple.readFahrenheit());
    delay(300);*/
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("C = "); 
    lcd.print(String(thermocouple.readCelsius())+" ");
    lcd.setCursor(0, 1);
    lcd.print(" F = ");
    lcd.print(String(thermocouple.readFahrenheit()));
    delay(300);

    //!!!!!! For the MAX6675 to update, you must delay AT LEAST 250ms between reads
  }
}

void temp(int th, int tt){
  int e=0;
  c=thermocouple.readCelsius();
  //Serial.print("C = "); 
  //Serial.println(c);
  while (c<th){
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    delay(300);
    c=thermocouple.readCelsius();
    lcd.setCursor(0,1);
    lcd.print(String(c)+"to"+String(th));
    //Serial.println(c);
    //Serial.println("heating");
  }
  while(c>th){
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    delay(300);
    c=thermocouple.readCelsius();
    lcd.setCursor(0,1);
    lcd.print(String(c)+"to"+String(th));
    //Serial.println(c);
    //Serial.println("cooling");
  }
  if(c>th-1 && c<th+1){
    start=millis();
    /*Serial.println(c);
    Serial.println("maintaining");*/
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
    while(e<tt){

      if (c>th){
        digitalWrite(13,LOW);
        delay(1000);
        digitalWrite(13,HIGH);
        
      }
      else if(c<th){
        digitalWrite(12,LOW);
        delay(1000);
        digitalWrite(12,HIGH);
        
      }
      delay(300);
      c=thermocouple.readCelsius();
      //Serial.println(c);
      final=millis();
      elapsed=final-start;
      e=int(elapsed)/1000;
      //Serial.println(e);
      lcd.setCursor(0,0);
      lcd.print("maintaining  ");
      lcd.setCursor(0,1);
      lcd.print(String(c)+" time"+String(e)+"s to "+ String(tt)+"s");
    }
  }
  delay(300);
  lcd.clear();
}

