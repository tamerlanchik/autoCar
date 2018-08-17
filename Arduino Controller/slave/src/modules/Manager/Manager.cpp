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
  radio=new RadioExtended(8,4, adr1, adr2, RF24_1MBPS, RF24_PA_MAX, false);

  dos.init();

  chassis.init();
  if(isDOSConnected) chassis.setDOS(&dos);

  sensors.init();
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
  /*float v;
  unsigned long t = 0;
  for(int i = 50; i < 225; i++){
    chassis.setValue(0, i);
    v=0;
    t = millis();
    for(int j = 0; j<10; j++){
      sensors.update();
      v+= sensors.enc->speed[1];
      delay(600);
    }
    v = v/10;
    Serial.print(i);
    Serial.print("->");
    Serial.print(v);
    Serial.print(", k=");
    Serial.println(i/v);
  }*/
  /*const int N=5;
  for(int i=20; i<=150; i+=2){
    float data[N];
    float d =0;
    float middle=0, middle1=0;
    int minD=0,maxD=0;
    int countZeros = 0;
    int countPics = 0;
    for(int j=0; j<N; j++){
      data[j]=sensors.getSonar(1, i, ROTATE_MEASURE);
      middle+=data[j];
      maxD = data[j]>data[maxD]?j:maxD;
      minD = data[j]<data[minD]?j:minD;
      if(data[j] == 0){
        countZeros++;
      }
      if(data[j] > sonarMaxDist){
        countPics++;
      }
    }
    middle/=N;

    //float d =0;
    Serial.print("#");
    Serial.print(i);
    Serial.print(":");
    //Serial.print(middle);
    //Serial.println("&");
    //Serial.print('&');
    /*for(int i=0; i<N; i++){
      Serial.print(data[i]);
      Serial.print(':');
    }
    Serial.print(middle);
    Serial.print(':');*/
    /*if(countZeros > 2){
      if(countPics > 0 || data[maxD] == 0){
        for(int j=0; j<N; j++){
          data[j] = 1000;
        }
      }
    }
    if(middle/fabs(middle-data[maxD]) < 2 ){
      data[maxD] = middle;
    }
    if(middle/fabs(middle-data[minD]) < 2 ){
      data[minD] = middle;
    }
    middle = 0;
    for(int i=0; i<N; i++){
      middle+=data[i];
    }
    middle/=N;
    Serial.print(middle);
    //Serial.print(':');
    Serial.println('&');
  }
  //dos.write(B11111111);
  */
  /*delay(300);
  dos.write(B00000000);
  delay(300);*/

  const double R = 100; //mm
  //unsigned long counterAlert = sensors.getEncoder()->counterAlert[0];
  unsigned long counterAlert = sensors.getEncoder()->counterAlert[0];
  chassis.setValue(0, 100);
  while((sensors.getEncoder()->counterAlert[0] - counterAlert)*5.35 < 3.14*R) {Serial.println(sensors.getEncoder()->counterAlert[0]); delay(10);}
  chassis.setValue(0,0);
  delay(2000);


  /*chassis.setValue(200, 200);
  delay(1000);
  chassis.setValue(0,0);
  delay(1000);
  chassis.setValue(-100, -100);
  delay(300);
  chassis.setValue(-250, -250);
  delay(1000);
  chassis.setValue(0,0);
  delay(1000);*/

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
