#include <B:\\roboCar\libraries\RF24\nRF24L01.h>
#include <B:\\roboCar\libraries\SPI\SPI.h>
#include <B:\\roboCar\libraries\RF24\RF24.h>
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
    void write(char data[], int size)
    {
        int i=0;
        bool fl=0;
        do{
             this->stopListening();
             fl=RF24::write(&data, size);
             this->startListening();
             if(!fl)
              delay(1*random(1, 5));
        }while((i++<10) && !fl);
    }
};
