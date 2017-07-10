const char motor[4]= {2, 3, 4, 5};
const char bord[4] = {6, 7, 8, 9};
//const char joy[2] = {A0, A1};
//int zeroJ[2];
int gaz, rot;
const char moveTemp[5][4] = {   {0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0} };
void serialEvent()
{
  unsigned char temp;
  const unsigned char stopper = '$';
  unsigned char *data = new unsigned char [30];
  unsigned int i = 0;
  while (true){
    if (Serial.available())
    {
      temp = char(Serial.read());
      if (temp != stopper)
        data[i++] = temp;
      else
        break;
    }
  }
  unsigned int *j = new unsigned int;
  *j = 0;
  while (data[*j]!='/'){
    if (data[*j] == '-')
      rot *= -1;
    else
      rot *= 10 + (data[*j++]-'0');
  }
  *j++;
  while (*j <= i){
    if (data[*j] == '-')
      gaz *= -1;
    else
      gaz *= 10 + (data[*j++]-'0');
  }
  delete j;
  delete [] data;

  if (gaz == 0 && rot == 0)
  {
    changeMoving(0);
  }
  else if (gaz > 0) {
   changeMoving(1);
  }
  else if (gaz < 0) {
   changeMoving(2);
  }
  else if (rot > 0) {
   changeMoving(3);
  }
  else if (rot < 0) {
   changeMoving(4);
  }
}
void changeMoving(int numb)
{
  for(unsigned int i = 0; i<4; i++)
    digitalWrite(motor[i], moveTemp[numb][i]);
}
void setup() {
  Serial.begin(9600);
  for(char i = 0; i<4; i++)
  {
    pinMode(motor[i], true);
    pinMode(bord[i*2], INPUT);
    pinMode(bord[(i+1)*2], INPUT);
    //zeroJ[i] = analogRead(joy[i]);
  }
}
/*
moving template:
  1) Stop:  {0, 0, 0, 0}
  2) Move Forvard: {1, 0, 1, 0]
  3) Move Backward: {0, 1, 0, 1}
  4) Rotate Left: {1, 0, 0, 1}
  5) Rotate Right: {0, 1, 1, 0}
 
 
 */
void loop() {
  for (unsigned char i = 0; i<4; i++)
  {
    if digitalRead(bord[i]) == true
    {
      changeMoving(0);
    }
  }
}
