#include "StateModule.h"

Humidity StateModule::getHumidity() {
	return DhtSensor::getHumidity();
}

Temperature StateModule::getTemperature() {
	return DhtSensor::getTemperature();
}

bool StateModule::isLightOff() {
	return Light::isOff();
}

bool StateModule::isLockClosed() {
	return Lock::isClosed();
}

void StateModule::measureHumidityAndTemperature() {
	DhtSensor::measure();
}

void StateModule::toggleLight() {
	if (Light::isOff())
		// Light is off
		Light::turnOn();
	else
		// Light is on
		Light::turnOff();
}

void StateModule::toggleLock() {
	if (Lock::isClosed())
		// Lock is closed
		Lock::open();
	else
		// Lock is opened
		Lock::close();
}
