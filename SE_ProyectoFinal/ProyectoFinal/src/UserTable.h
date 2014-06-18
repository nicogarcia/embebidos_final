#ifndef USER_TABLE
#define USER_TABLE

#include "Definitions.h"

class UserTable {
public:
	static void addEntry(Username username, Password password, Role role);
	static UserTableEntry *getEntry(Username username);
	static bool isFull();
	static void removeEntry(Username username);
private:
	static UserTableEntry entries[USER_TABLE_CAPACITY];
	static int length;
	static int getEntryIndex(Username username);
	static void removeEntry(int index);
};

#endif /* USER_TABLE */
