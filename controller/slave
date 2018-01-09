#include <SPI.h>                                          // Подключаем библиотеку  для работы с шиной SPI
#include <nRF24L01.h>                                     // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>                                         // Подключаем библиотеку  для работы с nRF24L01+
#include <Wire.h> 
RF24           radio(9, 10);                              // Создаём объект radio   для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
byte            data[2];
int t;
double del;
const byte LED=8;
const byte BUTTON=7;
const byte ledComm = 8;
bool flag=1;
bool butState, butStateTemp, ledState;
int i=0;
void setup(){
    pinMode(BUTTON, INPUT);
    pinMode(LED, OUTPUT);
    butState = digitalRead(BUTTON);
    ledState = false;
    radio.begin();                                        // Инициируем работу nRF24L01+
    radio.setChannel(5);                                  // Указываем канал приёма данных (от 0 до 127), 5 - значит приём данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
    radio.setDataRate     (RF24_250KBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
        radio.setRetries(5, 10);
    //radio.enableAckPayload();
    radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
    radio.openReadingPipe (1, 0x1234567890LL);            // Открываем 1 трубу с идентификатором 0x1234567890 для приема данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
    radio.openWritingPipe (0x1234567891LL);
    radio.startListening  ();                             // Включаем приемник, начинаем прослушивать открытую трубу
    t=0;
//  radio.stopListening   ();                             // Выключаем приёмник, если потребуется передать данные
}
void loop(){
    if(digitalRead(BUTTON)^butState)
  {
    butState=digitalRead(BUTTON);
    data[0]=ledComm;
    data[1]=butState;
    radio.stopListening();
    i=0;
    //while((i++<20) && !radio.write(&data, 2)) delay(50);
    radio.write(&data, 2);
    delay(300);
    radio.startListening();
  }
  if(radio.available())
  {
    radio.read(&data, sizeof(data));
    if(data[0]==ledComm)
    {
      ledState = data[1];
      digitalWrite(LED, ledState);
    }
    //radio.writeAckPayload(1, &t, sizeof(t));
    t++;
  }
}
