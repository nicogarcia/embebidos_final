#ifndef LOGIN_TABLE
#define LOGIN_TABLE

#include "Definitions.h"

class LoginTable {
public:
    static void addEntry(Username username, Ttl ttl);
    static LoginTableEntry *getEntries();
    static LoginTableEntry *getEntry(Username username);
    static int getEntryIndex(Username username);
    static int getLength();
    static void initialize();
    static bool isEmpty();
    static bool isFull();
    static void removeEntry(int index);
    static void removeEntry(Username username);
private:
    static LoginTableEntry entries[CAPACITY_LOGIN_TABLE];
    static uint8_t length;
};

#endif /* LOGIN_TABLE */
