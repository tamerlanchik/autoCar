#include <Servo.h>
#include <TimerOne.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

const char bord[4] = {0, 1, 2, 3};  //analog
const int relay = 2;
const int ser = 3;
const int trigPin = 4;
const int echoPin = 5; 
const int servo1 = 6;
const char motor[4]= {7, 8, 9, 10};
const char alarm = 11;
const int latch = 12;
const int clk = 13;

const float border = 15;  //in santimetres
const char moveTemp[5][4] = {   {0, 0, 0, 0}, {1, 0, 0, 1}, {0, 1, 1, 0}, {1, 0, 1, 0}, {0, 1, 0, 1} };
const byte numbs[10] = { B11101011, B10001000, B10110011, B10111010, // 0 1 2 3
                         B11011000, B01111010, B01111011, B10101000, // 4 5 6 7
                         B11111011, B11111010};
const byte state0 = B00000001;
unsigned int distance = 1;
bool direct = true;

int gaz, rot;
float m;

void serialEvent()
{
  unsigned char temp;
  const unsigned char stopper = '$';
  unsigned char *data = new unsigned char [30];
  unsigned int i = 0;
  lcd.clear();
  lcd.print("Received");
    while (Serial.available())
    {
      temp = char(Serial.read());
      if (temp != stopper)
        data[i++] = temp;
      else
        break;
    }
  unsigned int *j = new unsigned int;
  *j = 0;
  if (data[0] == '@'){
    lcd.print("Rescan");
    rescan();
  }
  else{
    lcd.clear();
    for(int j = 0; j<i; j++)
      lcd.print(data[j]);
    while (data[*j]!='/'){
      if (data[*j] == '-')
        rot *= -1;
      else
        rot *= 10 + (data[*j++]-'0');
    }
    *j++;
    while (*j <= i){
      if (data[*j] == '-')
        gaz *= -1;
      else
        gaz *= 10 + (data[*j++]-'0');
    }
    delete j;
    delete [] data;
  
    if (gaz == 0 && rot == 0)
    {
      changeMoving(0);
    }
    else if (gaz > 0) {
     changeMoving(1);
    }
    else if (gaz < 0) {
     changeMoving(2);
    }
    else if (rot > 0) {
     changeMoving(3);
    }
    else if (rot < 0) {
     changeMoving(4);
    }
    servo.attach(gaz);}
}
void changeMoving(int numb)
{
  for(unsigned int i = 0; i<4; i++)
    digitalWrite(motor[i], moveTemp[numb][i]);
}
void printN(){
  lcd.clear();
  lcd.print(distance);
}
int readSonar(){
  int dist = 0;
  for (int i = 0; i<10; i++){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  dist += pulseIn(echoPin, HIGH)/58;
  }
  return (dist/10);
}
void strike()
{
  //direct = !direct;
  //changeMoving(0);
  Serial.println("STRIKE");
  //changeMoving(0);
  //delay(5000);
}
void setup() {
  /*for(char i = 2; i<14; i++)
  {
    if (i!= 5 || i!=6)
      pinMode(i, OUTPUT);
  }
  pinMode(5, INPUT); //trigPin
  servo.attach(servo1);
 
  changeMoving(2);
  tone(alarm, 1000);
  delay(400);*/
  servo.attach(6);
  servo.write(50);
  tone(alarm, 1000);
  //digitalWrite(relay, HIGH);
}
/*
moving template:
  1) Stop:  {0, 0, 0, 0}
  2) Move Forvard: {1, 0, 1, 0]
  3) Move Backward: {0, 1, 0, 1}
  4) Rotate Left: {1, 0, 0, 1}
  5) Rotate Right: {0, 1, 1, 0}
 
 
 */
void rescan()
{
  servo.write(0);
  delay(300);
  for (int i = 0; i<=180; i+=20)
  {
    servo.write(i);
    delay(100);
    //Serial.print(i);
    //Serial.print('/');
    Serial.println(readSonar());
    delay(2);
    //Serial.print('$');
  }
  delay(100);
  Serial.println('%');
}
void borderWatcher()
{
  if (!(digitalRead(bord[0]) && digitalRead(bord[1])) && (digitalRead(bord[2]) && digitalRead(bord[3]))){       //strike forvard
    changeMoving(1);
    direct = 1;
  }
  else if (!(digitalRead(bord[2]) && digitalRead(bord[3])) && (digitalRead(bord[0]) && digitalRead(bord[1]))) {  //strike backward 
    changeMoving(2);
    direct = 0;
  }
  else if (!digitalRead(bord[0]) || !digitalRead(bord[1]) || !digitalRead(bord[2]) || !digitalRead(bord[3]))
    {
      tone(alarm, 500, 200);
      changeMoving(0);
    }
  else delay(100);
  delay(100);
}
void loop() {
  //borderWatcher();   
  rescan(); 
}
