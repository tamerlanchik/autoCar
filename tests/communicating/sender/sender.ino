
#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10); // можно использовать любые
const uint32_t pipe = 123456789; // адрес
byte massiv[10];
char temp;
byte* i;
void setup()
{
  massiv[0] = 1;
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
  radio.openWritingPipe(pipe); // открыть канал на отправку
}


void loop()   
{
   /*massiv[0]+=1;
   radio.write(massiv, 1);
   delay(500);*/
  if (Serial.available()){
  massiv[0] = Serial.read();
  radio.write(massiv, 1);}
  
}
