#include "LightSensor.h"

LightIntensity LightSensor::light_intensity; // TODO: assign default value

LightIntensity LightSensor::getLightIntensity() {
    return light_intensity;
}

void LightSensor::measure() {
    // TODO: actually measure light (and assign it to light_intensity)
}
