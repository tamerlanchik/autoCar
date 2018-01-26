#if !defined(HEADERIND)
#define HEADERIND

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pins.h"
#include "Logger.h"
extern Logger* Log;
class Indication{
private:
    //bool isMovingFlag;
    //bool isScanningFlag;
    LiquidCrystal_I2C lcd;
public:
    Indication();
    void initLCD();
    int powd(int ,int)const;
    void print(char [],int);
    void print(bool);
    void updateLCD(int[],int);
    void setMovingFlagLED(bool);
    void setScanningFlagLED(bool);
};

#endif