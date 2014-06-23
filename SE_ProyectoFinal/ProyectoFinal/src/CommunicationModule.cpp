#include "CommunicationModule.h"

SoftwareSerial CommunicationModule::BTSerial = SoftwareSerial(7, 6);

void serialEvent() {
#ifdef DEBUG
    if (Serial.available()) {
        char send_it = (char) Serial.read();
        CommunicationModule::BTSerial.write(send_it);
    }
#else /* DEBUG */
    if (Serial.available()) {
        if (((char) Serial.read()) == MESSAGE_BEGIN)
            CommunicationModule::readMessage();
    }
#endif /* DEBUG */
}

void CommunicationModule::readMessage() {
    int char_index = 0, string_index = 0;
    char read_char;
    Input input[INPUT_MAX_COUNT];
    char string[INPUT_MAX_LENGTH];
    uint8_t code = BTSerial.read() - 49;
    read_char = BTSerial.read(); //consume message separator
    read_char = BTSerial.read();


    while(BTSerial.available() && read_char != MESSAGE_END ) {
        if (read_char != MESSAGE_PARAMETERS_SEPARATOR)
            string[char_index++] = read_char;
        else {
            string[char_index] = '\0';
            char_index = 0;
            my_strcpy(string, (char*)&input[string_index++]);
        }

        read_char = BTSerial.read();
    }

    RequestModule::serveRequest(code, input);
}

void CommunicationModule::sendErrorResponse(Parameter error_parameter) {
    // Response
    Response response = ERROR;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += error_parameter;
    message += MESSAGE_END;

    // Sends the message
    sendMessage(message);
}

void CommunicationModule::sendLoginResponse(Parameter logged_in_parameter) {
    // Response
    Response response = SUCCESS;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += logged_in_parameter;
    message += MESSAGE_END;

    // Sends the message
    sendMessage(message);
}

void CommunicationModule::sendRequestStateResponse(Parameter lock_closed_parameter, Parameter light_off_parameter, Parameter light_disabled_parameter, Temperature temperature, Humidity humidity) {
    // Response
    Response response = SUCCESS;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += lock_closed_parameter;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += light_off_parameter;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += light_disabled_parameter;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += temperature;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += humidity;
    message += MESSAGE_END;

    // Sends the message
    sendMessage(message);
}

void CommunicationModule::sendRequestUsersResponse(int user_count, Username usernames[USER_TABLE_CAPACITY]) {
    // Response
    Response response = SUCCESS;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += user_count;
    forn (i, user_count) {
        message += MESSAGE_PARAMETERS_SEPARATOR;
        message += usernames[i];
    }
    message += MESSAGE_END;

    // Sends the message
    sendMessage(message);
}

void CommunicationModule::sendSuccessResponse() {
    // Response
    Response response = SUCCESS;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_END;

    // Sends the message
    sendMessage(message);
}

void CommunicationModule::sendMessage(String message) {
    // TODO: actually send the message (Serial)
    Serial.println(message);
}


void CommunicationModule::my_strcpy(const char* source, char* destiny) {
    while((*destiny++ = *source++));
}

// TODO: debugging purposes
void CommunicationModule::bluetoothEvent() {
    while(BTSerial.available()) {
        char first = (char) BTSerial.read();
        Serial.write(first);
        if (first == MESSAGE_BEGIN)
            readMessage();
    }
}
