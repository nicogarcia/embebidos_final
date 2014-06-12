#include "LCDKeypadKeys.h"

// Threshold values for AD conversion
int LCDKeypadKeys::ADCKeyValues[LCDKeypadKeys::KEY_COUNT] = { 30, 200, 360, 535, 760 };

// Key names for text I/O
const char* LCDKeypadKeys::KEY_NAMES[LCDKeypadKeys::KEY_COUNT] = { "RIGHT", "UP", "DOWN", "LEFT", "SELECT"};

// Converts an analog input to digital using threshold values
int LCDKeypadKeys::GetKey(int analog_input) {
    int k;
    for (k = 0; k < KEY_COUNT; k++)
        if (analog_input < ADCKeyValues[k])
            return k;

    if (k >= KEY_COUNT)
        k = -1;     // No valid key pressed

    return k;
}