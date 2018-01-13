#include <SPI.h>                                          // Подключаем библиотеку  для работы с шиной SPI
#include <nRF24L01.h>                                     // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>                                         // Подключаем библиотеку  для работы с nRF24L01+
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
class Queue
{
private:
    struct list1
    {
        int val;
        list1* next;
    };
    list1* first;
    list1* last;
public:
    Queue()
    {
        first=new list1;
        last = first;
    }
    void put(int a)
    {
        list1* newLink = new list1;
        newLink->next = NULL;
        last->val=a;
        last->next = newLink;
        last=newLink;
    }
    int get()
    {
        if(first->next!=NULL){
            int res=first->val;
            list1* temp=first;
            first=first->next;
            delete temp;
            return res;
        }
        else{
            return 0;
        }
    }
    bool isEnd()
    {
        if (first->next == NULL)
            return true;
        else
            return false;
    }
};
class Trans
{
  private:
    static const RF24 radio;
    static const LiquidCrystal_I2C lcd;
    static const byte LED=8;
    static const byte BUTTON=7;
    static const byte ledComm = 8;
    static const byte repN=20, randMin=1, randMax=10, randK=5;
    byte data[2];
    double del;
    bool butState, butStateTemp, ledState;  
  public:
    Trans(){}
    void init(){
      randomSeed(analogRead(0));
      pinMode(BUTTON, INPUT);
      pinMode(LED, OUTPUT);

      butState = digitalRead(BUTTON);
      ledState = false;
      lcd.init();                     
      lcd.backlight();
      lcd.print("Start");

      radio.begin();                                        // Инициируем работу nRF24L01+
      radio.setChannel(5);                                  // Указываем канал приёма данных (от 0 до 127), 5 - значит приём данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
      radio.setRetries(15, 10);
      radio.setDataRate     (RF24_250KBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
      radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
      radio.openReadingPipe (1, 0x1234567891LL);            // Открываем 1 трубу с идентификатором 0x1234567890 для приема данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
      radio.openWritingPipe (0x1234567890LL);
      radio.startListening  (); 
    }
    bool writeD(byte dat[], int len){
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
    void checkBut(){
      if(digitalRead(BUTTON)^butState)
      {
        butState=digitalRead(BUTTON);
        data[0]=ledComm;
        data[1]=butState;
        writeD(data, sizeof(data));
      }
    }
    void readBut(){
      radio.read(&data, sizeof(data));
      if(data[0]==ledComm)
      {
        ledState = data[1];
        digitalWrite(LED, ledState);
      }
    }
    bool radioAvailable(){
      if(radio.available())
        return true;
      else
        return false;
    }
};
const RF24 Trans::radio(9, 10);
const LiquidCrystal_I2C Trans::lcd(0x27,16,2);
Trans item;
void setup(){
  item.init();
  delay(500);
}

void loop(){
  item.checkBut();
  if(item.radioAvailable())
  {
    item.readBut();
  }
}
