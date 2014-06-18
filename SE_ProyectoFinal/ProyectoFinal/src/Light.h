#ifndef LIGHT
#define LIGHT

#include "Definitions.h"

class Light {
public:
	static bool isOff();
	static void turnOff();
	static void turnOn();
private:
	static bool is_off;
};

#endif /* LIGHT */
