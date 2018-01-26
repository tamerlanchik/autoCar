//base
#include "Manager.h"
extern Logger* Log;
Manager::Manager():radio(9, 10, adr1, adr2, RF24_1MBPS, true),
                  indicator(),control(),i(0){
  Log->d("Init Manager");
}

bool Manager::readRadio() {
  Log->d("readRadio()");
    radio.read(&message, sizeof(message));
    Log->d("Read msg");
    indicator.print(message[1]);
    Log->d("Print msg");
    return 1;
}

bool Manager::radioAvailable(){
    //Log->d("Radio available");
    return radio.available();
}

bool Manager::readControl()const {return 0;}

bool Manager::setIndication(int k)
{
        int indicationData[] = {1230, 321, k, 130, 432};
        indicator.updateLCD(indicationData, 5);
        Log->d("Update LCD");
        return 1;
}

void Manager::sendTest()
{
      message[0]=TEST1;
      message[1]=i++;
      indicator.print(radio.write(&message, sizeof(message)));
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
void Manager::printLCD(const char message[])
{
  indicator.print(message);
  Log->d("printLCD");
}
