#include "Chassis.h"
extern Logger* Log;

Chassis::Chassis(){
  dos = NULL;
  motorVal[0]=motorVal[1]=0;
  Log->d("Create-1 Chassis");
  t=0;
}

void Chassis::init(){
  Log->d("Init Chassis");
}

void Chassis::setDOS(DigitalOutShield* d){
  dos = d;
}

void Chassis::setValue(int a, int b){
  int epsRotate = 100;
  int epsMove = 50;
  Log->d("setValue - MOTORS");
  //analogWrite(motors[5], map(-a, -512, 512, 0, 255));
  int speedA= abs(a);
  int speedB = abs(b);
  speedA = map(speedA, 0, 521, 0, 255);
  speedA = F1(speedA);

  speedB = map(speedB, 0, 524, 0, 255);
  //speedB = F1(speedB);
  double spB = speedB/255 * 4 / 2+1;;
  //Диапазон масштаба: от 1.5 до 5
  if(b>0){
    void;
  }else{
    spB = 1/spB;
  }
  if(abs(a) < epsMove){
    if(abs(b) < epsRotate){
      writeMotors(Modes.Stop);
    }else{
      analogWrite(motors[4], speedB);
      analogWrite(motors[5], speedB);
      if(b > 0){
        writeMotors(Modes.Right);
      }else{
        writeMotors(Modes.Left);
      }
    }
  }else{
    if(a > 0){
      writeMotors(Modes.Forward);
      //analogWrite(motors[4], MIN(speedA*(spB), 255));
    //  analogWrite(motors[5], MIN(speedA/(spB), 255));
    analogWrite(motors[4], MIN(speedA*2, 255));
    analogWrite(motors[5], MIN(speedA, 255));
    }else{
      writeMotors(Modes.Backward);
      analogWrite(motors[4], speedA/spB);
      analogWrite(motors[5], speedA*spB);
    }
  }
  /*if(b<5 && b>-5){
      if(a>5){
        dos->add(0, 1);
        dos->add(1, 0);
        dos->add(2, 1);
        dos->add(3, 0);
        Log->d("1");
      }
      else if(a<-5){
        dos->add(0, 0);
        dos->add(1, 1);
        dos->add(2, 0);
        dos->add(3, 1);
        Log->d("2");
      }
      else if(a>=-5 && a<=5){
        dos->add(0, 0);
        dos->add(1, 0);
        dos->add(2, 0);
        dos->add(3, 0);
        Log->d("3");
      }
    }
    else{
      if(b>5){
        dos->add(0, 1);
        dos->add(1, 0);
        dos->add(2, 0);
        dos->add(3, 1);
        Log->d("4");
      }
      else if(b<-5){
        dos->add(0, 0);
        dos->add(1, 1);
        dos->add(2, 1);
        dos->add(3, 0);
        Log->d("5");
      }
      else if(b>=-5 && a<=5){
        dos->add(0, 0);
        dos->add(1, 0);
        dos->add(2, 0);
        dos->add(3, 0);
        Log->d("6");
      }
    }
    dos->detach();
    dos->send();
    dos->attach();
    */
  /*if(b<5 && b>-5){
    if(a>5){
        digitalWrite(motors[0],1);
        digitalWrite(motors[1],0);
        digitalWrite(motors[2],1);
        digitalWrite(motors[3],0);
    }
    else if(a<-5){
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],1);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],1);
    }
    else if(a>=-5 && a<=5){
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],0);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],0);
    }
  }
  else{
    if(b>5){
        digitalWrite(motors[0],1);
        digitalWrite(motors[1],0);
        digitalWrite(motors[2],0);
        digitalWrite(motors[3],1);
    }
    else if(b<-5){
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],1);
      digitalWrite(motors[2],1);
      digitalWrite(motors[3],0);
    }
    else if(b>=-5 && a<=5){
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],0);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],0);
    }
  }*/
  //int speed = map(abs(a), 0, 521, 0, 255);
  int speed = abs(a);
  speed = F1(speed);
  speed = map(speed, 0, 521, 0, 255);
  /*if(abs(b)<50)
    b = 0;*/
  //analogWrite(motors[4], speed);
  //analogWrite(motors[5], speed);
}

void Chassis::getValue(int val[]){
  val[0]=motorVal[0];
  val[1]=motorVal[1];
}

int Chassis::F1(int x){
  if(x<100)
    return x;
  else if(x<=230)
    return (int)0.1*x+100;
  else
    return x;
}

void Chassis::test(){
  if(t){
    dos->write(B10101010);
    delay(100);
  }else{
    dos->write(B01010101);
    delay(100);
  }
  t = !t;
}

//private
void Chassis::writeMotors(bool values[]){
  for(unsigned char i = 0; i<4; i++){
    dos->add(i, values[i]);
  }
  dos->detach();
  dos->send();
  dos->attach();
}
