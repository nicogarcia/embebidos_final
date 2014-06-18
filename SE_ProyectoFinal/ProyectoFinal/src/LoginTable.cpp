#include "LoginTable.h"

LoginTableEntry LoginTable::entries[LOGIN_TABLE_CAPACITY];
int LoginTable::length = 0;

void LoginTable::addEntry(Username username, Ttl ttl) {
    if (length == LOGIN_TABLE_CAPACITY)
        // The table is full
        return;

    // Creates a new entry
    entries[length].username = username;
    entries[length].ttl = ttl;
    length++;
}

void LoginTable::decrementTtls() {
    // Decrements the TTLs
    forn (i, length)
    entries[i].ttl--;
}

LoginTableEntry *LoginTable::getEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if (index < 0)
        // The entry has not been found
        return NULL;

    return &entries[index];
}

bool LoginTable::isFull() {
    return length == LOGIN_TABLE_CAPACITY;
}

void LoginTable::removeEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if (index < 0)
        // The entry has not been found
        return;

    // Actually removes the entry
    removeEntry(index);
}

void LoginTable::removeExpiredEntries() {
    forn (i, length)
    if (entries[i].ttl <= 0) {
        // The entry has expired
        removeEntry(i);
        i--; // The next index to check is the same of the entry that was removed
    }
}

int LoginTable::getEntryIndex(Username username) {
    // Searches for the entry
    forn (i, length)
    if (username == entries[i].username)
        // The entry has been found
        return i;

    // The entry has not been found
    return -1;
}

void LoginTable::removeEntry(int index) {
    // Shifts the remaining entries one position back
    forsn (i, index + 1, length)
    entries[i - 1] = entries[i];

    length--;
}
