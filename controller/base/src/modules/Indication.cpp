#include "Indication.h"

Indication::Indication():lcd(0x27,16,2),lcdLatestUpd(0.0) {
  lcd.init();
  lcd.backlight();
  uint8_t fillRect[8] = {B00000, B11111, B11111, B11111, B11111, B11111, B11111, B00000};
  uint8_t degree[8] = {B00100, B01010, B01010, B00100, B00000, B00000, B00000, B00000};
  lcd.createChar(1, fillRect);
  lcd.createChar(2, degree);
  for(int i=0; i<7; i++)
  {
    preIndicationData[i]=0;
  }
  pinMode(movingFlagLED, OUTPUT);
  pinMode(scanningFlagLED, OUTPUT);
  Log->d("Init LCD");
  delay(500);
}

int Indication::powd(int a, int b)const{
    int res=1;
    for(;b>0; b--)
        res*=a;
    return res;
}

void Indication::print(const char message[]){
  lcd.clear();
  lcd.print(message);
  Log->d("Print LCD success");
}
void Indication::print(char message){
  lcd.clear();
  lcd.print(static_cast<int>(message));
  Log->d("Print LCD success");
}
void Indication::print(int message, int posx=0, int posy=0, bool isClear=1){
  if(isClear) {lcd.clear();}
  lcd.setCursor(posx, posy);
  lcd.print(message);
  Log->d("Print LCD success");
}
void Indication::print(int data[], int size){
  lcd.clear();
  lcd.print(data[0]);
  lcd.setCursor(0, 1);
  lcd.print(data[1]);
}
void Indication::print(bool a){
  lcd.clear();
  //lcd.print(a);
}
bool Indication::compare(int data1[], int data2[], int len)const {
  for(int i=0; i<len; i++){
    if(data1[i]!=data2[i]){
      return true;
    }
  }
  return false;
}

void Indication::copy(int origin[], int dest[], int len){
  for(int i=0; i<len; i++){
    dest[i]=origin[i];
  }
}
void Indication::updateLCD(int data[], int len){
  //Log->d("UpdateLCD - 1");
    if(millis()-lcdLatestUpd>100){
      //Log->d("UpdateLCD - 2");
      //Log->write(int(compare(data, preIndicationData, len)), 'd');
      //lcd.clear();
      //lcd.print(compare(data, preIndicationData, len));
      //copy(data, preIndicationData, len);
      //lcd.print(compare(data, preIndicationData, len));
      if(compare(data, preIndicationData, len)){
        //Log->d("UpdateLCd - 3");
      //if(true){
        //Log->d("updateLCD");
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
        lcd.setCursor(10, 0);
        lcd.print("B");
        /*for(char i=0; i<4; i++){
            lcd.setCursor(12+(i%2)*3, i/2);
            lcd.print("|");
        }*/
        for(int i=0; i<4; i++){
            lcd.setCursor(11+i%2, i/2);
            if( (data[2] % (int)powd(10, i+1) ) / (int)powd(10, i)){
                lcd.write(1);
            }
            else{
              lcd.print("-");
            }
        }
        //Sonar angle+value
        lcd.setCursor(0, 1);
        lcd.print("S"); lcd.setCursor(2, 1);lcd.print(data[3]); lcd.write(2);
        lcd.setCursor(6, 1);
        if(data[4]<0) lcd.print("-");
        else          lcd.print(data[4]);
        Log->d("LCD updated");
        lcdLatestUpd=millis();
        copy(data, preIndicationData, len);
      }
    }
    //
    lcd.setCursor(14, 0);
    lcd.print("^");
    lcd.print(data[5]);
    lcd.setCursor(14,1);
    lcd.print("*");
    lcd.print(data[6]);
}

void Indication::setMovingFlagLED(bool flag)const{
    digitalWrite(movingFlagLED, flag);
    //Log->d("sMFL()");
}

void Indication::setScanningFlagLED(bool flag)const{
    digitalWrite(scanningFlagLED, flag);
    //Log->d("sSFL()");
}
