#include <Servo.h>
#include <TimerOne.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;
const int echoPin = 9; 
const int trigPin = 8;
const char motor[4]= {2, 3, 4, 5};
const char bord[4] = {6, 7, 8, 9};
const float border = 15;
const int SER = 10;
const int LATCH = 11;
const int CLK = 12;
//const char joy[2] = {A0, A1};
//int zeroJ[2];
int gaz, rot;
float m;
const char moveTemp[5][4] = {   {0, 0, 0, 0}, {1, 0, 0, 1}, {0, 1, 1, 0}, {1, 0, 1, 0}, {0, 1, 0, 1} };
const byte numbs[10] = { B11101011, B10001000, B10110011, B10111010, // 0 1 2 3
                         B11011000, B01111010, B01111011, B10101000, // 4 5 6 7
                         B11111011, B11111010};
const byte state0 = B00000001;
unsigned int distance = 1;
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
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  for(char i = 0; i<4; i++)
  {
    pinMode(motor[i], true);
    pinMode(bord[i*2], INPUT);
    pinMode(bord[(i+1)*2], INPUT);
    //zeroJ[i] = analogRead(joy[i]);
  }
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(12, OUTPUT);
  servo.attach(6);
  servo.write(50);
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  //Timer1.initialize(30000);
  //Timer1.attachInterrupt(printN);
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
  delay(400);
  for (int i = 0; i<130; i+=20)
  {
    servo.write(i);
    delay(10);
    Serial.print(i);
    Serial.print('/');
    Serial.println(readSonar());
    delay(2);
    //Serial.print('$');
  }
  delay(100);
  Serial.println('%');
}
void loop() {
  /*for (int i = 0; i<180; i+=5)
  {
    servo.write(i);
    delay(300);
    Serial.print(i);
    Serial.print('/');
    Serial.println(readSonar());
  }*/
  /*if (readSonar()<= border)
  {
    if (readSonar() <= border)
    {
      changeMoving(3);
      
    }
  }
  else
    changeMoving(1);*/
    
}
