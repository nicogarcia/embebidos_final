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

void Light::initialize() {
    // Sets the light pin as an output
    pinMode(DIGITAL_PIN_LIGHT, OUTPUT);
}

bool Light::isDisabled() {
    return is_disabled;
}

bool Light::isOff() {
    return is_off;
}

void Light::turnOff() {
    is_off = true;

    // Turns the light off
    digitalWrite(DIGITAL_PIN_LIGHT, LOW);
}

void Light::turnOn() {
    is_off = false;

    // Turns the light on
    digitalWrite(DIGITAL_PIN_LIGHT, HIGH);
}
