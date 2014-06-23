#ifndef COMMUNICATION_MODULE
#define COMMUNICATION_MODULE

#include "Definitions.h"

void serialEvent();

class CommunicationModule {
public:
    static void initialize();
    static void sendErrorResponse(Parameter error_parameter);
    static void sendLoginResponse(Parameter logged_in_parameter);
    static void sendRequestStateResponse(Parameter lock_closed_parameter, Parameter light_off_parameter, Parameter light_disabled_parameter, Temperature temperature, Humidity humidity);
    static void sendRequestUsersResponse(int user_count, Username usernames[CAPACITY_USER_TABLE]);
    static void sendSuccessResponse();
    static void serialEvent();
private:
#ifdef DEBUG_MODE
    static SoftwareSerial bluetoothInterface;
#else /* DEBUG_MODE */
    static HardwareSerial bluetoothInterface;
#endif /* DEBUG_MODE */
    static bool ignore_message;
    static char message[MESSAGE_MAX_LENGTH];
    static int message_index;
    static void processMessage();
    static void readCharacter();
    static void sendMessage(String message);
};

#endif /* COMMUNICATION_MODULE */
