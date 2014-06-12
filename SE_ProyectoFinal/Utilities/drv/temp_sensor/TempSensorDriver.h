#ifndef TEMPSENSORDRIVER_H_
#define TEMPSENSORDRIVER_H_
#include "Driver.h"

class TempSensorDriver_ : public Driver {
public:
    void initialize();
    // FIXME: This should not be static
    static double temperature;

    //static void driver_ISR(int value);
    static void driver_ISR_temp( int value );
};
extern TempSensorDriver_ lm35;

#endif /* TEMPSENSORDRIVER_H_ */