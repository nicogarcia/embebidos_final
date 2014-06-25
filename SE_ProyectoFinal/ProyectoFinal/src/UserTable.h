#ifndef USER_TABLE
#define USER_TABLE

#include "Definitions.h"

class UserTable {
public:
    static void addEntry(Username username, Password password, Role role);
    static UserTableEntry *getEntries();
    static UserTableEntry *getEntry(Username username);
    static int getEntryIndex(Username username);
    static int getLength();
    static void initialize();
    static bool isEmpty();
    static bool isFull();
    static void removeEntry(int index);
    static void removeEntry(Username username);
    static void readEEPROM();
private:
    static UserTableEntry entries[CAPACITY_USER_TABLE];
    static void updateEEPROM(Username username,Password password, Role role, int index);
    static int length;
};

#endif /* USER_TABLE */
