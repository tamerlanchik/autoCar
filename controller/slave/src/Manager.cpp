#include <RadioExtended.cpp>
class Manager{
private:
  RadioExtended radio;
  char message[3];
public:
  Manager():radio(9, 10){
  }
  bool radioAvailable(){
    return radio.available();
  }
  void init(){
    radio.initRadio(0x1234567890LL, 0x1234567891LL, RF24_1MBPS);
  }
  int readRadio(){
    radio.read(&message, sizeof(message));
    return (int)message[1];
  }
  void writeRadio(int data){
    message[1]=data;
    radio.write(message, sizeof(message));
  }
};
