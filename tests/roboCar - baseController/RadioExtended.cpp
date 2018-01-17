#include <nRF24L01.h>
#include <SPI.h>
#include <RF24.h>
class RadioExtended  : public RF24
{
public:
    RadioExtended(char  a, char b):RF24(a, b){
    }
    void initRadio(int*  adr1, int* adr2, rf24_datarate_e r){
        this->begin();
        this->setDataRate(r); // RF24_1MBPS §Ú§Ý§Ú RF24_2MBPS
        this->openReadingPipe(1,*adr1); // §à§ä§Ü§â§í§ä§î §Ü§Ñ§ß§Ñ§Ý §ß§Ñ §á§â§Ú§×§Þ
        this->openWritingPipe(*adr2);
        this->startListening();
    }
};
