//base
#if !defined(HEADCOM)
#define HEADCOM
#include <RadioExtended.h>
#include "Joysticks.h"
#include "Indication.h"
#include "pins.h"
#include <config.h>
#include "Logger.h"
using namespace std;
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
    //int indicationData[7];
    int data[7];
    int i;
    long int time2, timeCheckJoys;
    bool connectionState;
    int test[2];
    int tm;
    unsigned long freezeTime;
    bool freezeLedState;
    Indication_template indicationData;
    byte mSerialMessage[32];
    Message* mMessage;
public:
    Manager();
    bool checkRadioConnection(unsigned int);
    void maintainRadioConnection(bool=false);
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
    void indicateFreeze();
    bool readSerial();
    void retranslate();
    //void reverseString(char[],int);
    //void parseJoystickMessage(char[]);
    //float getFloatFromByteArray(char[],unsigned int);
};
#endif
