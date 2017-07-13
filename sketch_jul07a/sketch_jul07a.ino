#include <Servo.h>
#include <TimerOne.h> 
//Servo servo;
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
  while (true){
    if (Serial.available())
    {
      temp = char(Serial.read());
      if (temp != stopper)
        data[i++] = temp;
      else
        break;
    }
  }
  unsigned int *j = new unsigned int;
  *j = 0;
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
}
void changeMoving(int numb)
{
  for(unsigned int i = 0; i<4; i++)
    digitalWrite(motor[i], moveTemp[numb][i]);
}
void printN(){
  unsigned int temp = distance;
  for(int j = 0; j<4; j++)
   {
    digitalWrite(LATCH, LOW);
    shiftOut(SER, CLK, MSBFIRST, ~(state0<<j));
    if (temp>0)
      shiftOut(SER, CLK, MSBFIRST, numbs[temp%10]);
    else
      shiftOut(SER, CLK, MSBFIRST, B00000000);
    digitalWrite(LATCH, HIGH);
    temp /= 10;
    delay(1);
   }

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
  //servo.attach(6);
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  //Timer1.initialize(15000);
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
void loop() {
  /*for(int i = 0; i<180; i+=10)
  {
    servo.write(i);
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW); 
    m = (pulseIn(echoPin, HIGH)/58);
    Serial.println(m);
    if (m <= border){
      changeMoving(1);
      digitalWrite(12, HIGH);}
    else
      {changeMoving(2);
      digitalWrite(12, LOW);}
    delay(15);
  }
  delay(100);
  servo.write(0);
  delay(300);*/
  /*do{
    distance = readSonar();
    delay(10);
    if (readSonar() - 
    Serial.println(distance);
    printN();
    changeMoving(3);
  }
  while (distance <= border);
  changeMoving(1);*/
  if (readSonar()<= border)
  {
    if (readSonar() <= border)
    {
      changeMoving(3);
    }
  }
  else
    changeMoving(1);
}
