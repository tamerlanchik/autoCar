//base
#include "Manager.h"
extern Logger* Log;
Manager::Manager():radio(9, 10, adr1, adr2, RF24_2MBPS, RF24_PA_MIN, true),
                  indicator(),control(),i(0),time2(0),timeCheckJoys(0),connectionState(false){
  for(int i=0; i<7; i++)
  {
    indicationData[i]=0;
  }
  test[0]=5; test[1]=7;
  //while(!radio.write(&test,sizeof(test))) {}
  Log->d("Init Manager");
  // * For use with setPALevel()
  //enum { RF24_PA_MIN = 0,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX, RF24_PA_ERROR } rf24_pa_dbm_e ;
  //enum { RF24_1MBPS = 0, RF24_2MBPS, RF24_250KBPS } rf24_datarate_e;
}
bool Manager::isConnectionActive(){return connectionState;}
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
  mess.mode=CHECK_CONN;
  mess.data[0]='?';
  connectionState=false;
  while(!connectionState)
  {
    if(radio.write(&mess, sizeof(mess))){
      Log->d("Succesfully sent");
      if(radio.available()){
        radio.read(&mess,sizeof(mess));
        if(mess.data[0]=='!'){
          Log->d("Connection exits");
          connectionState=true;
        }
      }
      else{
        Log->d("No connection");
        connectionState=false;
      }
    }
  }
  return true;
}
/*bool Manager::readRadio() {
  Log->d("readRadio()");
    radio.read(&message, 6);
    Log->d("Read msg");
    indicator.print(message[1]);
    Log->d("Print msg");
    return 1;
}*/
Message_template Manager::readRadio() {
    Log->d("Read Radio");
    radio.read(&mess, sizeof(mess));
    Log->d("Message get:");
    Log->write(mess.mode, 'i');
    for(int i=0; i<3; i++){
      Log->write(mess.data[i], 'i');
    }
    return mess;
}
void Manager::writeRadio(Message_template m)
{
  Log->d("WriteRadio()");
  mess=m;
  radio.write(&mess, sizeof(mess));
}
bool Manager::radioAvailable(){
    //Log->d("Radio available");
    return radio.available();
}

bool Manager::readControl()const {return 0;}

bool Manager::setIndication(int k)
{
        int indicationDatai[] = {1230, 321, k, 130, 432};
        indicator.updateLCD(indicationDatai, 5);
        Log->d("Update LCD");
        return 1;
}

void Manager::sendTest()
{
      mess.mode=TEST1;
      mess.data[0]=i++;
      //indicator.print(radio.write(&message, sizeof(message)));
      radio.write(&mess, sizeof(mess));
      Log->d("sendTest");
}

bool Manager::sendCommandRadio() {return 0;}

bool Manager::sendCommandSerial() {return 0;}

bool Manager::devSerialEvent() {return 0;}
void Manager::ascControl(){
  Log->d("ascControl()");
  if(control.getSonarJoy(&sonarAngle))
  {
    //indicator.print(sonarAngle;, 10, 0, false);
    indicationData[3]=sonarAngle;
  }
  if(control.getMotorsJoys(motorVals)){
    //indicator.print(motorVals, 2);
    indicationData[0]=motorVals[0];
    indicationData[1]=motorVals[1];
  }
  indicationData[2]=1010;
  indicationData[4]=173;
  indicator.setMovingFlagLED(control.getSignalState());
  indicator.setScanningFlagLED(control.getSonarState());
  indicationData[5]=control.getSignalState();
  indicationData[6]=control.getSonarState();
  indicator.updateLCD(indicationData, 7);
}
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
