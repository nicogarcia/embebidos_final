#include "Driver.h"

Driver::Driver () {
    time = 0;
    last_execution = 0;
    callback = NULL;
    enabled = false;
    analog_reference = REF_DEFAULT;
}

void Driver::driver_ISR( int adc_value ) {
    isr_func(adc_value);
}