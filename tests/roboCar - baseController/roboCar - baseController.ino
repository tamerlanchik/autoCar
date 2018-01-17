#include <Arduino.h>
#include <Wire.h>
#include <libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h>
class Joysticks{
private:
    const byte motorJoys[2] = {2, 3};
    const int sonarJoy = 1;
    const byte signalBut = 3;
    const byte scanBut = 4;
    const byte epsM = 5;
    const byte epsS = 3;

    int preMotorsVals[2];
    byte preSonarAngle;
    int motorJoysNeutral[2];
    int sonarJoyNeutral;

public:
    bool getMotorsJoys(int val[]) {
        bool isChanged=false;
        for(byte i=0; i<2; i++){
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
        val=analogRead(sonarJoys);
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

    const LiquidCrystal_I2C lcd;
    const byte movingFlagLED = 5;
    const byte scanningFlagLED = 6;
public:
    Indication():lcd(0x27,16,2) {}
    bool updateLCD(int data[], int len){
        lcd.clear();

        //Motors values
        lcd.setCursor(0, 0);
        lcd.print("M");
        lcd.print(data[0]);
        lcd.setCursor(5, 0);
        lcd.print("|");
        lcd.print(data[1]);

        //Borders values
        lcd.setCursor(11, 0);
        lcd.print("B");
        for(byte i=0; i<4; i++){
            lcd.setCursor(11+(i%2)*3, i/2);
            lcd.print("|");
        }
        for(byte i=0; i<4; i++){
            if((data[2]%pow(10, i+1))/pow(10, i)){
                lcd.setCursor(12+i%2, i/2);
                lcd.print("\xDB");
            }
        }

        //Sonar angle+value
        lcd.setCursor(0, 1);
        lcd.print("S"); lcd.print(data[3]); lcd.print("°");
        if(data[4]<0) lcd.print("-");
        else          lcd.print(data[4]);
        return true;
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
public:
    bool readRadio() {return 0;}
    bool readControl() {return 0;}
    bool setIndication() {
        int indictionData[] = {123, 321, 1010, 130, 432};
        indicator.updateLCD(indicationData, 5);
    }

    bool sendCommandRadio() {return 0;}
    bool sendCommandSerial() {return 0;}
    void devSerialEvent() {void}
    void ascSensors() {void}
};
Manager manager;
void setup()
{
    manager.setIndication();
}

void loop()
{
}
