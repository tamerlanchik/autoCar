#include <SPI.h>                                          // Подключаем библиотеку  для работы с шиной SPI
#include <nRF24L01.h>                                     // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>                                         // Подключаем библиотеку  для работы с nRF24L01+
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
class Trans
{
  private:
    const RF24 radio;
    const LiquidCrystal_I2C lcd;
    static const byte LED=8;
    static const byte BUTTON=7;
    static const byte ledComm = 8;
    static const byte repN=20, randMin=1, randMax=10, randK=5;
    static const int pipeAddress[2]={0x1234567891LL, 0x1234567890LL};
    static const byte channel = 5;
    enum {GETINF, GETSEN, CNTRL, SET};
    static const int serialSpeed = 9600;
    static const byte msgSize = 5;
    
    
    int data[msgSize];
    int cntrl[msgSize];
    int set[msgSize];
    int getsen[msgSize];
    double del;
    bool butState, butStateTemp, ledState;  
  public:
    Trans():radio(9, 10), lcd(0x27,16,2){}
    void init(){
      randomSeed(analogRead(0));
      pinMode(BUTTON, INPUT);
      pinMode(LED, OUTPUT);

      butState = digitalRead(BUTTON);
      ledState = false;
      
      lcd.init();                     
      lcd.backlight();
      //lcd.print("Start");
      
      initRadio(); 

      Serial.begin(serialSpeed);
    }
    void initRadio(){
      radio.begin();                                        // Инициируем работу nRF24L01+
      radio.setChannel(channel);                                  // Указываем канал приёма данных (от 0 до 127), 5 - значит приём данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
      radio.setRetries(15, 10);
      radio.setDataRate     (RF24_250KBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
      radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
      radio.openReadingPipe (1, pipeAddress[0]);            // Открываем 1 трубу с идентификатором 0x1234567890 для приема данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
      radio.openWritingPipe (pipeAddress[1]);
      radio.startListening  (); 
      delay(300);
    }
    void cpy(int src[], int dest[]){
      for(int i=0; i<msgSize; i++)
        dest[i]=src[i];
    }
    void readRadio(){
      bool s, f, r;
      radio.whatHappened(s, f, r);
      lcd.print("y");
      if(r)
      {
        while(radio.available())
        {
          radio.read(&data, sizeof(data));
          lcd.print("hppp");
        }
      }
    }
    bool writeD(int dat[], int len){
      int i=0;
      bool fl=0;
      do{
         radio.stopListening();
         fl=radio.write(dat, sizeof(dat));
         radio.startListening();
         if(!fl)
          delay(randK*random(randMin, randMax));
      }while((i++<repN) && !fl);
      lcd.clear();
      lcd.print(i);
      return fl;
    }
    void readMail()
    {
    }
    void checkBut(){
      if(digitalRead(BUTTON)^butState)
      {
        butState=digitalRead(BUTTON);
        data[0]=CNTRL;
        data[1]=butState;
        writeD(data, sizeof(data));
      }
    }
    void readBut(){
      /*radio.read(&data, sizeof(data));
      if(data[0]==ledComm)
      {
        ledState = data[1];
        digitalWrite(LED, ledState);
      }*/
      byte temp[1];
      while(radio.available())
      {
        radio.read(&temp, sizeof(temp));
        lcd.clear();
        //lcd.print(temp[0]);
        delay(100);
      }
    }
    bool radioAvailable(){
      if(radio.available())
        return true;
      else
        return false;
    }
};
Trans item;
void readRadio(){Serial.println("t");}
void setup(){
  item.init();
  //attachInterrupt(1, readRadio, FALLING);
}

void loop(){
  //item.readMail();
  //item.checkBut();
  if(item.radioAvailable())
  {
    item.readBut();
  }
  if(digitalRead(3))
    Serial.println("1");
}
