#include <TimerOne.h> 

const int trigPin = 2;
const int echoPin = 3; 
const int SER = 10;
const int LATCH = 11;
const int CLK = 12;
int dist = 1234;
const byte numbs[10] = { B11101011, B10001000, B10110011, B10111010, // 0 1 2 3
                         B11011000, B01111010, B01111011, B10101000, // 4 5 6 7
                         B11111011, B11111010};
const byte state0 = B00000001;
int readSonar(){
  dist=0;
  for (int i = 0; i<3; i++){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  dist += pulseIn(echoPin, HIGH)/58;}
  dist /= 3;
  return (dist);
}
void printN(){
  unsigned int temp = dist;
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
    delay(2);
   }

}
void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(SER, OUTPUT);
pinMode(LATCH, OUTPUT);
pinMode(CLK, OUTPUT);
Serial.begin(9600);
Serial.println("Hello");
Timer1.initialize(20000);
Timer1.attachInterrupt(printN);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(readSonar());
  printN();
  //delay(100);
}
