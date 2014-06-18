#include "Light.h"

bool Light::is_off = true;

bool Light::isOff() {
    return is_off;
}

void Light::turnOff() {
    is_off = true;

    // TODO: actually turn the light off
    Serial.println("turnOff");
}

void Light::turnOn() {
    is_off = false;

    // TODO: actually turn the light on
    Serial.println("turnOn");
}
