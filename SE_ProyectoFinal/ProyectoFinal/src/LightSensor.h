#ifndef LIGHT_SENSOR
#define LIGHT_SENSOR

#include "Definitions.h"

class LightSensor {
public:
    static LightIntensity getLightIntensityAverage();
    static void initialize();
    static void measure();
private:
    static LightIntensity light_intensity_sum;
};

#endif /* LIGHT_SENSOR */
