#include "MainModule.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Hello world, SISAD!");
    EventModule::initialize();
}

void loop() {
    EventModule::checkEvent();
}
