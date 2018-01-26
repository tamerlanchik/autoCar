//base
#if !defined(HEADCOM)
#define HEADCOM
#include "RadioExtended.h"
#include "Joysticks.h"
#include "Indication.h"
#include "pins.h"
#include "Logger.h"
class Manager{
private:
    int motorVals[2];
    int sonarAngle;
    bool isScanningFlag;
    bool isSignallingFlag;
    bool isMovingFlag;
    int sensorData[3];
    int urgentData[3];
    char message[3];
    RadioExtended radio;
    Indication indicator;
    Joysticks control;
    char i;
    long int time2;
    enum messageCodes {MOTOR_COMMAND, SENSOR_REQUEST, ACCOUNT_REQUEST, TEST1};
public:
    Manager();
    bool checkRadioConnection(int,int);
    bool makeRadioConnection();
    bool readRadio();
    bool radioAvailable();
    bool readControl()const;
    bool setIndication(int);
    void sendTest();
    bool sendCommandRadio();
    bool sendCommandSerial();
    bool devSerialEvent();
    void ascSensors(char);
    void printLCD(const char[]);
};
#endif
