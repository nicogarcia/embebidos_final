#include "ADCManager.h"
#include "util/delay.h"
#include "Arduino.h"

ADCManager_ ADCManager;
void (*ADCManager_::vref_setters[ADCManager_::CANT_ADC])() = {
    vref_setter_ch0,
    vref_setter_ch1,
    vref_setter_ch2,
    vref_setter_ch3,
    vref_setter_ch4,
    vref_setter_ch5,
};

ADCManager_::ADCManager_() {
    for(uint8_t i = 0; i < CANT_ADC; i++)
        drivers[i] = NULL;
    current = 0;
    adc_initializer();
}

void ADCManager_::insertDriver(Driver* driver, uint8_t adc) {
    if(adc < CANT_ADC) {
        noInterrupts();

        drivers[adc] = driver;
        Dispatcher.attach(Task(driver->time, vref_setters[adc]));

        interrupts();
    }
}

// ADC initialization routine
void ADCManager_::adc_initializer() {
    // Based on example found in http://maxembedded.com/2011/06/20/the-adc-of-the-avr/
    noInterrupts();

    //Set the ADC reference and the channel to read
    //REFS1 = 0 and REFS0 = 0 means externarl reference (AREF)
    //REFS1 = 0 and REFS0 = 1 means Vcc reference 5V
    //REFS1 = 1 and REFS0 = 1 means internal reference 1.1V (for Arduino UNO)
    ADMUX = (1 << REFS1) | (1 << REFS0) | (current & 0x07) ;

    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    /**
    * ADEN: ADC Enable set to 1 to enable de ADC
    * ADIE: ADC Interrupt Enable. Set to 1 to enable de ADC interrupts
    * ADPS2::0: The prescalar is define by this three bits. 111 means 128.
    **/
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    interrupts();
}

volatile int channel_to_read = -1;
volatile bool adc_running = false;

void ADC_vect() {
    if(channel_to_read == -1)
        return;
    //Current driver to 'execute'.
    Driver *current_driver = ADCManager.drivers[channel_to_read];

    //If its time to execute the current driver the it's enable
    if(current_driver->enabled)
        current_driver->driver_ISR(ADC);

    channel_to_read = -1;

    // Set ADC as idle
    adc_running = false;

    // Disable Sleep Mode
    SMCR = 0;
}

void ADCManager_::vref_setter_common(int channel) {

}

//Set the SMCR and the ADCSRA registers to start a conversion in the ADC
void start_adc_conversion() {
    // Set adc as started
    adc_running = true;

    // Enable ADC Noise Reduction Mode
    SMCR = (1 << SE) | (1 << SM0);

    // Actually start ADC
    ADCSRA |= (1 << ADSC);
}

int count = 0;
void ADCManager_::vref_setter_ch0() {
    int channel = 0;
    Driver* current_driver = ADCManager.drivers[channel];

    if(!adc_running) {
        channel_to_read = channel;

        // Set channel and reference
        ADMUX = (current_driver->analog_reference << REFS0) | (channel & 0x07);

        // Start adc conversion
        start_adc_conversion();
        count = 0;
    }

    Dispatcher.attach(Task(current_driver->time, vref_setter_ch0));
}

void ADCManager_::vref_setter_ch1() {
    int channel = 1;
    Driver* current_driver = ADCManager.drivers[channel];

    // Wait for adc to finish
    while(adc_running);

    // Set channel and reference
    channel_to_read = channel;
    ADMUX = (current_driver->analog_reference << REFS0) | (channel & 0x07);

    // Wait for reference to be set
    _delay_ms(10);

    // Start ADC
    start_adc_conversion();

    Dispatcher.attach(Task(current_driver->time, vref_setter_ch1));
}

void ADCManager_::vref_setter_ch2() {

}

void ADCManager_::vref_setter_ch3() {

}

void ADCManager_::vref_setter_ch4() {

}

void ADCManager_::vref_setter_ch5() {

}