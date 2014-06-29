#ifndef STATE_MODULE
#define STATE_MODULE

#include "Definitions.h"

class StateModule {
public:
    static Humidity getHumidity();
    static LightIntensity getLightIntensityAverage();
    static Temperature getTemperature();
    static void initialize();
    static bool isLightDisabled();
    static bool isLightOff();
    static bool isLockClosed();
    static void measureLightIntensity();
    static void measureTemperatureAndHumidity();
    static void toggleLight();
    static void toggleLock();
    static void turnOffLight();
    static void turnOnLight();
};

#endif // STATE_MODULE
