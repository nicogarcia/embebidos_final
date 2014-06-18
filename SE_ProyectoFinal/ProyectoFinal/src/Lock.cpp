#include "Lock.h"

bool Lock::is_closed = true;

void Lock::close() {
    is_closed = true;

    // TODO: actually close the lock
    Serial.println("close");
}

bool Lock::isClosed() {
    return is_closed;
}

void Lock::open() {
    is_closed = false;

    // TODO: actually open the lock
    Serial.println("open");
}
