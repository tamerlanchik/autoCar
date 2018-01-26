//base
#include "Manager.h"
extern Logger* Log;
Manager::Manager():radio(9, 10, adr1, adr2, RF24_2MBPS, RF24_PA_MIN, true),
                  indicator(),control(),i(0),time2(0){
  Log->d("Init Manager");
  // * For use with setPALevel()
  //enum { RF24_PA_MIN = 0,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX, RF24_PA_ERROR } rf24_pa_dbm_e ;
  //enum { RF24_1MBPS = 0, RF24_2MBPS, RF24_250KBPS } rf24_datarate_e;
}
bool Manager::checkRadioConnection(int timeOut, int tries)
{
  char checkData='?';
  int c=0;
  radio.write(&checkData, sizeof(checkData));
  do{
    if(radio.available())
    {
      radio.read(&checkData, sizeof(checkData));
      if(checkData=='!')
        return true;
    }
    c++;
    delay(timeOut);
  }while(c<tries);
  return false;
}
bool Manager::makeRadioConnection()
{
  if(millis()/1000-time2>3){
    while(!checkRadioConnection(3, 5)) {
      printLCD("No connection");
      delay(100);
    }
    time2=millis()/1000;
    printLCD("Connected");
  }
  return true;
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
      //indicator.print(radio.write(&message, sizeof(message)));
      radio.write(&message, sizeof(message));
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
