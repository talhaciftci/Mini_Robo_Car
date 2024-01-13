#include<SoftwareSerial.h>
SoftwareSerial bt_iletisim(0,1);
#define sol_ileri 10
#define sol_geri 9
#define sol_hiz 11
#define echoPin 2
#define trigPin 3
#define sag_ileri 7
#define sag_geri 8
#define sag_hiz 6
int maximumRange = 35;
int minimumRange = 0;
int okunan_deger = 0;
int buzzerPin = 12;
int motorlar_hiz = 255;
int onled = 6; 
int onled1 = 7;
int geled = 11;
int geled1 = 8;
void setup()
{
  pinMode(sol_ileri, OUTPUT);
  pinMode(sag_ileri, OUTPUT);
  pinMode(sol_geri, OUTPUT);
  pinMode(sag_geri, OUTPUT);
  pinMode(sol_hiz, OUTPUT);
  pinMode(sag_hiz, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(onled, OUTPUT);
  pinMode(onled1, OUTPUT);
  pinMode(geled, OUTPUT);
  pinMode(geled1, OUTPUT);   
  Serial.begin(9600);
  bt_iletisim.begin(9600);
}
void loop()
{   
  int olcum = mesafe(maximumRange, minimumRange);
  melodi(olcum*5);
}
int mesafe(int maxrange, int minrange)
{
  long duration, distance;
  digitalWrite(trigPin,0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, 1);
  distance = duration / 25.2;
  delay(50);
  if(distance >= maxrange || distance <= minrange)
  return 0;
  return distance;
}
int melodi(int dly)
{
  tone(buzzerPin, 440);
  delay(dly);
  noTone(buzzerPin);
  delay(dly);
  if (bt_iletisim.available())
  {
    char data = bt_iletisim.read();
    Serial.println(data);
    if (data == 'F')
    {
      digitalWrite(onled1, 0);
      digitalWrite(buzzerPin, 0);
      ileri();    
    }
    else if (data == 'B')
    {
      digitalWrite(onled1, 0);
      digitalWrite(buzzerPin, 1);
      geri();
    } 
    else if (data == 'L')
    {
      sol();  
    } 
    else if (data == 'R')
    {
      sag();
    }
    else if (data == 'S')
    {
      dur();    
    }
    else if(data == 'V'){
     digitalWrite(onled1, 0);
     digitalWrite(buzzerPin, 1);
    }
    else if(data == 'v')
    {
      digitalWrite(onled1, 0);
      digitalWrite(buzzerPin, 0);
    }
    else if(data == 'O' ){
      digitalWrite(onled,1);
      digitalWrite(geled,1);
    }
    else if(data == 'A' ){
      digitalWrite(onled1,1);
      digitalWrite(geled1,1);
    }
  } 
}
void ileri()
{
  digitalWrite(sol_geri, 1);
  digitalWrite(sag_geri, 1);
  analogWrite(sol_hiz, motorlar_hiz);
  analogWrite(sag_hiz, motorlar_hiz);
}
void geri()
{
  digitalWrite(sol_ileri, 1);
  digitalWrite(sag_ileri, 1);
  analogWrite(sol_hiz, motorlar_hiz);
  analogWrite(sag_hiz, motorlar_hiz);
}
void sag()
{
  digitalWrite(sol_ileri, 1);
  digitalWrite(sag_geri, 1);
  analogWrite(sol_hiz, motorlar_hiz);
  analogWrite(sag_hiz, motorlar_hiz);
}
void sol()
{
  digitalWrite(sol_geri, 1);
  digitalWrite(sag_ileri, 1);
  analogWrite(sol_hiz, motorlar_hiz);
  analogWrite(sag_hiz, motorlar_hiz);
}
void dur()
{
  digitalWrite(sol_ileri, 0);
  digitalWrite(sol_geri, 0);
  digitalWrite(sag_ileri, 0);
  digitalWrite(sag_geri, 0);
  analogWrite(sol_hiz, 0);
  analogWrite(sag_hiz, 0);
}
