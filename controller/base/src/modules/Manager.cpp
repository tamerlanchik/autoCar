//base
#include "Manager.h"
extern Logger* Log;
Manager::Manager():radio(9, 10, adr1, adr2, RF24_250KBPS, RF24_PA_MIN, true),
                  indicator(),control(),i(0),time2(0),timeCheckJoys(0),connectionState(false){
  for(int i=0; i<7; i++)
  {
    indicationData[i]=0;
    data[i]=0;
  }
  delay(300);
  indicator.updateLCD(data,7,true);
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
bool Manager::makeRadioConnection(bool isEmerge){
  if(isEmerge || radio.isTimeToCheckConnection())
  {
    Log->d("-------checkConnection()");
    mess.mode=57;
    mess.data[0]='?';
    connectionState=false;
    int i=0;
    while(!connectionState)
    {
        if(!radio.ackRequest(&mess,sizeof(mess), &mess))
        {
          Log->e("Cant send ackReq()");
        }
        else{
          if(mess.data[0]=='!'){
            Log->d("Connection exits\n");
            connectionState=true;
            radio.lastConnectionTime=millis()/1000;
          }
          else{
            Log->d("No connection\n");
            connectionState=false;
          }
        }
      }
  }
  return connectionState;
}
Message_template Manager::readRadio() {
    if(radio.available()){
      Log->d("Read Radio");
      radio.read(&mess, sizeof(mess));
      Log->d("Message get:");
      Log->write((int)mess.mode, 'i');
      for(int i=0; i<3; i++){
        Log->write(mess.data[i], 'i');
      }
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
    return radio.available();
}

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

bool Manager::sendCommandRadio(int mode) {
  Log->d("sendCommandRadio");
  mess.mode=mode;
  switch(mode)
  {
    case 74:
      mess.data[0]=data[0];
      mess.data[1]=data[1];
      radio.write(&mess, sizeof(mess));
      break;
    case 14:
      mess.data[0]=89;
      mess.data[1]=data[4];
      mess.data[2]=data[6];
      radio.write(&mess, sizeof(mess));
      delay(5);
      readRadio();
      break;
    case 15:
      mess.data[0]=90;
      mess.data[1]=data[4];
      mess.data[2]=data[6];
      radio.write(&mess, sizeof(mess));
      delay(5);
      readRadio();
      break;
    case 91:
      mess.data[0]=data[5];
      radio.write(&mess, sizeof(mess));
      break;
    default:
      Log->e("Unknown command mode");
      return false;
  }
  return true;
}

bool Manager::sendCommandSerial() {return 0;}

bool Manager::devSerialEvent() {return 0;}
void Manager::ackControl(){
  //Log->d("ascControl()");
  if(control.getMotorsJoys(motorVals)){
    //indicator.print(motorVals, 2);
    indicationData[0]=motorVals[0];
    indicationData[1]=motorVals[1];
  }
  //indicationData[2]=1010;
  if(control.getSonarJoy(&sonarAngle))
  {
    //indicator.print(sonarAngle;, 10, 0, false);
    indicationData[3]=sonarAngle;
  }
  indicator.setMovingFlagLED(control.getSignalState());
  indicator.setScanningFlagLED(control.getSonarState());
  indicationData[5]=control.getSignalState();
  indicationData[6]=control.getSonarState();
  handleControlResults();
}
void Manager::ackSensors(char number)
{
    Log->d("Asc sensors");
    if(indicationData[6]==1)
    {
      mess.mode = 14;
      mess.data[0]=89;
      radio.ackRequest(&mess,sizeof(mess),&mess);
      indicationData[4]=mess.data[1];
    }
    mess.mode = 14;
    mess.data[0]=33;
    radio.ackRequest(&mess, sizeof(mess),&mess);
    indicationData[2]=mess.data[1];
}
void Manager::handleControlResults()
{
  //motors
  if(indicationData[0]!=data[0] || indicationData[1]!=data[1])
  {
    data[0]=indicationData[0];
    data[1]=indicationData[1];
    //sendCommandRadio(74);
  }
  //sonar
  if(indicationData[3]!=data[3] || indicationData[6]!=data[6])
  {
    data[3]=indicationData[3];
    data[6]=indicationData[6];
    //sendCommandRadio(14);
  }
  //bip
  if(indicationData[5]!=data[5])
  {
    data[5]=indicationData[5];
    sendCommandRadio(91);
  }
  indicator.updateLCD(indicationData, 7);
}
void Manager::printLCD(void* message, char type){
  indicator.print(message,type);
}
void Manager::debugRadio(){
  if(Serial.available())
  {
    //approx. 5-6 ms longs
    int t = Serial.read();
    Log->d("Received: ");
    Log->d(&t, 'd');
    //Serial.println((int)t);
    mess.mode=123;
    mess.data[0]=t;
    Message_template ans;
    if(radio.ackRequest(&mess,sizeof(mess),&mess))
    {
      Log->i(&mess.data[0],'d');
    }
    else{
      Log->e("No ascRequest");
    }
  }
}
