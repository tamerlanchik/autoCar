#include "Indication.h"

Indication::Indication():lcd(0x27,16,2) {}

void Indication::initLCD()
{
    lcd.init();
    lcd.backlight();
    uint8_t fillRect[8] = {B00000, B11111, B11111, B11111, B11111, B11111, B11111, B00000};
    uint8_t degree[8] = {B00100, B01010, B01010, B00100, B00000, B00000, B00000, B00000};
    lcd.createChar(1, fillRect);
    lcd.createChar(2, degree);
}

int Indication::powd(int a, int b)const{
    int res=1;
    for(;b>0; b--)
        res*=a;
    return res;
}

void Indication::print(char message[], int size){
  lcd.clear();
  if(size>1){
    lcd.print(message[1]);
  }
  else{
    lcd.print("Error in Indicate.print()");
  }
}

void Indication::print(bool a){
  lcd.clear();
  lcd.print(a);
}

void Indication::updateLCD(int data[], int len){
    lcd.clear();
    //Motors values
    lcd.setCursor(0, 0);
    lcd.print("M");
    lcd.setCursor(2, 0);
    lcd.print(data[0]);
    lcd.setCursor(5, 0);
    lcd.print("|");
    lcd.print(data[1]);
    //Borders values
    lcd.setCursor(11, 0);
    lcd.print("B");
    for(char i=0; i<4; i++){
        lcd.setCursor(12+(i%2)*3, i/2);
        lcd.print("|");
    }
    for(int i=0; i<4; i++){
        if( (data[2] % (int)powd(10, i+1) ) / (int)powd(10, i)){
            lcd.setCursor(13+i%2, i/2);
            lcd.write(1);
        }
    }
    //Sonar angle+value
    lcd.setCursor(0, 1);
    lcd.print("S"); lcd.setCursor(2, 1);lcd.print(data[3]); lcd.write(2);
    if(data[4]<0) lcd.print("-");
    else          lcd.print(data[4]);
}

void Indication::setMovingFlagLED(bool flag){
    digitalWrite(movingFlagLED, flag);
}

void Indication::setScanningFlagLED(bool flag){
    digitalWrite(scanningFlagLED, flag);
}
