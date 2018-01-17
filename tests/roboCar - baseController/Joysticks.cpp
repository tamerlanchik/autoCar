#include <Arduino.h>
#include <B:\\roboCar\pins.h>
class Joysticks{
private:
    int preMotorsVals[2];
    char preSonarAngle;
    int motorJoysNeutral[2];
    int sonarJoyNeutral;


public:
    Joysticks():preSonarAngle(0)
    {
        for(char i=0; i<2; i++){
            preMotorsVals[i]=0;
            motorJoysNeutral[i]=analogRead(motorJoys[i]);
        }
        sonarJoyNeutral=analogRead(sonarJoy);
    }
    bool getMotorsJoys(int val[]) {
        bool isChanged=false;
        for(char i=0; i<2; i++){
            val[i]=analogRead(motorJoys[i])-motorJoysNeutral[i];
            if(abs(val[i]-preMotorsVals[i])>epsM){
                isChanged = true;
                preMotorsVals[i] = val[i];
            }
        }
        return isChanged;
    }
    bool getSonarJoy(int* val){
        bool isChanged=false;
        *val=analogRead(sonarJoy)-sonarJoyNeutral;
        if(abs(*val-preSonarAngle)>epsS){
            isChanged = true;
            preSonarAngle = *val;
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
