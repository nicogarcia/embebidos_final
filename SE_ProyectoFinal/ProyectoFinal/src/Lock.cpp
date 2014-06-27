#include "Lock.h"

bool Lock::is_closed;

void Lock::close() {
    is_closed = true;

    // Closes the lock
    digitalWrite(DIGITAL_PIN_LOCK, HIGH);
}

void Lock::initialize() {
    // Sets the lock pin as an output
    pinMode(DIGITAL_PIN_LOCK, OUTPUT);
}

bool Lock::isClosed() {
    return is_closed;
}

void Lock::open() {
    is_closed = false;

    // Opens the lock
    digitalWrite(DIGITAL_PIN_LOCK, LOW);
}
