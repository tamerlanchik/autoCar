#include "Manager.h"
//Logger Log(28800);
extern Logger* Log;
Manager::Manager():radio(9, 10){
  Log->i("Manager init");
}

void Manager::init(){
      Log->d("Init manager");
      radio.initRadio(adr1, adr2, RF24_1MBPS);
      Log->d("Init Radio");

}

int Manager::readRadio() {
    Log->d("Read Radio");
    radio.read(message, sizeof(message));
    Log->d("Read msg");
    Log->d(message);
    return message[1];
}

bool Manager::radioAvailable(){
    return radio.available();
}
void Manager::writeRadio(int dat){
  Log->d("WriteRadio");
  message[1]=dat;
  radio.writee(message, sizeof(message));
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
