#ifndef HeaderCommonConfig
#define HeaderCommonConfig

const char epsM = 10;
const char epsS = 3;

const char sonarCount = 1;
const char servoCount = 1;
const unsigned long serialRate = 115200;
const uint8_t adr1[]="1PIPE", adr2[]="2PIPE";
const unsigned int radioWaitCheckAnswerTimeout = 1000;
const char lcdUpdateTimeout = 100;

//commands
const char MOTOR_COMM = 51;
const char SENSOR_REQUEST = 14;
const char ACCOUNT_REQUEST = 126;
const char CHECH_CONN = 93;
const char SIGNAL_COMM = 74;
enum SonarMode {ROTATE_MEASURE, MEASURE, ROTATE};
enum SensorAck {BORDERS, DISTANCE1};
struct Message_template{
  char mode;
  int data[3];
};
class Indication_template{
  public:
    int motors[2];
    int sonarAngle;
    unsigned int sonarValue;
    bool borders[4];
    bool signalState;
    bool scanState;
    Indication_template(){
      motors[0] = 0;
      motors[1] = 0;
      sonarAngle = 0;
      sonarValue = 0;
      for(unsigned char i = 0; i<4; i++){
        borders[i] = 0;
      }
      signalState = 0;
      scanState = 0;
    }
    bool compare(Indication_template* b){
      bool flag = 1;
      for(unsigned char i = 0; i<2; i++){
        flag = motors[i] == b->motors[i];
      }
      if(flag)  flag = sonarAngle == b->sonarAngle;
      if(flag) flag = sonarValue == b->sonarValue;
      if(flag){
        for(unsigned char i = 0; i<4; i++){
          flag = borders[i] == b->borders[i];
        }
      }
      if(flag) flag = signalState == b->signalState;
      if(flag) flag = scanState == b->scanState;
      return flag;
    }
    void copy(Indication_template* origin){
      for(unsigned char i = 0; i<2; i++)
        motors[i] = origin->motors[i];
      sonarAngle = origin->sonarAngle;
      sonarValue = origin->sonarValue;
      for(unsigned char i = 0; i<4; i++){
        borders[i] = origin->borders[i];
      }
      signalState = origin->signalState;
      scanState = origin->scanState;
    }
};
struct SensorsPack{
  bool borders[4];
  int sonarAngle[1];
  int sonarValue[1];
};
#endif
