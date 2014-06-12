#ifndef LCDKEYPAD_DRIVER_H
#define LCDKEYPAD_DRIVER_H

#include <avr/interrupt.h>
// Include special properties of the keypad
#include "LCDKeypadKeys.h"
#include "Driver.h"

// Callback function array parameters
#define CALLBACKS_DEPTH		2
#define KEY_UP_CALLBACK		0
#define KEY_DOWN_CALLBACK	1

// Implement LCDKeypadDriver for the LCDKeypad Shield
class LCDKeypadDriver : public Driver {
public:
    LCDKeypadDriver();

    void initialize();

    // Unimplemented virtual methods, java equivalent of "interface"
    void registerOnKeyDownCallback(void (*handler)(), int key);
    void registerOnKeyUpCallback(void (*handler)(), int key);

private:
    // Array of function pointers that registers callbacks
    void (*callbacks[CALLBACKS_DEPTH][LCDKeypadKeys::KEY_COUNT])();

    // Set if there's a callback to call
    bool event_flag;

    // Function to be called if event_flag is set
    // when control is returned to the main
    // loop through LCDKeypadDriver::Instance->checkEvents()
    void (*function_to_be_called)();

    // Initializes the ADC
    void adc_initialize();


    static void driver_ISR_lcd(int adc_value);
    // ADC ISR
    //friend void driver_ISR(int);

};
extern LCDKeypadDriver KeypadDriver;

#endif
