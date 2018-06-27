//base
#include <Arduino.h>
#include "Manager.h"
#include "pins.h"
#include <config.h>
#include <TimerOne.h>
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

List l;
char* t;
Logger* Log;
Manager* manager;
void setup()
{
  Log = new Logger();

  Log->d("BASE");
  Timer1.initialize(300000);
  manager=new Manager();
  pinMode(14, OUTPUT);
  //manager->makeRadioConnection(true);
}

void loop()
{
  //manager->indicateFreeze();
  //manager->makeRadioConnection();
  //delay(5);
  //manager->debugRadio();
  //delay(300);
  //manager->ackControl();
  manager->maintainRadioConnection();

  /*if(manager->checkRadioConnection(2, 10)){
    Log->d("Connection is active");
  }else{
    Log->e("No connection");
  }*/
  //delay(5);
  //delay(5);
  manager->ackSensors();
  delay(50);
  //Log->i(" ");
}
