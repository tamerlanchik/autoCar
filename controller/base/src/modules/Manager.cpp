//base
#include "Manager.h"
extern Logger* Log;
Manager::Manager():radio(9, 10, adr1, adr2, RF24_1MBPS){
  Log->d("Manager init");
  indicator.initLCD();
  Log->d("Init LCD");
}

bool Manager::readRadio() {
    radio.read(&message, sizeof(message));
    Log->d("Read msg");
    indicator.print(message, sizeof(message));
    Log->d("Print msg");
    return 1;
}

bool Manager::radioAvailable(){
    return radio.available();
}

bool Manager::readControl() {return 0;}

bool Manager::setIndication(int i)
{
        int indicationData[] = {1230, 321, i, 130, 432};
        //indicator.initLCD();
        indicator.updateLCD(indicationData, 5);
        Log->d("Update LCD");
        return 1;
}

void Manager::sendTest()
{
      message[0]=TEST1;
      message[1]=i++;
      indicator.print(radio.write(message, sizeof(message)));
      Log->d("sendTest");
}

bool Manager::sendCommandRadio() {return 0;}

bool Manager::sendCommandSerial() {return 0;}

bool Manager::devSerialEvent() {return 0;}

void Manager::ascSensors(char number=0)
{
        message[0] = SENSOR_REQUEST;
        message[1] = number;
        radio.write(message, sizeof(message));
        Log->d("Asc sensors");
}
