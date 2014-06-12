#ifndef LCDKEYPADKEYS_H
#define LCDKEYPADKEYS_H

// Describes LCDKeypad keys and converts
// an analog signal to a key
class LCDKeypadKeys {
public:
    enum Keys {
        KEY_RIGHT = 0,
        KEY_UP = 1,
        KEY_DOWN = 2,
        KEY_LEFT = 3,
        KEY_SELECT = 4
    };

    static const char* KEY_NAMES[];

    static const int KEY_COUNT = 5;

    static int GetKey(int analog_input);

private:
    static int ADCKeyValues[];
};

#endif
