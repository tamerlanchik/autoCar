#include "DigitalOutShield.h"

DigitalOutShield::DigitalOutShield(unsigned char blocksCount, unsigned char signalPin){
  this->SS = signalPin;
  this->count = blocksCount;
  this->LOCK = 0;
}

DigitalOutShield::DigitalOutShield(unsigned char blocksCount, unsigned char signalPin, unsigned char lock_pin){
  this->SS = signalPin;
  this->count = blocksCount;
  this->LOCK = lock_pin;
}

void DigitalOutShield::init(){
  Serial.begin(9600);
  pinMode(SS, OUTPUT);
  values = new bool[8*this->count];
  for(int i=0; i<8*(this->count); i++){
    values[i] = 0;
  }
  SPI.begin();

  if(LOCK){
    pinMode(LOCK, OUTPUT);
    writeSPI(0);    //обнулить выходы регистра
    digitalWrite(LOCK, 1); //включить выходы регистра
  }
}

bool DigitalOutShield::write(unsigned char pin, bool value){
  if(add(pin, value)){
    return writeShift();
  }
  else{
    return false;
  }
}

bool DigitalOutShield::write(byte value){
  writeSPI(value);
}

bool DigitalOutShield::writeShift(){
  byte data;
  for(int i=this->count-1; i>=0; i--){
    data=0;
    for(int j=7; j>=0; j--){
      data=data<<1;
      data = data|values[i*8+j];
      Serial.print(values[i*8+j], BIN);
    }
    Serial.println();
    writeSPI(data);
  }
  return true;
}

void DigitalOutShield::writeSPI(byte data){
  digitalWrite(SS, LOW);
  SPI.transfer(data);
  digitalWrite(SS, HIGH);
}

bool DigitalOutShield::add(unsigned char pin, bool value){
  if(pin<0 || pin >= (this->count*8)){
    return false;
  }
  values[pin] = value;
  return true;
}

bool DigitalOutShield::send(){
  return writeShift();
}

void DigitalOutShield::attach(){
  if(LOCK)
    digitalWrite(LOCK, 1);
}

void DigitalOutShield::detach(){
  if(LOCK)
    digitalWrite(LOCK, 0);
}

//Значение filler по умолчанию: 0
void DigitalOutShield::zeroBuffer(bool filler){
  for(int i=0; i<8*count; i++){
    values[i] = filler;
  }
}
