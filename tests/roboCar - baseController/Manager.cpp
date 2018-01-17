#include <RadioExtended.cpp>
#include <Joysticks.cpp>
#include <Indication.cpp>
#include <pins.h>
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
    RadioExtended radio;
public:
    Manager():radio(9, 10){
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
