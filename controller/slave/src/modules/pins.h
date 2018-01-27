#ifndef HeaderH
#define HeaderH
const char motorJoys[] = {2, 3};
const char sonarJoy = 2;
const char signalBut = 3;
const char scanBut = 4;
const char movingFlagLED = 5;
const char scanningFlagLED = 6;
const char epsM = 10;
const char epsS = 3;
const long int serialRate = 115200;
const uint8_t adr1[]="1PIPE", adr2[]="2PIPE";
enum messageCodes {MOTOR_COMMAND, SENSOR_REQUEST, ACCOUNT_REQUEST, TEST1};
struct Message_template{
  char mode;
  int data[3];
};

#endif
