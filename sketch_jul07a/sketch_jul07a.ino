const char motorR[2]= {2, 3};
const char motorL[2] = {4, 5};
const char bord[4] = {6, 7, 8, 9};
const char joy[2] = {A0, A1};
int zeroJ[2];
int data;
void setup() {
  Serial.begin(9600);
  for(char i = 0; i<2; i++)
  {
    pinMode(motorR[i], OUTPUT);
    pinMode(motorL[i], OUTPUT);
    pinMode(bord[i*2], INPUT);
    pinMode(bord[(i+1)*2], INPUT);
    zeroJ[i] = analogRead(joy[i]);
  }
}

void loop() {
  if (Serial.available())
  {
    data = Serial.read();
    if (data == '1')
    {
      digitalWrite(motorR[0], 1);
      digitalWrite(motorR[1], 0);
      digitalWrite(motorL[0], 1);
      digitalWrite(motorL[1], 0);
    }
    else if (data == '2')
    {
      digitalWrite(motorR[0], 1);
      digitalWrite(motorR[1], 0);
      digitalWrite(motorL[0], 0);
      digitalWrite(motorL[1], 1);
    }
    else if (data == '0')
    {
      digitalWrite(motorR[0], 0);
      digitalWrite(motorR[1], 0);
      digitalWrite(motorL[0], 0);
      digitalWrite(motorL[1], 0);
    }
    else if (data == '3')
    {
      digitalWrite(motorR[0], 1);
      digitalWrite(motorR[1], 0);
      digitalWrite(motorL[0], 1);
      digitalWrite(motorL[1], 0);
    }
    else if (data == '4')
    {
      digitalWrite(motorR[0], 0);
      digitalWrite(motorR[1], 1);
      digitalWrite(motorL[0], 0);
      digitalWrite(motorL[1], 10);
    }
  }
  
 /*if (digitalRead(6))
  {
    digitalWrite(2, 1);
    digitalWrite(3, 0);
  }
  else if (digitalRead(7))
  {
    digitalWrite(2, 0);
    digitalWrite(3, 1);
  }
  else
  {
    digitalWrite(2, 0);
    digitalWrite(3, 0);
  }

  if (digitalRead(8))
  {
    digitalWrite(4, 1);
    digitalWrite(5, 0);
  }
  else if (digitalRead(9))
  {
    digitalWrite(4, 0);
    digitalWrite(5, 1);
  }
  else
  {
    digitalWrite(4, 0);
    digitalWrite(5, 0);
  }*/
}
