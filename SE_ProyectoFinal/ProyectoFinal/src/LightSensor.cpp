#include "LightSensor.h"

LightIntensity LightSensor::light_intensity;

LightIntensity LightSensor::getLightIntensity() {
    return light_intensity;
}

void LightSensor::measure() {
    // TODO: actually measure light (and assign it to light_intensity)
    light_intensity = 24; // TODO: just to debug
}
