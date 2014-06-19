#include "StateModule.h"

Humidity StateModule::getHumidity() {
    return DhtSensor::getHumidity();
}

LightIntensity StateModule::getLightIntensity() {
    return LightSensor::getLightIntensity();
}

Temperature StateModule::getTemperature() {
    return DhtSensor::getTemperature();
}

bool StateModule::isLightDisabled() {
    return Light::isDisabled();
}

bool StateModule::isLockClosed() {
    return Lock::isClosed();
}

void StateModule::measureLightIntensity() {
    LightSensor::measure();
}

void StateModule::measureTemperatureAndHumidity() {
    DhtSensor::measure();
}

void StateModule::toggleLight() {
    if (Light::isDisabled())
        // Light is disabled
        Light::enable();
    else
        // Light is enabled
        Light::disable();
}

void StateModule::toggleLock() {
    if (Lock::isClosed())
        // Lock is closed
        Lock::open();
    else
        // Lock is opened
        Lock::close();
}

void StateModule::turnOffLight() {
    Light::turnOff();
}

void StateModule::turnOnLight() {
    Light::turnOn();
}
