#ifndef HeaderCommonConfig
#define HeaderCommonConfig

#define byte unsigned char

#define DEBUG

const char epsM = 10;
const char epsS = 3;

const char sonarCount = 1;
const char servoCount = 1;
const unsigned char borderSensorsCount = 5;
const unsigned long serialRate = 115200;
//const uint8_t adr1[]="1PIPE", adr2[]="2PIPE";
const char adr1[]="1PIPE", adr2[]="2PIPE";
const unsigned int radioWaitCheckAnswerTimeout = 1000;
const char lcdUpdateTimeout = 100;
const char motorChannelsCount = 2;

//commands
/*const char MessageType.MOTOR_COMM = 51;
const char SENSOR_REQUEST = 14;
const char ACCOUNT_REQUEST = 126;
const char CHECH_CONN = 93;
const char SIGNAL_COMM = 74;*/
enum angled {ROLL, PITCH, YAW};
enum coordinates {X,Y,Z};
enum SonarMode {ROTATE_MEASURE, MEASURE, ROTATE};
enum SensorAck {BORDERS, DISTANCE1};
enum class MessageType {CHECK_CONN, MOTOR_COMM, SIGNAL_COMM, SENSOR_REQUEST, ALL};
struct Message_template{
  char mode;
  int data[3];
};
class SonarData{
  private:
    unsigned int mMode[sonarCount];
    int mAngle[sonarCount];
    bool checkIndex(int number){
      if(number >= 0 && number < sonarCount){
        return true;
      }else{
        return false;
      }
    }
  public:
    SonarData(){
      for(unsigned char i = 0; i<sonarCount; i++)
      {
        mMode[i] = 0;
        mAngle[i] = 0;
      }
    }
    void setMode(unsigned int number, unsigned int mode){
      if(checkIndex(number)){
        mMode[number] = mode;
      }
    }
    unsigned int getMode(unsigned int number){
      if(checkIndex(number)){
        return mMode[number];
      }
    }
    unsigned int getDistance(unsigned int number){
      if(checkIndex(number)){
        return mMode[number];
      }
    }
    void setDistance(unsigned int numb, unsigned int dist){
      if(checkIndex(numb)){
        mMode[numb] = dist;
      }
    }
    void setAngle(int number, int angle){
      if(checkIndex(number)){
        mAngle[number] = angle;
      }
    }
    int getAngle(unsigned int number){
      if(checkIndex(number)){
        return mAngle[number];
      }
    }
    void setData(unsigned int number, SonarMode mode, int angle){
      setMode(number, mode);
      setAngle(number, angle);
    }
};
struct TwoSideData{
  int left;
  int right;
};
class ByteArray{
  public:
    static void reverseString(byte a[], int l){
      char t;
      for(int i=0; i<l/2; i++){
            t = a[i];
            a[i] = a[l-i-1];
            a[l-i-1] = t;
        }
    }

    static float getFloatFromByteArray(byte t[], unsigned int start){
      byte o[4];
      for(int i=0; i<4; i++){
        o[i] = t[i+start];
      }
      ByteArray::reverseString(o, 4);
      return *reinterpret_cast<float*>(o);
      //return *(float*)o;
    }
};

class ChassisData{
  private:
    int mValues[motorChannelsCount];
    static bool checkIndex(int number){
      if(number >= 0 && number < motorChannelsCount){
        return true;
      }else{
        return false;
      }
    }
  public:
    void setValue(unsigned int i, int val){
      if(checkIndex(i)){
        mValues[i] = val;
      }
    }
    int getValue(unsigned int i){
      if(checkIndex(i)){
        return mValues[i];
      }
    }
};
struct Borders{
  unsigned char values[borderSensorsCount];
};
class Message{
private:
  MessageType mMode;
  ChassisData mChassis;
  //SonarData mSonars;
  //Borders mBorders;
public:
  /*SonarData* getSonars(){
    return &mSonars;
  }*/
  ChassisData* getChassis(){
    return &mChassis;
  }
  void inflateMessage(byte data[]){
    if(data[0] == '#'){
      mMode = MessageType::MOTOR_COMM;
      float a, b;
      this->parseJoystickMessage(data+1, &a,&b);
      mChassis.setValue(0, (int)a);
      mChassis.setValue(1, (int)b);
    }else if(data[0] == '?'){
      mMode = MessageType::CHECK_CONN;
    }

  }
  void parseJoystickMessage(byte mess[], float* a, float* b){
    *a = ByteArray::getFloatFromByteArray(mess, 0);
    *b = ByteArray::getFloatFromByteArray(mess, 4);
  }
  /*Borders* getBorders(){
    return &mBorders;
  }*/
  void setMode(MessageType mode){
    mMode = mode;
  }
  MessageType getMode(){
    return mMode;
  }
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
