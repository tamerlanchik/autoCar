#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
const char motorJoys[2] = {2, 3};
const char sonarJoy = 2;
const char signalBut = 3;
const char scanBut = 4;
const char movingFlagLED = 5;
const char scanningFlagLED = 6;
const char epsM = 10;
const char epsS = 3;
class Joysticks{
private:
    int preMotorsVals[2];
    char preSonarAngle;
    int motorJoysNeutral[2];
    int sonarJoyNeutral;


public:
    bool getMotorsJoys(int val[]) {
        bool isChanged=false;
        for(char i=0; i<2; i++){
            val[i]=analogRead(motorJoys[i]);
            if(abs(val[i]-preMotorsVals[i])>epsM){
                isChanged = true;
                preMotorsVals[i] = val[i];
            }
        }
        return isChanged;
    }
    bool getSonarJoy(int val){
        bool isChanged=false;
        val=analogRead(sonarJoy);
        if(abs(val-preSonarAngle)>epsS){
            isChanged = true;
            preSonarAngle = val;
        }
        return isChanged;
    }
    bool getSonarState(void){
        return digitalRead(scanBut);
    }
    bool getSignalState(void){
        return digitalRead(signalBut);
    }

};
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
class Manager{
private:
    int motorVals[2];
    int sonarAngle;
    bool isScanningFlag;
    bool isSignallingFlag;
    bool isMovingFlag;
    int sensorData[3];
    int exertData[3];
    Indication indicator;
    Joysticks control;
public:
    Manager(){
    }
    bool readRadio() {return 0;}
    bool readControl() {return 0;}
    bool setIndication() {
        int indicationData[] = {1230, 321, 1011, 130, 432};
        indicator.initLCD();
        indicator.updateLCD(indicationData, 5);
    }

    bool sendCommandRadio() {return 0;}
    bool sendCommandSerial() {return 0;}
    void devSerialEvent() {char a;}
    void ascSensors() {char a;}
};
Manager* manager = new Manager();
void setup()
{
    manager->setIndication();
}

void loop()
{
}
