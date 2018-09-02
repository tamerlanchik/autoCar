//slave
#include "Manager.h"
extern Logger* Log;

Manager::Manager():
dos(1, SHIFT_SS),
sensors(),
chassis(),
movingTimeout(0),
reloadRadioTime(0),
prevData(0),
isAnswerNeeded(0){
  //radio=new RadioExtended(8,4, adr1, adr2, RF24_1MBPS, RF24_PA_MAX, false);

  //dos.init();

  chassis.init();
  //if(isDOSConnected) chassis.setDOS(&dos);

  //sensors.init();
  //if(isDOSConnected) sensors.setDOS(&dos);


  Log->d("Manager inited");
}

void Manager::setModel(Model* m){
  model = m;
}

void Manager::readRadio() {
  //Log->d("readRadio/");
  if(radio->available()){
    //Log->d("\nRadio available:");
    radio->read(mSerialMessage, 32);
    //Log->d("Package receive:");
    //Log->d(&mess.data[0], 'd');
    /*model->update(&message);
    MessageType mode = message.getMode();
    if(mode == MessageType::SENSOR_REQUEST || mode == MessageType::ALL){
      updateModel();
      model->inflateMessage(&message);
      radio->write(&message, sizeof(message));
    }*/
    message.inflateMessage(mSerialMessage);
    if(message.getMode() == MessageType::MOTOR_COMM){
      //Serial.println("M: " + String(message.getChassis()->getValue(0)) + "; " + String(message.getChassis()->getValue(1)));
      chassis.setValue(message.getChassis()->getValue(0), message.getChassis()->getValue(1));
      //Log->d("Motor command got");
    }
/*
    switch(message.getMode()){
      case MessageType::CHECK_CONN:
        Log->d("Check connection");
        radio->write(&message,sizeof(message));
        break;
      case MessageType::MessageType.MOTOR_COMM:
        Log->d("Motor command");
        chassis.setValue(message.getChassis());
        //chassis.setValue(message.data[0],message.data[1]);
        movingTimeout = millis()/100;
        break;
      case MessageType::SENSOR_REQUEST:
        Log->d("Sensor request");
        //sensors.getValue(message.data);
        radio->write(&message, sizeof(message));
        break;
      case MessageType::SIGNAL_COMM:
        Log->d("Bip");
        break;
      case MessageType::ALL:
        Log->d("Entire account request");
        chassis->setValue(message.getChassis());
        model->inflateMessage(&message);
        radio->write(&message, sizeof(message));
      default:
        Log->d("Unknown mode got");
        //Log->d(&(message.getMode()), 'd');
        break;
    }
  }*/
}
}

bool Manager::radioAvailable(){
    return radio->available();
}

bool Manager::sendCommandRadio() {return 0;}

//sound signal
void Manager::bip(int isOn)const{
  if(isOn){tone(buzzer, 1350);}
  else{
    noTone(buzzer);
  }
}

//activate when there is no commands for a long time
void Manager::guard(){
  this->watchBorders(5);
  /*if(millis()/100-movingTimeout > 1)
  {
    chassis.setValue(0,0);
    movingTimeout = millis()/100;
    tone(buzzer, 300);
  }*/
}

void Manager::autonomousMode() {
}

void Manager::testing(){
  chassis.setValue(200, 0);
  delay(1500);
  chassis.setValue(0, 0);
  delay(500);
  chassis.setValue(-200, 0);
  delay(1500);
  chassis.setValue(0, 0);
  delay(500);
}

void Manager::watchBorders(unsigned int count){
  sensors.updateBorderValues();
  bool face = 0, stern = 0;
  for(unsigned int i=0; i<3; i++){
    face = face | sensors.borderValues[i];
  }
  for(unsigned int i = 3; i<5; i++){
    stern = stern | sensors.borderValues[i];


  }

  if(speed[0] * speed[1] >=0){    //если не разворот на месте
    if(speed[0] > 0){             //если едем вперед
      if(face){                  //если впереди преграда
        chassis.setValue(-100, -100);
        //Serial.print("\nSpeed: "); Serial.println(sensors.enc->speed[0]);
        //while(sensors.enc->speed[0] > 0.1 && sensors.enc->speed[1] > 0.1) {delay(5);}
        //chassis.setValue(0, 0);
        //delay(300);
        speed[0] = -speed[0];
        speed[1] = -speed[1];
        chassis.setValue(speed[0], speed[1]);
        Log->d("Obstacle ahead");
      }
    }
    else if(speed[0] < 0){    //если едем задом
      if(stern){             //сзади препятствие
        chassis.setValue(100, 100);
        //while(sensors.enc->speed[0] > 0.1 && sensors.enc->speed[1] > 0.1) {delay(5);}
        chassis.setValue(0, 0);
        delay(300);
        speed[0] = -speed[0];
        speed[1] = -speed[1];
        chassis.setValue(speed[0], speed[1]);
        Log->d("Obstacle behind");
      }
    }
  }
}

void Manager::shedulled(){
  //chassis.setValue(model->motorVals[0], model->motorVals[1]);
  //this->watchBorders(5);
  //model->sonarDistance[0] = sensors.readSonar(0, model->sonarAngle[1][0], ROTATE_MEASURE);
  model->sonarAngle[0][0] = model->sonarAngle[1][0];
  sensors.getBorders(model->borderValues);
  sensors.shedulled();  //update speed
  /*chassis.setValue(speed);
  unsigned long c = sensors.enc->counterAlert[1];
  while(sensors.enc->counterAlert[1] - c < 396){delay(2);}
  chassis.setValue(0, 0);
  delay(1000);
  Serial.println(sensors.enc->counterAlert[1] - c );*/

}
void Manager::updateModel(){
  shedulled();
}
Sensors* Manager::getSensorMaster(){
  return &sensors;
}

Chassis* Manager::getChassisMaster(){
  return &chassis;
}

void Manager::regulator(){

}
