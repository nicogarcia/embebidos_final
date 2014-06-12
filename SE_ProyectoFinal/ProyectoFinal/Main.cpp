#include "Arduino.h"
#include "Dispatcher.h"

void setup() {

}

void loop() {
    // Check and execute if there were events triggered
    Dispatcher.checkEvents();
}