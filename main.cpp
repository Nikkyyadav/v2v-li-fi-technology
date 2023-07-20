#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SoftwareSerial TXSerial(4,5);
int buz=8;
int sw1 = A0;
int sw2 = A1;
int sw3 = A2;
unsigned long previousMillis=0;
char rec=0;
void setup()
{
pinMode(sw1, INPUT);
pinMode(sw2, INPUT);
pinMode(sw3, INPUT);
digitalWrite(sw1, HIGH);
digitalWrite(sw2, HIGH);
digitalWrite(sw3, HIGH);
pinMode(buz, OUTPUT);
digitalWrite(buz, LOW);
Serial.begin(9600);
Serial.println("Vehicle To Vehicle Communication Using LiFi");
lcd.begin(16, 2);
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("Vehicle To Vehi.");
lcd.setCursor(0, 1);
lcd.print(" Communication ");
delay(3000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(" Using LiFi ");
delay(3000);
lcd.clear();
previousMillis = millis();
TXSerial.begin(400);
}
void loop()
{
read_data();
Send_data();
if(millis() - previousMillis > 5000)
{
lcd.setCursor(0, 0);
lcd.print("Please wait.....");
lcd.setCursor(0, 1);
lcd.print(" ");
}
}
void buzzer_on()
{
digitalWrite(buz, HIGH);
}
//*********************************************
void buzzer_off()
{
digitalWrite(buz, LOW);
}
void read_data()
{
if(TXSerial.available() != 0)
{
rec = TXSerial.read();
if(rec=='A')
{
digitalWrite(buz, HIGH);
lcd.clear();
lcd.print(" Police Alert!! ");
lcd.setCursor(0, 1);
lcd.print(" Stop the car. ");
delay(2000);
digitalWrite(buz, LOW);
previousMillis = millis();
}
if(rec=='B')
{
digitalWrite(buz, HIGH);
lcd.clear();
lcd.print("Slow Down!! You.");
lcd.setCursor(0, 1);
lcd.print("are overspeeding");
delay(2000);
digitalWrite(buz, LOW);
previousMillis = millis();
}
if(rec=='C')
{
digitalWrite(buz, HIGH);
lcd.clear();
lcd.print(" Emergency case ");
lcd.setCursor(0, 1);
lcd.print(" Give Me Side. ");
delay(2000);
digitalWrite(buz, LOW);
previousMillis = millis();
}
}
}
void Send_data()
{
if(digitalRead(sw1)==LOW)
{
delay(100);
if(digitalRead(sw1)==LOW)
{TXSerial.print("A");}
//buzzer_on();
while(digitalRead(sw1)==LOW);
//buzzer_off();
}
if(digitalRead(sw2)==LOW)
{
delay(100);
if(digitalRead(sw2)==LOW)
{TXSerial.print("B");}
//buzzer_on();
while(digitalRead(sw2)==LOW);
//buzzer_off();
}
if(digitalRead(sw3)==LOW)
{
delay(100);
if(digitalRead(sw3)==LOW)
{TXSerial.print("C");}
//buzzer_on();
while(digitalRead(sw3)==LOW);
// buzzer_off();}}
