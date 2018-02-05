#ifndef HeaderH
#define HeaderH
const char motorJoys[] = {0, 1};
const char sonarJoy = 2;
const char signalBut = 4;
const char scanBut = 3;
const char movingFlagLED = 5;
const char scanningFlagLED = 6;
const char epsM = 2;
const char epsS = 3;
const int serialRate = 9600;
const uint8_t adr1[]="1PIPE", adr2[]="2PIPE";
enum messageCodes {MOTOR_COMMAND, SENSOR_REQUEST, ACCOUNT_REQUEST, CHECK_CONN, TEST1};
const char commands[]={74,74,14,14,14,14,14};
struct Message_template{
  char mode;
  int data[3];
};
#endif
