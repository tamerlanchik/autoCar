#include "Indication.h"

Indication::Indication():lcd(0x27,16,2),lcdLatestUpd(0),preIndicationData() {
  lcd.init();
  lcd.backlight();
  uint8_t fillRect[8] = {B00000, B11111, B11111, B11111, B11111, B11111, B11111, B00000};
  uint8_t degree[8] = {B00100, B01010, B01010, B00100, B00000, B00000, B00000, B00000};
  lcd.createChar(1, fillRect);
  lcd.createChar(2, degree);
  pinMode(movingFlagLED, OUTPUT);
  pinMode(scanningFlagLED, OUTPUT);
  Log->d("Init LCD");
}

/*void Indication::print(const char message[]){
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
}*/
void Indication::print(void* data, char mode){
  lcd.print("N");
  /*if(millis()-lcdLatestUpd>lcdUpdateTimeout){
    printEmerge(data, mode);
  }*/
}
void Indication::print(String message){
  if(millis()-lcdLatestUpd>lcdUpdateTimeout){
    lcd.clear();
    lcd.print(message.c_str());
  }
  //lcd.print("J");
}

void Indication::printEmerge(void* data, char mode){
  lcd.clear();
  switch(mode)
  {
    case 'd': lcd.print(*((int*)data)); break;
    case 'c': lcd.print(*((char*)data)); break;
    case 's': lcd.print((char*)data); break;
    case 'b': lcd.print(*((bool*)data)); break;
    default:
      lcd.print("Wrong mode");
      Log->e("Wrong ind.prt mode");
      break;
  }
  lcdLatestUpd = millis();
}

void Indication::updateLCD(Indication_template data, bool isEmerge){
  if(millis()-lcdLatestUpd>100){
    if(data.compare(&preIndicationData)){
        lcd.clear();

        //Motors values
        lcd.setCursor(0, 0);
        lcd.print("M");
        lcd.setCursor(2, 0);
        lcd.print(data.motors[0]);
        lcd.setCursor(5, 0);
        lcd.print("|");
        lcd.print(data.motors[1]);

        //Borders values
        lcd.setCursor(10, 0);
        lcd.print("B");
        for(byte i = 0; i<4; i++){
          lcd.setCursor(11+i%2, i/2);
          if(data.borders[i]){
            lcd.print("-");
          }
          else{
            lcd.write(1);
          }
        }
        /*for(int i=0; i<4; i++){
            lcd.setCursor(11+i%2, i/2);
            if( (data[2] % (int)powd(10, i+1) ) / (int)powd(10, i)){
                lcd.write(1);
            }
            else{
              lcd.print("-");
            }
        }*/

        //Sonar angle+value
        lcd.setCursor(0, 1);
        lcd.print("S"); lcd.setCursor(2, 1);lcd.print(data.sonarAngle); lcd.write(2);
        lcd.setCursor(6, 1);
        lcd.print(data.sonarValue);

        Log->d("LCD updated");
        lcdLatestUpd=millis();
        preIndicationData.copy(&data);
      }
    }
    //
    lcd.setCursor(14, 0);
    lcd.print("^");
    lcd.print((int)data.scanState);
    lcd.setCursor(14,1);
    lcd.print("*");
    lcd.print((int)data.signalState);
}

void Indication::setMovingFlagLED(bool flag)const{
    digitalWrite(movingFlagLED, flag);
}

void Indication::setScanningFlagLED(bool flag)const{
    digitalWrite(scanningFlagLED, flag);
}
