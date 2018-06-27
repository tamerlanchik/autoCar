#ifndef HeaderH
#define HeaderH
#define MIN(a,b) ((a)<(b)) ? (a) : (b)
#define MAX(a, b) ((a)>(b)) ? (a) : (b)
//Nano SWM: 3.5.6.9.10.11

//pins
const char sonarServoPin[] = {9};
const char sonar_trigPin[] = {0};
const char sonar_echoPin[] = {8};
const char bordersSensor[] = {0,1,2,3};
const char motors[] = {1,2,3,4, 5, 6};
const char buzzer = 3;
const char SHIFT_SS = 7;
const char SHIFT_LOCK = 8;

//settings
const int sonarTimeout = 50;   // [ms]
const char servoRange[1][2] = { {5, 180}};

#endif
