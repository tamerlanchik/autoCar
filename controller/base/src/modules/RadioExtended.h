#if !defined(HEADERRE)
#define HEADERRE
#include <RF24.h>
class RadioExtended : public RF24
{
public:
    RadioExtended(char,char);
    void initRadio(int*,int*,rf24_datarate_e r);
    bool write(char[],int);
};
#endif
