#include "LightSensor.h"

LightIntensity LightSensor::light_intensity;

LightIntensity LightSensor::getLightIntensity() {
    return light_intensity;
}

void LightSensor::measure() {
    // Measures the light intensity
    light_intensity = analogRead(PIN_LIGHT_SENSOR);
}
