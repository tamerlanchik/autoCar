//base
#define DEBUG
#include <Arduino.h>
#include "Manager.h"
#include "pins.h"
#include <config.h>
unsigned long tim = 0;

class ListItem{
  public:
      char data;
      ListItem* prev;
      ListItem* next;
      ListItem(char dat){
          data = dat;
          prev = NULL;
          next = NULL;
      }
};
class List{
  private:
      ListItem* first;
      ListItem* current;
  public:
      List(){
          first = NULL;
          current = NULL;
      }
      void add(char dat){
          ListItem* temp = new ListItem(dat);
          temp->prev = current;
          if(current!=NULL){
              current->next = temp;
          }
          current = temp;
          if(!first){
              first = current;
          }
      }
      char pop(){
          if(first){
              char temp = first->data;
              ListItem* t = first->next;
              delete first;
              first = t;
              if(!t){
                  current = NULL;
              }
              return temp;
          }else{
              return 0;
          }
      }
      bool isEmpty(){
          if(first==NULL){
              return true;
          }else{
              return false;
          }
      }

};

char* t;
Logger* Log;
Manager* manager;
void setup()
{
  Log = new Logger();

  Log->d("BASE");
  manager=new Manager();
  //manager->makeRadioConnection(true);
}

void loop()
{
  manager->retranslate();
  //manager->readSerial();
  //manager->indicateFreeze();
  //manager->makeRadioConnection();
  //delay(5);
  //manager->debugRadio();
  //delay(300);
  //manager->ackControl();
  //manager->maintainRadioConnection();

  /*if(manager->checkRadioConnection(2)){
    Log->d("Connection is active");
  }else{
    Log->e("No connection");
  }
  delay(100);*/
  //delay(5);
  //delay(5);
  //manager->ackSensors();
  //delay(50);
  //Log->i(" ");
}
