#if !defined(HEADERJOY)
#define HEADERJOY
#include <Arduino.h>
#include "pins.h"
#include <config.h>
#include "Logger.h"
extern Logger* Log;
class Joysticks{
private:
    int preMotorsVals[2];
    char preSonarAngle;
    int motorJoysNeutral[2];
    int sonarJoyNeutral;
public:
    Joysticks();
    bool getMotorsJoys(int[]);
    bool getSonarJoy(int*);
    bool getSonarState(void) const;
    bool getSignalState(void) const;
};
#endif
