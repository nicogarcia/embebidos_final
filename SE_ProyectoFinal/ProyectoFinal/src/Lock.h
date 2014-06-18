#ifndef LOCK
#define LOCK

#include "Definitions.h"

class Lock {
public:
	static void close();
	static bool isClosed();
	static void open();
private:
	static bool is_closed;
};

#endif /* LOCK */
