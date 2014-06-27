#include "UserTable.h"

UserTableEntry UserTable::entries[CAPACITY_USER_TABLE];
uint8_t UserTable::length;

void UserTable::addEntry(Username username, Password password, Role role) {
    if (length == CAPACITY_USER_TABLE)
        // The table is full
        return;

    // Creates a new entry
    strcpy(entries[length].username, username);
    strcpy(entries[length].password, password);
    entries[length].role = role;
    length++;

    // Updates the table state in the EEPROM
    UserTableEeprom::writeEntry(length - 1, &entries[length - 1]);
    UserTableEeprom::writeLength(length);
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
    forn (i, length) {
        if (strcmp(username, entries[i].username) == 0)
            // The entry has been found
            return i;
    }

    // The entry has not been found
    return -1;
}

uint8_t UserTable::getLength() {
    return length;
}

void UserTable::initialize() {
#ifdef EEPROM_INITIALIZATION_MODE
    // Writes in the EEPROM the length of the table (initially, 0)
    UserTableEeprom::writeLength(0);
#endif // EEPROM_INITIALIZATION_MODE

    // Reads the table entries from the EEPROM
    length = UserTableEeprom::readEntries(entries);
}

bool UserTable::isEmpty() {
    return length == 0;
}

bool UserTable::isFull() {
    return length == CAPACITY_USER_TABLE;
}

void UserTable::removeEntry(int index) {
    if (index < 0 || index >= CAPACITY_USER_TABLE)
        // Invalid index
        return;

    // Replaces the entry with the last entry
    entries[index] = entries[length - 1];
    length--;

    // Updates the table state in the EEPROM
    UserTableEeprom::writeEntry(index, &entries[index]);
    UserTableEeprom::writeLength(length);
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
