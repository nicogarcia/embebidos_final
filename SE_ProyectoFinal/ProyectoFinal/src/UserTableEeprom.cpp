#include "UserTableEeprom.h"

uint8_t UserTableEeprom::readEntries(UserTableEntry entries[CAPACITY_USER_TABLE]) {
    // Reads the table length
    uint8_t length = eeprom_read_byte((uint8_t *) USER_TABLE_EEPROM_LENGTH_ADDRESS);

    // Initializes the base address
    uint16_t base_address = USER_TABLE_EEPROM_ENTRIES_ADDRESS;

    // Reads the entries
    forn(i, length) {
        // Reads the username
        eeprom_read_block(entries[i].username, (void *) base_address, sizeof(entries[i].username));

        // Shifts the base address
        base_address += sizeof(entries[i].username);

        // Reads the password
        eeprom_read_block(entries[i].password, (void *) base_address, sizeof(entries[i].password));

        // Shifts the base address
        base_address += sizeof(entries[i].password);

        // Reads the role
        entries[i].role = eeprom_read_byte((uint8_t *) base_address);

        // Shifts the base address
        base_address += sizeof(entries[i].role);
    }

    // Returns the table length
    return length;
}

void UserTableEeprom::writeEntry(int index, UserTableEntry *entry) {
    // Calculates the base address
    uint16_t base_address = USER_TABLE_EEPROM_ENTRIES_ADDRESS + index * USER_TABLE_EEPROM_ENTRY_SIZE;

    // Writes the username
    eeprom_write_block(entry->username, (void *) base_address, sizeof(entry->username));

    // Shifts the base address
    base_address += sizeof(entry->username);

    // Writes the password
    eeprom_write_block(entry->password, (void *) base_address, sizeof(entry->password));

    // Shifts the base address
    base_address += sizeof(entry->password);

    // Writes the role
    eeprom_write_byte((uint8_t *) base_address, entry->role);
}

void UserTableEeprom::writeLength(uint8_t length) {
    eeprom_write_byte((uint8_t *) USER_TABLE_EEPROM_LENGTH_ADDRESS, length);
}
