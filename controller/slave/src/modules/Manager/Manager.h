//slave
#if !defined(HEADCOM)
#define HEADCOM
#include "RadioExtended.h"
#include "Logger.h"
#include <Sensors.h>
#include "Chassis.h"
#include "DigitalOutShield.h"
#include <pins.h>
class Manager{
private:
    DigitalOutShield dos;
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
    int movingTimeout;
    int prevData;
public:
    Manager();
    Message_template readRadio();
    void initMirf();
    void testAckPayloads();
    void writeRadio(int);
    void writeRadio(Message_template);
    bool radioAvailable();
    bool setIndication(int);
    void sendTest();
    bool sendCommandRadio();
    void bip(int)const;
    void guard();
    void autonomousMode();
    void testing();
};
#endif