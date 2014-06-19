#include "Light.h"

bool Light::is_disabled;
bool Light::is_off;

void Light::disable() {
    is_disabled = true;

    // Turns off the light
    turnOff();
}

void Light::enable() {
    is_disabled = false;
}

bool Light::isDisabled() {
    return is_disabled;
}

bool Light::isOff() {
    return is_off;
}

void Light::turnOff() {
    is_off = true;

    // TODO: actually turn the light off
}

void Light::turnOn() {
    is_off = false;

    // TODO: actually turn the light on
}
