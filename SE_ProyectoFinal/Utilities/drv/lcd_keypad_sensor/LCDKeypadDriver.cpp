#include "Arduino.h"
#include "LCDKeypadDriver.h"
#include "Dispatcher.h"
#include <avr/io.h>
#include <avr/interrupt.h>

LCDKeypadDriver KeypadDriver;

// Contructor
LCDKeypadDriver::LCDKeypadDriver() {
    event_flag = false;

    for(int i = 0; i < LCDKeypadKeys::KEY_COUNT; i++) {
        callbacks[KEY_UP_CALLBACK][i] = NULL;
        callbacks[KEY_DOWN_CALLBACK][i] = NULL;
    }
}

void LCDKeypadDriver::initialize() {
    time = 1;
    enabled = true;
    isr_func = driver_ISR_lcd;
}

// Registers the callback function for the keydown event of the corresponding key
void LCDKeypadDriver::registerOnKeyDownCallback(void (*handler)(), int key) {
    callbacks[KEY_DOWN_CALLBACK][key] = handler;
}

// Registers the callback function for the keyup event of the corresponding key
void LCDKeypadDriver::registerOnKeyUpCallback(void (*handler)(), int key) {
    callbacks[KEY_UP_CALLBACK][key] = handler;
}

/************************************************************************
	Code to handle interrupts
	TIMER1_COMPA_vect y ADC_vect are LCDKeypadDriver 'friends' so
	they have access to its members (like callbacks array, defines, etc)
************************************************************************/

// Key ISR variables
volatile int last_key = -1;
volatile int current_key = -1;
volatile int callback_type = -1;
volatile int key_involved = -1;
volatile int last_key_before_db = -1;
volatile bool finish_debouncing = false;
volatile bool bouncing = false;

//  Debouncing callback
void debouncing() {
    finish_debouncing = true;
    bouncing = false;
}

// Key ISR
void LCDKeypadDriver::driver_ISR_lcd(int adc_value) {
    // Read digital value from ADC register
    current_key = LCDKeypadKeys::GetKey(adc_value);

    // Test if there were changes (keyup or keydown)
    if(last_key != current_key) {
        // Toggle led when there's a change in state (for debugging)
        //PORTB ^= (1 << PB5);

        if(!bouncing) {
            last_key_before_db = last_key;
            // Wait for timer to launch the next ADC conversion after debouncing period
            Dispatcher.attach(Task(30, debouncing));
            bouncing = true;
        }

        // Update last key
        last_key = current_key;
    }

    if(finish_debouncing) {
        // key_involved stores the key being pushed or released
        // to access the callbacks array
        key_involved = (last_key_before_db == -1) ? current_key : last_key_before_db;

        // Use last_key to set if there was keyup or keydown
        // and store it in callback_type for direct access
        callback_type = (last_key_before_db == -1) ? KEY_DOWN_CALLBACK : KEY_UP_CALLBACK;

        // If there's a callback for current key and action, set its callback to be launched
        if(KeypadDriver.callbacks[callback_type][key_involved] != NULL)
            Dispatcher.enqueueReadyFunction(KeypadDriver.callbacks[callback_type][key_involved]);

        finish_debouncing = false;
    }
}