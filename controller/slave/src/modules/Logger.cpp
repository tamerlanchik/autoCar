#include "Logger.h"
Logger::Logger(){
  Serial.begin(115200);
  delay(200);
  Serial.println("DEBUG: Init serial");
}

void Logger::write(void* mess, char mode, char level)const
{
  switch(mode)
  {
    case 'i': Serial.print("I: "); break;
    case 'd': Serial.print("D: "); break;
    case 'e': Serial.print("E: "); break;
    default: break;
  }
  switch(mode)
  {
    case 'd': Serial.println(*((int*)mess));break;
    case 'c': Serial.println(*((char*)mess)); break;
    case 's': Serial.println((char*)mess); break;
    case 'b': Serial.println(*((bool*)mess)); break;
    default: break;
  }
}
void Logger::d(void* mess, char mode)const{
  write(mess, mode, 'd');
}
void Logger::e(void* mess, char mode)const{
  write(mess, mode, 'e');
}
void Logger::i(void* mess, char mode)const{
  write(mess, mode, 'i');
}
