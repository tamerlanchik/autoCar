#ifndef HeaderH
#define HeaderH
//Nano SWM: 3.5.6.9.1.11
const char sonarServoPin[] = {3};
const char sonar_trigPin[] = {4};
const char sonar_echoPin[] = {5};
const char epsM = 10;
const char epsS = 3;
const long int serialRate = 115200;
const uint8_t adr1[]="1PIPE", adr2[]="2PIPE";
enum messageCodes {MOTOR_COMMAND, SENSOR_REQUEST, ACCOUNT_REQUEST, CHECK_CONN};
struct Message_template{
  char mode;
  int data[3];
};

#endif
