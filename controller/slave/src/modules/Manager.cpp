//slave
#include "Manager.h"
//Logger Log(28800);
extern Logger* Log;
Manager::Manager():sensors(), chassis(),reloadRadioTime(0),movingTimeout(0)
{
  radio=new RadioExtended(2, 4, adr1, adr2, RF24_1MBPS, RF24_PA_MAX, false);
  Log->d("Manager inited");
  pinMode(buzzer, OUTPUT);
  for(int i=0; i<4; i++)
  {
    pinMode(motors[i], OUTPUT);
  }
  //Log->d("Init manager");
  //radio->initRadio(adr1, adr2, RF24_1MBPS);
  //Log->d("Init Radio");
}

Message_template Manager::readRadio() {
  if(radio->available()){
    //Log->d("Radio available:");
    //radio->writeAckPayload(1, &mess, sizeof(mess));
    radio->read(&mess, sizeof(mess));
    //Log->d("Package receive:");
    //Log->d(&mess.data[0], 'd');
    switch(mess.mode)
    {
      case CHECH_CONN:
        Log->d("Check connection");
        mess.data[0]='!';
        radio->write(&mess,sizeof(mess));
        break;
      case MOTOR_COMM:
        Log->d("Motor command");
        chassis.setValue(mess.data[0],mess.data[1]);
        movingTimeout = millis()/100;
        int trt;
        trt = analogRead(A4);
        Log->d(&trt, 'd');
        break;
      case SENSOR_REQUEST:
        Log->d("Sensor request");
        sensors.getValue(mess.data);
        radio->write(&mess, sizeof(mess));
        break;
      case SIGNAL_COMM:
        Log->d("Bip");
        bip(mess.data[0]);
        //radio->write(&mess, sizeof(mess));
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
  else{noTone(buzzer);}
}

//activate when there is no commands for a long time
void Manager::guard(){
  if(millis()/100-movingTimeout > 1)
  {
    chassis.setValue(0,0);
    movingTimeout = millis()/100;
  }
}

void Manager::autonomousMode() {
  SensorsPack data = sensors.getValues();
  if(data.borders[0] || data.borders[1] || data.borders[2] || data.borders[3])
  {
    Log->d(&data.borders[1], 'b');
    chassis.setValue(0,0);
  }else{
    Log->d("Go");
    chassis.setValue(-300, 0);
  }
}
