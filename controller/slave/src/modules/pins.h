#ifndef HeaderH
#define HeaderH
//Nano SWM: 3.5.6.9.10.11
const char sonarServoPin[] = {3};
const char sonar_trigPin[] = {11};
const char sonar_echoPin[] = {11};
const char bordersSensor[] = {0,1,2,3};
const char motors[] = {6,7,8,9, 3, 5};
const char buzzer = 10;
const char epsM = 10;
const char epsS = 3;
const long int serialRate = 115200;
const uint8_t adr1[]="1PIPE", adr2[]="2PIPE";
const char MOTOR_COMM = 51;
const char SENSOR_REQUEST = 14;
const char ACCOUNT_REQUEST = 126;
const char CHECH_CONN = 93;
const char SIGNAL_COMM = 74;
///enum messageCodes {MOTOR_COMMAND, SENSOR_REQUEST, ACCOUNT_REQUEST, CHECK_CONN};
enum sensorsCodes {SONAR_ID, BORDERS_ID};
struct Message_template{
  char mode;
  int data[3];
};
struct SensorsPack{
  bool borders[4];
  int sonarAngle;
  int sonarValue;
};

#endif
