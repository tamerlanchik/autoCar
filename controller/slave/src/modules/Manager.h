//slave
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
    int message[3];
    Message_template mess;
    RadioExtended radio;
    int i=0;
public:
    Manager();
    Message_template readRadio();
    void writeRadio(int);
    void writeRadio(Message_template);
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
