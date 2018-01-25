#if !defined(HEADERRE)
#define HEADERRE
#include <RF24.h>
#include "Logger.h"
class RadioExtended : public RF24
{
public:
    RadioExtended(int,int);
    void initRadio(const uint8_t*,const uint8_t*,rf24_datarate_e r);
    bool writee(const char[],int);
};
#endif
