#include "Log.h"
Log::Log(){
  Serial.begin(serialRate);
}
void Log::write(char mess[], char mode='i'){};
void Log::d(char mess[]){};
void Log::e(char mess[]){};
void Log::i(char mess[]){};
