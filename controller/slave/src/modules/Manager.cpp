//slave
#include "Manager.h"
//Logger Log(28800);
extern Logger* Log;
Manager::Manager():radio(9, 10, adr1, adr2, RF24_2MBPS, RF24_PA_MIN, false){
  Log->d("Manager inited");
  test[0]=10;test[1]=65;
  delay(20);
  //Log->d("Init manager");
  //radio.initRadio(adr1, adr2, RF24_1MBPS);
  //Log->d("Init Radio");
}

Message_template Manager::readRadio() {
  if(radio.available()){
    radio.read(&mess, sizeof(mess));
    Log->d("Package receive:");
    if(mess.mode==CHECK_CONN)
    {
      mess.data[0]='!';
      Log->d("Check connection");
      radio.write(&mess,sizeof(mess));
    }
  }
    return mess;
}
bool Manager::radioAvailable(){
    return radio.available();
}
void Manager::writeRadio(int dat){
  Log->d("WriteRadio");
  message[1]=dat;
  radio.write(&message, 6);
}
void Manager::writeRadio(Message_template m)
{
  Log->d("WriteRadio()");
  mess=m;
  radio.write(&mess, sizeof(mess));
}
bool Manager::readControl() {return 0;}

bool Manager::sendCommandRadio() {return 0;}

bool Manager::sendCommandSerial() {return 0;}

bool Manager::devSerialEvent() {return 0;}

void Manager::ascSensors(char number=0)
{
        Log->d("Asc sensors");
        message[0] = SENSOR_REQUEST;
        message[1] = number;
        radio.write(message, sizeof(message));
}
