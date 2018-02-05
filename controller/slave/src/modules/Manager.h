//slave
#if !defined(HEADCOM)
#define HEADCOM
#include "RadioExtended.h"
#include "pins.h"
#include "Logger.h"
#include "Sensors.h"
#include "Chassis.h"
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
    RadioExtended* radio;
    Sensors sensors;
    Chassis chassis;
    int i=0;
    int t=0;
    int test[2];
    int reloadRadioTime;
public:
    Manager();
    Message_template readRadio();
    void testAckPayloads();
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
    void bip(int)const;
};
#endif
