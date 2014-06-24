#include "LightSensor.h"

LightIntensity LightSensor::light_intensity;

LightIntensity LightSensor::getLightIntensity() {
    return light_intensity;
}

void LightSensor::initialize() {
    light_intensity = UNKNOWN_LIGHT_INTENSITY;
}

void LightSensor::measure() {
    // Measures the light intensity
    light_intensity = analogRead(PIN_LIGHT_SENSOR);
}
