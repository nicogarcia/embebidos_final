/*
* UserTableEeprom.h
*
* Created: 27/06/2014 13:16:05
* Author: Fede
*/
#ifndef USER_TABLE_EEPROM
#define USER_TABLE_EEPROM

#include "Definitions.h"

class UserTableEeprom {
public:
    static uint8_t readEntries(UserTableEntry entries[CAPACITY_USER_TABLE]);
    static void writeEntry(int index, UserTableEntry *entry);
    static void writeLength(uint8_t length);
private:
    static void waitUntilIsReady();
};

#endif // USER_TABLE_EEPROM
