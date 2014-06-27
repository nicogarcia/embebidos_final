#ifndef COMMUNICATION_MODULE
#define COMMUNICATION_MODULE

#include "Definitions.h"

class CommunicationModule {
public:
    static void initialize();
    static void readRequest();
    static void sendErrorResponse(OutputParameter error_parameter);
    static void sendLoginResponse(OutputParameter logged_in_parameter);
    static void sendRequestStateResponse(OutputParameter lock_closed_parameter, OutputParameter light_off_parameter, OutputParameter light_disabled_parameter, Temperature temperature, Humidity humidity);
    static void sendRequestUsersResponse(int user_count, Username usernames[CAPACITY_USER_TABLE]);
    static void sendSuccessResponse();
private:
    static SoftwareSerial bluetoothInterface;
    static bool ignore_message;
    static char message_buffer[INPUT_MESSAGE_MAX_LENGTH];
    static int message_buffer_index;
    static void processCharacter(char character);
    static void processMessage();
    static void sendMessage(String message);
};

#endif // COMMUNICATION_MODULE
