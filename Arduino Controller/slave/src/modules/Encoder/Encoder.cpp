#include "Encoder.h"

Encoder::Encoder(float speed[]):measureTime(0){
  mSpeed = speed;
  for(unsigned int i=0; i<2; i++){
    precountAlert[i] = 0;
    counterAlert[i] = 0;
    lastTimeMeasured[i] = 0;
    moved[i] = 0;
  }
}

void Encoder::handleEvent(unsigned char code){
  if(millis()-lastTimeMeasured[code] > 0){
    /*if(code==1){
      Serial.print(counterAlert[code]%40);
      Serial.print(" ");
      Serial.println(millis()-lastTimeMeasured[code]);
    }*/
    counterAlert[code]++;
    moved[code] = 1;
    lastTimeMeasured[code]=millis();
    /*Serial.print(code);
    Serial.print(" ");
    Serial.println(counterAlert[code]);*/
  }
}

void Encoder::calcSpeed(){
  if(millis()-measureTime > 500){
    for(unsigned int i = 0; i<2; i++){
        mSpeed[i] = (dL * (counterAlert[i] - precountAlert[i])) / (millis() - measureTime);
        mSpeed[i] /= 2;
        mSpeed[i] *= 1000;
        //Serial.println((float)(1000 * dL * (counterAlert[i] - precountAlert[i]))/ (millis() - measureTime));
        /*Serial.print((millis() - measureTime));
        Serial.print(" ");
        Serial.println((counterAlert[i] - precountAlert[i]));*/
        precountAlert[i] = counterAlert[i];
    }
    measureTime = millis();
    /*Serial.print(speed[0]);
    Serial.print(" ");
    Serial.println(speed[1]);*/
  }
}

unsigned long Encoder::test(){
  return 0;
}
