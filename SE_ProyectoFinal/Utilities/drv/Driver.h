#ifndef DRIVER_H_
#define DRIVER_H_

#include "Arduino.h"
#include "Dispatcher.h"

class Driver {

public:
    Driver();
    // Set analog reference
    byte analog_reference;

    //If it's true it will execute the next ADC conversion of driver's ADC
    bool enabled;

    //Function to do after the conversion
    fptr callback;

    //Function to do in the interruption
    void (*isr_func)(int);

    //The function to do
    void driver_ISR(int adc_value);

    //the time between execution of the function
    unsigned long time;

    //the last time the function was execute
    unsigned long last_execution;

    enum REFERENCES {
        REF_DEFAULT = 1,
        REF_INTERNAL_1V1 = 3
    };

private:

};

#endif /* DRIVER_H_ */