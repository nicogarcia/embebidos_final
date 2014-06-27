#include "LightSensor.h"

LightIntensity LightSensor::light_intensity_sum;

LightIntensity LightSensor::getLightIntensityAverage() {
    return light_intensity_sum / LightIntensityQueue::getLength();
}

void LightSensor::initialize() {
    light_intensity_sum = 0;

    // Modules initializations
    LightIntensityQueue::initialize();

    // Initializes the registry with the maximum light intensity
    LightIntensityQueue::push(LIGHT_INTENSITY_MAX);
    light_intensity_sum += LIGHT_INTENSITY_MAX;
}

void LightSensor::measure() {
    // Measures the light intensity
    LightIntensity light_intensity = analogRead(ANALOG_PIN_LIGHT_SENSOR);

    if (LightIntensityQueue::isFull()) {
        // The queue is full
        // Removes the oldest light intensity record
        light_intensity_sum -= LightIntensityQueue::getFront();
        LightIntensityQueue::pop();
    }

    // Records the measured light intensity
    LightIntensityQueue::push(light_intensity);
    light_intensity_sum += light_intensity;
}
