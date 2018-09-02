#ifndef HeaderH
#define HeaderH
#define MIN(a,b) ((a)<(b)) ? (a) : (b)
#define MAX(a, b) ((a)>(b)) ? (a) : (b)
//Nano SWM: 3.5.6.9.10.11

//pins
//REMEMBER: PIN 10 ONLY OUTPUT!
const char sonarServoPin[] = {9};
const char sonar_trigPin[] = {15};
const char sonar_echoPin[] = {7};
const char borderSensorPins[] = {3, 4, 5, 1, 2};
const char motors[] = {4,7,8,9, 5, 6};
const char buzzer = 3;
const char SHIFT_SS = 7;
const char SHIFT_LOCK = 8;

//settings
const int sonarTimeout = 10;   // [ms]
const int sonarMaxDist = 100;
const unsigned char servoRange[1][2] = { {5, 180}};
const float dL = 0.02105;
const bool areMotorsConnectedThroughtDOS = 0;
const bool isSonarConnectedThroughtDOS = 0;
const bool isDOSConnected = 0;

#endif
