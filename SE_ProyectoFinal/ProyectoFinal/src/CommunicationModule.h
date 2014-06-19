#ifndef COMMUNICATION_MODULE
#define COMMUNICATION_MODULE

#include "Definitions.h"

void serialEvent();

class CommunicationModule {
public:
    static void sendErrorResponse(Parameter error_parameter);
    static void sendLoginResponse(Parameter logged_in_parameter);
    static void sendRequestStateResponse(Parameter lock_parameter, Parameter light_parameter, Temperature temperature, Humidity humidity);
    static void sendRequestUsersResponse(int user_count, Username usernames[USER_TABLE_CAPACITY]);
    static void sendSuccessResponse();
private:
    static void sendMessage(String message);
};

#endif /* COMMUNICATION_MODULE */
