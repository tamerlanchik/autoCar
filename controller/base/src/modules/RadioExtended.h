#if !defined(HEADERRE)
#define HEADERRE
#include <RF24.h>
#include "Logger.h"
class RadioExtended : public RF24
{
private:
  unsigned int connectionTimeout;
public:
    unsigned long int lastConnectionTime;
    RadioExtended(int,int,const uint8_t*,const uint8_t*,rf24_datarate_e,rf24_pa_dbm_e,bool);
    bool writeChecked(void*,int);
    bool write(void*,int);
    bool debugAckPayloads(void*,int,void*);
    bool ackRequest(void*,int,void*);
    bool isTimeToCheckConnection();
};
#endif
