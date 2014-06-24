#ifndef LIGHT_SENSOR
#define LIGHT_SENSOR

#include "Definitions.h"

class LightSensor {
public:
    static LightIntensity getLightIntensity();
    static void initialize();
    static void measure();
private:
    static LightIntensity light_intensity;
};

#endif /* LIGHT_SENSOR */
