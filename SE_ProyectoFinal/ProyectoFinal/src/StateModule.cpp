#include "StateModule.h"

void StateModule::closeLock() {
    Lock::close();
}

void StateModule::disableLight() {
    Light::disable();
}

void StateModule::enableLight() {
    Light::enable();
}

Humidity StateModule::getHumidity() {
    return DhtSensor::getHumidity();
}

LightIntensity StateModule::getLightIntensityAverage() {
    return LightSensor::getLightIntensityAverage();
}

Temperature StateModule::getTemperature() {
    return DhtSensor::getTemperature();
}

void StateModule::initialize() {
    // Modules initializations
    DhtSensor::initialize();
    Light::initialize();
    LightSensor::initialize();
    Lock::initialize();

    // State initialization tasks
    closeLock();
    disableLight();
    measureLightIntensity();
    measureTemperatureAndHumidity();
}

bool StateModule::isLightDisabled() {
    return Light::isDisabled();
}

bool StateModule::isLightOff() {
    return Light::isOff();
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

void StateModule::openLock() {
    Lock::open();

    // Resets the lock closing event time
    MainModule::resetEventTime(LOCK_CLOSING);
}

void StateModule::toggleLight() {
    if (Light::isDisabled())
        // The light is disabled
        Light::enable();
    else
        // The light is enabled
        Light::disable();
}

void StateModule::toggleLock() {
    if (Lock::isClosed())
        // The lock is closed
        Lock::open();
    else
        // The lock is opened
        Lock::close();
}

void StateModule::turnOffLight() {
    Light::turnOff();
}

void StateModule::turnOnLight() {
    Light::turnOn();
}
