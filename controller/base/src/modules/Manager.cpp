#include "Manager.h"

Manager::Manager():radio(9, 10){}

void Manager::init(){
      indicator.initLCD();
      radio.initRadio(adr1, adr2, RF24_1MBPS);;
}

bool Manager::readRadio() {
    radio.read(&message, sizeof(message));
    indicator.print(message, sizeof(message));
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
}

void Manager::sendTest()
{
      message[0]=TEST1;
      message[1]=i++;
      indicator.print(radio.write(message, sizeof(message)));
}

bool Manager::sendCommandRadio() {return 0;}

bool Manager::sendCommandSerial() {return 0;}

void Manager::devSerialEvent() {char a;}

void Manager::ascSensors(char number=0)
{
        message[0] = SENSOR_REQUEST;
        message[1] = number;
        radio.write(message, sizeof(message));
}
