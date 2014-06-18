#ifndef STATE_MODULE
#define STATE_MODULE

#include "Definitions.h"

class StateModule {
public:
	static Humidity getHumidity();
	static Temperature getTemperature();
	static bool isLightOff();
	static bool isLockClosed();
	static void measureHumidityAndTemperature();
	static void toggleLight();
	static void toggleLock();
};

#endif /* STATE_MODULE */
