//slave
#include "Manager.h"
extern Logger* Log;

Manager::Manager():sensors(), chassis(),reloadRadioTime(0),movingTimeout(0),dos(1, SHIFT_SS),prevData(0){
  radio=new RadioExtended(2, 4, adr1, adr2, RF24_1MBPS, RF24_PA_MAX, false);

  dos.init();

  chassis.init();
  chassis.setDOS(&dos);

  sensors.init();
  sensors.setDOS(&dos);

  Log->d("Manager inited");
}

Message_template Manager::readRadio() {
  if(radio->available()){
    Log->d("\nRadio available:");
    radio->read(&mess, sizeof(mess));
    //Log->d("Package receive:");
    //Log->d(&mess.data[0], 'd');

    switch(mess.mode){
      case CHECH_CONN:
        Log->d("Check connection");
        mess.data[0]='!';
        radio->write(&mess,sizeof(mess));
        break;
      case MOTOR_COMM:
        Log->d("Motor command");
        chassis.setValue(mess.data[0],mess.data[1]);
        movingTimeout = millis()/100;
        break;
      case SENSOR_REQUEST:
        Log->d("Sensor request");
        sensors.getValue(mess.data);
        radio->write(&mess, sizeof(mess));
        break;
      case SIGNAL_COMM:
        Log->d("Bip");
        bip(mess.data[0]);
        break;
      default:
        Log->d("Unknown mode got");
        Log->d(mess.mode, 'd');
        break;
    }
  }

  return mess;
}

bool Manager::radioAvailable(){
    return radio->available();
}

void Manager::writeRadio(int dat){
  Log->d("WriteRadio");
  message[1]=dat;
  radio->write(&message, 6);
}

void Manager::writeRadio(Message_template m){
  Log->d("WriteRadio()");
  mess=m;
  radio->write(&mess, sizeof(mess));
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
  if(millis()/100-movingTimeout > 1)
  {
    chassis.setValue(0,0);
    movingTimeout = millis()/100;
    tone(buzzer, 300);
  }
}

void Manager::autonomousMode() {
}

void Manager::testing(){
  //int k = sensors.getSonar(1,1,2);
  //Log->d(&k, 'd');
  Log->d("Start");
  for(int i=0; i<=180; i+=5){
    //sensors.getSonar(0, i, sensors.ROTATE);
    //sensors.rotate(0, i, true);
    int r = sensors.getSonar(0, i, sensors.ROTATE_MEASURE);
    Log->d(&r, 'd');
    /*int t = millis();
    while(abs(analogRead(0)-255) < 3) {};
    t = millis() - t;*/
    //Log->d(&i, 'd');
    //Log->d(&t, 'd');
  }
  /*sensors.rotate(0, 100);
  delay(1000);
  sensors.rotate(0, 120);
  int t = millis();
  while(abs(analogRead(0)-353) > 1) {};
  t = millis() - t;
  Log->d(&t, 'd');
  Log->d("Finish");*/
}
