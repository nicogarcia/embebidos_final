#ifndef REQUEST_MODULE
#define REQUEST_MODULE

#include "Definitions.h"

class RequestModule {
public:
    static void serveRequest(Request request, Input inputs[INPUT_MAX_COUNT]);
private:
    static void addUser(Username username, Password password);
    static void changePassword(Username username, Password password);
    static void login(Username username, Password password);
    static void logout(Username username);
    static void refreshTtl(Username username);
    static void removeUser(Username username);
    static void requestState();
    static void requestUsers();
    static void toggleLight();
    static void toggleLock();
    static bool validateInputs(Request request, Input inputs[INPUT_MAX_COUNT]);
};

#endif /* REQUEST_MODULE */
