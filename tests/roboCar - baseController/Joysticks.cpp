#include <Arduino.h>
#include <pins.h>
class Joysticks{
private:
    int preMotorsVals[2];
    char preSonarAngle;
    int motorJoysNeutral[2];
    int sonarJoyNeutral;


public:
    bool getMotorsJoys(int val[]) {
        bool isChanged=false;
        for(char i=0; i<2; i++){
            val[i]=analogRead(motorJoys[i]);
            if(abs(val[i]-preMotorsVals[i])>epsM){
                isChanged = true;
                preMotorsVals[i] = val[i];
            }
        }
        return isChanged;
    }
    bool getSonarJoy(int val){
        bool isChanged=false;
        val=analogRead(sonarJoy);
        if(abs(val-preSonarAngle)>epsS){
            isChanged = true;
            preSonarAngle = val;
        }
        return isChanged;
    }
    bool getSonarState(void){
        return digitalRead(scanBut);
    }
    bool getSignalState(void){
        return digitalRead(signalBut);
    }

};
