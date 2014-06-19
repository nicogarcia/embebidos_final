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

LoginTableEntry *LoginTable::getEntries() {
    return entries;
}

LoginTableEntry *LoginTable::getEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if (index < 0)
        // The entry has not been found
        return NULL;

    return &entries[index];
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

int LoginTable::getLength() {
    return length;
}

bool LoginTable::isFull() {
    return length == LOGIN_TABLE_CAPACITY;
}

void LoginTable::removeEntry(int index) {
    if (index < 0 || index >= LOGIN_TABLE_CAPACITY)
        // Invalid index
        return;

    // Shifts the remaining entries one position back
    forsn (i, index + 1, length)
    entries[i - 1] = entries[i];

    length--;
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
