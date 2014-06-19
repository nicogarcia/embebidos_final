#include "Lock.h"

bool Lock::is_closed;

void Lock::close() {
    is_closed = true;

    // TODO: actually close the lock
}

bool Lock::isClosed() {
    return is_closed;
}

void Lock::open() {
    is_closed = false;

    // TODO: actually open the lock
}
