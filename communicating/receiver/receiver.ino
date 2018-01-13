#include <SPI.h>
#include <RF24.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
RF24 radio(9, 10);
const uint32_t pipe = 123456789;

byte massiv[4];

void setup()   
{
  lcd.init();                     
  lcd.backlight();
  pinMode(6, OUTPUT);
  Serial.begin(57600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS); // RF24_1MBPS или RF24_2MBPS
  radio.openReadingPipe(1,pipe); // открыть канал на приём
  radio.startListening(); // приём
}


void loop()  
{
  if(radio.available())
    {
      radio.read(massiv, 1);
      Serial.println(massiv[0]);    
      lcd.clear();
      lcd.print(massiv[0]);   
    }
}
