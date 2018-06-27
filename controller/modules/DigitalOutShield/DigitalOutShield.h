#if !defined(HEADERDSH)
#define HEADERDSH
#include <Arduino.h>
#include <SPI.h>

  class DigitalOutShield {
  private:
    unsigned char SS;           //Номер контакта SS (Выбор Ведомого)
    unsigned char count;        //Число модулей в каскаде
    unsigned char LOCK;         //Номер контакта для отключения/подкючения подачи значений на выходы регистра
    bool* values;               //Массив значений выводов
    bool writeShift();          //Отправка серии данных
    void writeSPI(byte);        //Отправка байта
  public:
    //Параметры: количество модулей регистров (для каскада), номер вывода SS
    DigitalOutShield(unsigned char, unsigned char);

    //Параметры: количество модулей регистров (для каскада), номер вывода SS,
    //номер вывода для отключения/подкючения подачи значений на выходы регистра
    DigitalOutShield(unsigned char, unsigned char, unsigned char);

    //Инициализация (установка pinMode и запуск SPI)
    void init();

    //Обновить значение пина pin значением value
    bool write(unsigned char, bool);

    //Отправить байт данных
    bool write(byte);

    //Добавить в буфер значение value на позицию pin
    bool add(unsigned char, bool);

    //Отправить добавленные с помощью add() данные
    bool send();

    //Включить подачу значений на выходы регистра
    void attach();

    //Отключить подачу значений на выходы регистра
    void detach();

    //Обнулить буфер
    void zeroBuffer(bool = 0);
  };

#endif
