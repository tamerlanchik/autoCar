#if !defined(HEADCOM)
#define HEADCOM
#include "RadioExtended.h"
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
    int i=0;
    enum messageCodes {MOTOR_COMMAND, SENSOR_REQUEST, ACCOUNT_REQUEST, TEST1};
public:
    Manager();
    int readRadio();
    void writeRadio(int);
    bool radioAvailable();
    bool readControl();
    bool setIndication(int);
    void sendTest();
    bool sendCommandRadio();
    bool sendCommandSerial();
    bool devSerialEvent();
    void ascSensors(char);
};
#endif
