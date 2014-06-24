#include "Lock.h"

bool Lock::is_closed;

void Lock::close() {
    is_closed = true;

    // Closes the lock
    digitalWrite(PIN_LOCK, HIGH);
}

bool Lock::isClosed() {
    return is_closed;
}

void Lock::open() {
    is_closed = false;

    // Opens the lock
    digitalWrite(PIN_LOCK, LOW);
}
