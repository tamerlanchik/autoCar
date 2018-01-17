#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <pins.h>
class Indication{
private:
    //bool isMovingFlag;
    //bool isScanningFlag;

    LiquidCrystal_I2C lcd;
public:
    Indication():lcd(0x27,16,2) {
      }
    void initLCD(){
      uint8_t a[8] = {B00000, B11111, B11111, B11111, B11111, B11111, B11111, B00000};
      uint8_t b[8] = {B00100, B01010, B01010, B00100, B00000, B00000, B00000, B00000};
      lcd.init();
      lcd.backlight();
      lcd.createChar(1, a);
      lcd.createChar(2, b);
    }
    void updateLCD(int data[], int len){
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
        for(char i=0; i<4; i++){
            if((data[2]%(int)pow(10, i+1))/(int)pow(10, i)){
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
    void setMovingFlagLED(bool flag){
        digitalWrite(movingFlagLED, flag);
    }
    void setScanningFlagLED(bool flag){
        digitalWrite(scanningFlagLED, flag);
    }
};
