#include <B:\\roboCar\RadioExtended.cpp>
#include <B:\\roboCar\Joysticks.cpp>
#include <B:\\roboCar\Indication.cpp>
#include <B:\\roboCar\pins.h>
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
    Indication indicator;
    Joysticks control;
    RadioExtended radio;
    enum messageCodes {MOTOR_COMMAND, SENSOR_REQUEST, ACCOUNT_REQUEST};
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
    void ascSensors(char number=0) {
        message[0] = SENSOR_REQUEST;
        message[1] = number;
        radio.write(message, sizeof(message));
    }
};
