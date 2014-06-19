#include "UserTable.h"

UserTableEntry UserTable::entries[USER_TABLE_CAPACITY];
int UserTable::length = 0;

void UserTable::addEntry(Username username, Password password, Role role) {
    if (length == USER_TABLE_CAPACITY)
        // The table is full
        return;

    // Creates a new entry
    entries[length].username = username;
    entries[length].password = password;
    entries[length].role = role;
    length++;
}

UserTableEntry *UserTable::getEntries() {
    return entries;
}

UserTableEntry *UserTable::getEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if (index < 0)
        // The entry has not been found
        return NULL;

    return &entries[index];
}

int UserTable::getEntryIndex(Username username) {
    // Searches for the entry
    forn (i, length)
    if (username == entries[i].username)
        // The entry has been found
        return i;

    // The entry has not been found
    return -1;
}

int UserTable::getLength() {
    return length;
}

bool UserTable::isFull() {
    return length == USER_TABLE_CAPACITY;
}

void UserTable::removeEntry(int index) {
    // Shifts the remaining entries one position back
    forsn (i, index + 1, length)
    entries[i - 1] = entries[i];

    length--;
}

void UserTable::removeEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if (index < 0)
        // The entry has not been found
        return;

    // Actually removes the entry
    removeEntry(index);
}
