//base
#include "Manager.h"
extern Logger* Log;
Manager::Manager():radio(9, 10, adr1, adr2, RF24_1MBPS, RF24_PA_MAX, true),indicator(),control(),i(0),time2(0),timeCheckJoys(0),connectionState(false){
  for(int i=0; i<7; i++)
  {
    indicationData[i]=0;
    data[i]=0;
  }
  delay(300);
  indicator.updateLCD(data,7,true);
  test[0]=5; test[1]=7;
  Log->d("Init Manager");
  mess.data[0]=15;
}

bool Manager::isConnectionActive(){return connectionState;}

bool Manager::checkRadioConnection(int timeOut, int tries){
  mess.mode = CHECH_CONN;
  mess.data[0] = '?';
  int c=0;
  radio.write(&mess, sizeof(mess));
  do{
    if(radio.available())
    {
      radio.read(&mess, sizeof(mess));
      if(mess.data[0]=='!')
        return true;
      else
        makeRadioConnection();
    }
    c++;
    delay(1);
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

void Manager::writeRadio(Message_template m){
  Log->d("WriteRadio()");
  mess=m;
  radio.write(&mess, sizeof(mess));
}

bool Manager::radioAvailable(){
    return radio.available();
}

bool Manager::sendCommandRadio(int mode) {
  Log->d("sendCommandRadio");
  mess.mode=mode;
  switch(mode){
    //motors
    case MOTOR_COMM:
      mess.data[0]=data[0];
      mess.data[1]=data[1];
      radio.write(&mess, sizeof(mess));
      delay(3);
      break;
    case CHECH_CONN:
      mess.data[0] = '?';
      radio.write(&mess, sizeof(mess));
      break;
    //sonar
    case SENSOR_REQUEST:
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
    //bip
    case SIGNAL_COMM:
      Log->d("Bip");
      mess.data[0]=data[5];
      Log->d("Radio valid");
      radio.write(&mess, sizeof(mess));
      delay(3);
      break;
    default:
      Log->e("Unknown command mode");
      return false;
  }
  return true;
}

void Manager::ackControl(){
  Log->d("ascControl()");
  if(control.getMotorsJoys(motorVals)){
    indicationData[0]=motorVals[0];
    indicationData[1]=motorVals[1];
  }
  if(control.getSonarJoy(&sonarAngle))
  {
    indicationData[3]=sonarAngle;
  }
  indicator.setMovingFlagLED(control.getSignalState());
  indicator.setScanningFlagLED(control.getSonarState());
  indicationData[5]=control.getSignalState();
  indicationData[6]=control.getSonarState();
  handleControlResults();
}

void Manager::ackSensors(char number){
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
    indicator.updateLCD(indicationData, 7);
}

void Manager::handleControlResults(){
  Log->d("Handle");
  //motors
  if(indicationData[0]!=data[0] || indicationData[1]!=data[1])
  {
    data[0]=indicationData[0];
    data[1]=indicationData[1];
  }
  sendCommandRadio(MOTOR_COMM);
  //sonar
  if(indicationData[3]!=data[3] || indicationData[6]!=data[6])
  {
    data[3]=indicationData[3];
    data[6]=indicationData[6];
    sendCommandRadio(SENSOR_REQUEST);
  }
  //bip
  if(indicationData[5]!=data[5])
  {
    data[5]=indicationData[5];
  }
  sendCommandRadio(SIGNAL_COMM);

  indicator.updateLCD(indicationData, 7);
}

void Manager::printLCD(void* message, char type){
  indicator.print(message,type);
}

void Manager::debugRadio(){
    Log->d("Start debug");
    /*mess.data[0]++;
    Log->d(&mess.data[0], 'd');
    radio.write(&mess, sizeof(mess));*/
    /*mess.mode = 91;
    data[5] = !digitalRead(signalBut);
    //data[5] = 0;
    sendCommandRadio(91);*/
    //mess.data[0]++;
    int i = 123;
    unsigned long t;
    Mirf.send((byte *) &i);
    t=millis();
    while(Mirf.isSending()) {
      if(millis()-t>2000){
        Log->d("Error send");
        break;
      }
    }
    //while(radio1.isSending()) {}
    //approx. 5-6 ms longs
    /*int t = Serial.read();
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
    }*/
    /*if(radio.write(&mess,sizeof(mess)))
    {
      radio.read(&mess, sizeof(mess));
    }*/
}
