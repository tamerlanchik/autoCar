#if !defined(HEADERRE)
#define HEADERRE
#include <RF24.h>
#include "Logger.h"
class RadioExtended : public RF24
{
public:
    RadioExtended(char,char);
    void initRadio(const uint8_t*,const uint8_t*,rf24_datarate_e r);
    bool write(const char[],int);
};
#endif
