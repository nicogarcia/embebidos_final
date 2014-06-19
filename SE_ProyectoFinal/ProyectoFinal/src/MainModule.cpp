#include "MainModule.h"

void setup() {
    // Initializes the system
    EventModule::initializeSystem();
}

void loop() {
    // Checks for an event
    EventModule::checkEvent();
}
