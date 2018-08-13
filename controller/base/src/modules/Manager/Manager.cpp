//base
#include "Manager.h"
extern Logger* Log;
Manager::Manager():radio(9, 10, adr1, adr2, RF24_1MBPS, RF24_PA_MAX, true),indicator(),control(),i(0),time2(0),timeCheckJoys(0),connectionState(false),tm(100),
freezeTime(0), freezeLedState(false),indicationData(){
  for(int i=0; i<7; i++)
  {
    data[i]=0;
  }
  delay(100);
  mMessage = new Message();
  Log->d("Init Manager");
}

bool Manager::isConnectionActive(){return connectionState;}

bool Manager::checkRadioConnection(unsigned int timeout){
  mess.mode = 123;
  mess.data[0] = '?';
  radio.write(&mess, sizeof(mess));
  unsigned long startTime=millis();
  while(millis()-startTime <= 10) {
    if(radio.available()){
      radio.read(&mess, sizeof(mess));
      if(mess.data[0]=='!'){
        connectionState = true;
        Log->d("Connecion alive!");
        return true;
      }
      else{
        Log->e("A wrong check answer is got");
        break;
      }
    }
  }
  //Log->e("No check answer");
  connectionState = false;
  return 0;
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
  /*switch(mode){
    //motors
    case MessageType.MOTOR_COMM:
      mess.data[0]=data[0];
      mess.data[1]=-data[1];
      if(!radio.write(&mess, sizeof(mess))){
        Log->e("Connection lost!!!!!");
      }
      delay(3);
      break;
    case MessageType.CHECH_CONN:
      mess.data[0] = '?';
      radio.write(&mess, sizeof(mess));
      break;
    //sonar
    case MessageType.SENSOR_REQUEST:
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
    case MessageType.SIGNAL_COMM:
      Log->d("Bip");
      mess.data[0]=data[5];
      Log->d("Radio valid");
      radio.write(&mess, sizeof(mess));
      delay(3);
      break;
    default:
      Log->e("Unknown command mode");
      return false;
  }*/
  return true;
}

void Manager::ackControl(){
  Log->d("ascControl()");
  if(control.getMotorsJoys(motorVals)){
    for(byte i=0; i<2; i++){
      indicationData.motors[i] = motorVals[i];
    }
  }

  if(control.getSonarJoy(&sonarAngle)){
    indicationData.sonarAngle=sonarAngle;
  }

  indicator.setMovingFlagLED(control.getSignalState());
  indicator.setScanningFlagLED(control.getSonarState());

  indicationData.signalState = control.getSignalState();
  indicationData.scanState = control.getSonarState();

  handleControlResults();
}

void Manager::maintainRadioConnection(bool isEmerge){
  if(isEmerge || radio.isTimeToCheckConnection()){
      while(!checkRadioConnection(++tm)){
        indicator.print("No connection");
      }
      radio.lastCheckConnectionTime = millis();
      indicator.print("Connected");
  }
}

void Manager::ackSensors(char number){
    //Log->d("Asc sensors");
    //mess.mode = SENSOR_REQUEST;
    mess.data[0] = DISTANCE1;
    mess.data[2] = ROTATE_MEASURE;
    bool flag = 0;
    for(int i=0; i<180; i++){
      flag = 0;
      mess.data[1] = i;
      radio.write(&mess, sizeof(mess));
      unsigned long tim = millis();
      while(!radio.available() && millis()-tim < 10) {}
      while(millis()-tim < 100){
        if(radio.available()){
          radio.read(&mess, sizeof(mess));
          Serial.println(mess.data[1]);
          indicator.updateLCD(indicationData, 7);
          flag = 1;
          break;
        }
      }
      if(!flag){
        i--;
      }

    }
}

void Manager::handleControlResults(){
  Log->d("Handle");
  //motors
  //sendCommandRadio(MessageType.MOTOR_COMM);
  //sonar
  //sendCommandRadio(SENSOR_REQUEST);
  //bip
  //sendCommandRadio(SIGNAL_COMM);

  indicator.updateLCD(indicationData);
}

void Manager::printLCD(void* message, char type){
  indicator.print(message,type);
}

void Manager::debugRadio(){
    Log->d("Start debug");

}

void Manager::indicateFreeze(){
  if(millis()-freezeTime > 300){
      indicator.setMovingFlagLED(freezeLedState);
      freezeLedState = !freezeLedState;
      freezeTime = millis();
  }
}

void Manager::retranslate(){
  if(readSerial()){
    radio.write(mSerialMessage, 32);
  }
}

bool Manager::readSerial(){
  if(Serial.available()){
    //byte mode = Serial.read();
    unsigned int i = 0;
    while(i<32){
      if(Serial.available() > 0){
        mSerialMessage[i] = Serial.read();
        if(mSerialMessage[i] == ';') break;
        i++;
      }
    }
    Serial.println(String((char*)mSerialMessage));
    //radio.write(&mSerialMessage, 64);

    /*if(mode == '#'){
      mMessage->inflateMessage(mode, mSerialMessage);
      //parseJoystickMessage(mSerialMessage);
    }*/
    return true;
  }
  return false;
}

/*void Manager::parseJoystickMessage(char t[]){
  //struct: #### ####;
  float a = getFloatFromByteArray(t, 0);
  float b = getFloatFromByteArray(t, 4);

  indicator.print("J: " +String(a) + " " + String(b));
}*/
