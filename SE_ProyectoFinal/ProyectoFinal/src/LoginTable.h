#ifndef LOGIN_TABLE
#define LOGIN_TABLE

#include "Definitions.h"

class LoginTable {
public:
	static void addEntry(Username username, Ttl ttl);
	static void decrementTtls();
	static LoginTableEntry *getEntry(Username username);
	static bool isFull();
	static void removeEntry(Username username);
	static void removeExpiredEntries();
private:
	static LoginTableEntry entries[LOGIN_TABLE_CAPACITY];
	static int length;
	static int getEntryIndex(Username username);
	static void removeEntry(int index);
};

#endif /* LOGIN_TABLE */
