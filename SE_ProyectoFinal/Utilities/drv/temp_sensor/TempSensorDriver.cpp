#include "TempSensorDriver.h"
#include "Dispatcher.h"
#define TEMP_ADC_CONST 0.107421875

TempSensorDriver_ lm35;

// FIXME: Should not be static, to be removed
double TempSensorDriver_::temperature;

void TempSensorDriver_::driver_ISR_temp(int value) {
    TempSensorDriver_::temperature = TEMP_ADC_CONST * value ;
    //PORTB ^= (1 << PB5);
    Dispatcher.enqueueReadyFunction(lm35.callback);
}

void TempSensorDriver_::initialize() {
    time = 130;
    enabled = true;
    isr_func = driver_ISR_temp;
    analog_reference = REF_INTERNAL_1V1;
}
