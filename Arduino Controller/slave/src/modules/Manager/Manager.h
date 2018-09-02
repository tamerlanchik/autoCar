//slave
#if !defined(HEADCOM)
#define HEADCOM
#include "Logger.h"
#include "Chassis.h"
#include <pins.h>
class Manager{
private:
  Chassis* chassis;
public:
    Manager();
    void testing();
};
#endif
