//slave
#if !defined(HEADCOM)
#define HEADCOM
#include "RadioExtended.h"
#include "Logger.h"
#include <Sensors.h>
#include "Chassis.h"
#include "DigitalOutShield.h"
#include "Model.h"
#include <pins.h>
class Manager{
public:
    DigitalOutShield dos;
    int motorVals[2];
    int sonarAngle;
    bool isScanningFlag;
    bool isSignallingFlag;
    bool isMovingFlag;
    int sensorData[3];
    int urgentData[3];
    Message_template mess;
    Message message;
    RadioExtended* radio;
    Sensors sensors;
    Chassis chassis;
    int i=0;
    int t=0;
    int test[2];
    int movingTimeout;
    int reloadRadioTime;
    int prevData;
    float speed[2];
    Model* model;
    bool isAnswerNeeded;
    byte mSerialMessage[32];

    Manager();
    void readRadio();
    void setModel(Model*);
    void initMirf();
    void testAckPayloads();
    bool radioAvailable();
    bool setIndication(int);
    void sendTest();
    bool sendCommandRadio();
    void bip(int)const;
    void guard();
    void autonomousMode();
    void testing();
    Sensors* getSensorMaster();
    Chassis* getChassisMaster();
    void watchBorders(unsigned int);
    void shedulled();
    void regulator();
    void updateModel();
};
#endif
