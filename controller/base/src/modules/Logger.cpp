#include "Logger.h"
Logger::Logger(int sRate){
  //Serial.begin(sRate);
}
void Logger::write(char mess[], char mode='i')
{
  /*switch(mode)
  {
    case 'i': Serial.print("INFO: "); break;
    case 'd': Serial.print("DEBUG: "); break;
    case 'e': Serial.print("ERROR: "); break;
    default: break;
  }
  Serial.println(mess);*/
}
void Logger::d(char mess[]){
  //write(mess, 'd');
}
void Logger::e(char mess[]){
  //write(mess, 'e');
}
void Logger::i(char mess[]){
  //write(mess, 'i');
}
Logger log(serialRate);
