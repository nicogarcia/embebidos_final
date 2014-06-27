#ifndef LIGHT
#define LIGHT

#include "Definitions.h"

class Light {
public:
    static void disable();
    static void enable();
    static void initialize();
    static bool isDisabled();
    static bool isOff();
    static void turnOff();
    static void turnOn();
private:
    static bool is_disabled;
    static bool is_off;
};

#endif // LIGHT
