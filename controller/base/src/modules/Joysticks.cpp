#include "Joysticks.h"
Joysticks::Joysticks():preSonarAngle(0)
{
  for(int i=0; i<2; i++){
      preMotorsVals[i]=0;
      motorJoysNeutral[i]=analogRead(motorJoys[i]);
  }
  sonarJoyNeutral=analogRead(sonarJoy);
  Log->d("Init Joysticks");
}
bool Joysticks::getMotorsJoys(int val[]) {
    bool isChanged=false;
    for(int i=0; i<2; i++){
        val[i]=analogRead(motorJoys[i])-motorJoysNeutral[i];
        if(abs(val[i]-preMotorsVals[i])>epsM){
            isChanged = true;
            preMotorsVals[i] = val[i];
        }
    }
    Log->d("gMJ()");
    return isChanged;
}
bool Joysticks::getSonarJoy(int* val){
    bool isChanged=false;
    *val=analogRead(sonarJoy)-sonarJoyNeutral;
    if(abs(*val-preSonarAngle)>epsS){
        isChanged = true;
        preSonarAngle = *val;
    }
    Log->d("gSJ()");
    return isChanged;
}
bool Joysticks::getSonarState(void) const{
    Log->d("gSoS()");
    return digitalRead(scanBut);
}
bool Joysticks::getSignalState(void) const{
  Log->d("gSiS()");
    return digitalRead(signalBut);
}
