#if !defined(HEADERIND)
#define HEADERIND

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pins.h"
#include <config.h>
#include "Logger.h"
#include <String.h>
extern Logger* Log;
class Indication{
private:
    //bool isMovingFlag;
    //bool isScanningFlag;
    LiquidCrystal_I2C lcd;
    unsigned long lcdLatestUpd;
    Indication_template preIndicationData;
public:
    Indication();
    /*void print(const char []);
    void print(int[],int);
    void print(char);
    void print(int, int, int, bool);
    void print(bool);*/
    void print(void*,char='s');
    void print(String);
    void printEmerge(void*, char='s');
    void updateLCD(Indication_template,bool=false);
    void setMovingFlagLED(bool)const;
    void setScanningFlagLED(bool)const;
};

#endif
