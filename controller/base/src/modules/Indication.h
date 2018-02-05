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
    double lcdLatestUpd;
    int preIndicationData[7];
    bool compare(int[],int[],int)const; //True if non equals
    int powd(int ,int)const;
    void copy(int[],int[],int);
public:
    Indication();
    /*void print(const char []);
    void print(int[],int);
    void print(char);
    void print(int, int, int, bool);
    void print(bool);*/
    void print(void*,char='s');
    void updateLCD(int[],int);
    void setMovingFlagLED(bool)const;
    void setScanningFlagLED(bool)const;
};

#endif
