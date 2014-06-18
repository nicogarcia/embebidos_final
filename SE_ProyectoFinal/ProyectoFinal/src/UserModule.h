#ifndef USER_MODULE
#define USER_MODULE

#include "Definitions.h"

class UserModule {
public:
	static void addUser(Username username, Password password, Role role);
	static bool authenticateUser(Username username, Password password);
	static void autoLogout();
	static void changeUserPassword(Username username, Password password);
	static void decrementTtls();
	static Role getUserRole(Username username);
	static bool isLoginTableFull();
	static bool isUserLoggedIn(Username username);
	static bool isUserTableFull();
	static void loginUser(Username username);
	static void refreshUserTtl(Username username);
	static void removeUser(Username username);
	static bool userExists(Username username);
};

#endif /* USER_MODULE */
