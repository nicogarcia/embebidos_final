#include "LoginTable.h"

LoginTableEntry LoginTable::entries[CAPACITY_LOGIN_TABLE];
uint8_t LoginTable::length;

void LoginTable::addEntry(Username username, Ttl ttl) {
    if(length == CAPACITY_LOGIN_TABLE)
        // The table is full
        return;

    // Creates a new entry
    strcpy(entries[length].username, username);
    entries[length].ttl = ttl;
    length++;
}

LoginTableEntry *LoginTable::getEntries() {
    return entries;
}

LoginTableEntry *LoginTable::getEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if(index < 0)
        // The entry has not been found
        return NULL;

    return &entries[index];
}

int LoginTable::getEntryIndex(Username username) {
    // Searches for the entry
    forn(i, length)
    if(!strcmp(username, entries[i].username))
        // The entry has been found
        return i;

    // The entry has not been found
    return -1;
}

int LoginTable::getLength() {
    return length;
}

void LoginTable::initialize() {
    length = 0;
}

bool LoginTable::isEmpty() {
    return length == 0;
}

bool LoginTable::isFull() {
    return length == CAPACITY_LOGIN_TABLE;
}

void LoginTable::removeEntry(int index) {
    if(index < 0 || index >= CAPACITY_LOGIN_TABLE)
        // Invalid index
        return;

    // Shifts the remaining entries one position back
    forsn(i, index + 1, length)
    entries[i - 1] = entries[i];

    length--;
}

void LoginTable::removeEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if(index < 0)
        // The entry has not been found
        return;

    // Actually removes the entry
    removeEntry(index);
}
