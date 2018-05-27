//base
#if !defined(HEADCOM)
#define HEADCOM
#include "RadioExtended.h"
#include "Joysticks.h"
#include "Indication.h"
#include "pins.h"
#include "Logger.h"
#include "Radio1Extended.h"
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
    RadioExtended radio;
    Indication indicator;
    Joysticks control;
    Message_template mess;
    int indicationData[7];
    int data[7];
    int i;
    long int time2, timeCheckJoys;
    bool connectionState;
    int test[2];

public:
    Manager();
    bool checkRadioConnection(int,int);
    bool makeRadioConnection(bool=false);
    bool isConnectionActive();
    void testAscPayloads();
    Message_template readRadio();
    void writeRadio(Message_template);
    bool radioAvailable();
    bool sendCommandRadio(int);
    void ackControl();
    void ackSensors(char=0);
    void printLCD(void*,char='s');
    void handleControlResults();
    void debugRadio();
};
#endif
