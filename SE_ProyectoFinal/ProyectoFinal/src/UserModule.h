#ifndef USER_MODULE
#define USER_MODULE

#include "Definitions.h"

class UserModule {
public:
    static void addUser(Username username, Password password, Role role);
    static bool authenticateUser(Username username, Password password);
    static void autoLogoutUsers();
    static void changeUserPassword(Username username, Password password);
    static void decrementUserTtls();
    static Role getUserRole(Username username);
    static uint8_t getUserUsernames(Username usernames[CAPACITY_USER_TABLE]);
    static void initialize();
    static bool isLoginTableFull();
    static bool isUserLoggedIn(Username username);
    static bool isUserTableFull();
    static void loginUser(Username username);
    static void logoutUser(Username username);
    static void refreshUserTtl(Username username);
    static void removeUser(Username username);
    static bool userExists(Username username);
};

#endif // USER_MODULE
