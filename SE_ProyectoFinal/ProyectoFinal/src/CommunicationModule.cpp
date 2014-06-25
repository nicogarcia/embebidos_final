#include "CommunicationModule.h"

SoftwareSerial CommunicationModule::bluetoothInterface(PIN_SOFTWARE_SERIAL_RECEPTION, PIN_SOFTWARE_SERIAL_TRANSMISSION);
bool CommunicationModule::ignore_message;
char CommunicationModule::message_buffer[INPUT_MESSAGE_MAX_LENGTH];
int CommunicationModule::message_index;

void CommunicationModule::initialize() {
    ignore_message = true;
    message_index = 0;

    // Initializes the bluetooth interface
    bluetoothInterface.begin(BAUD_RATE_BLUETOOTH);

#ifdef DEBUG_MODE
    // Initializes the terminal interface
    Serial.begin(BAUD_RATE_TERMINAL);
    Serial.println("Hello from SISAD");
#endif /* DEBUG_MODE */
}

void CommunicationModule::readRequest() {
    while (bluetoothInterface.available() > 0)
        // There are characters unread
        readCharacter();
}

void CommunicationModule::sendErrorResponse(OutputParameter error_parameter) {
    // Response
    Response response = ERROR;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_INPUTS_SEPARATOR;
    message += error_parameter;
    message += MESSAGE_END;

    // Sends the message
    sendMessage(message);
}

void CommunicationModule::sendLoginResponse(OutputParameter logged_in_parameter) {
    // Response
    Response response = SUCCESS;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_INPUTS_SEPARATOR;
    message += logged_in_parameter;
    message += MESSAGE_END;

    // Sends the message
    sendMessage(message);
}

void CommunicationModule::sendRequestStateResponse(OutputParameter lock_closed_parameter, OutputParameter light_off_parameter, OutputParameter light_disabled_parameter, Temperature temperature, Humidity humidity) {
    // Response
    Response response = SUCCESS;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_INPUTS_SEPARATOR;
    message += lock_closed_parameter;
    message += MESSAGE_INPUTS_SEPARATOR;
    message += light_off_parameter;
    message += MESSAGE_INPUTS_SEPARATOR;
    message += light_disabled_parameter;
    message += MESSAGE_INPUTS_SEPARATOR;
    message += temperature;
    message += MESSAGE_INPUTS_SEPARATOR;
    message += humidity;
    message += MESSAGE_END;

    // Sends the message
    sendMessage(message);
}

void CommunicationModule::sendRequestUsersResponse(int user_count, Username usernames[CAPACITY_USER_TABLE]) {
    // Response
    Response response = SUCCESS;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_INPUTS_SEPARATOR;
    message += user_count;
    forn (i, user_count) {
        message += MESSAGE_INPUTS_SEPARATOR;
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

void CommunicationModule::processMessage() {
    Input inputs[INPUT_MAX_COUNT];

    // Initializes the inputs as empty strings
    forn (i, INPUT_MAX_COUNT)
    inputs[i] = "";

    int inputs_index = 0;
    forn (i, message_index)
    if (message_buffer[i] == MESSAGE_INPUTS_SEPARATOR) {
        inputs_index++;

        if (inputs_index == INPUT_MAX_COUNT)
            // There are too many inputs: ignores the message
            return;
    } else
        inputs[inputs_index] += message_buffer[i];

    // Serves the request
    RequestModule::serveRequest(inputs);
}

void CommunicationModule::readCharacter() {
    char character = bluetoothInterface.read();

    switch (character) {
    case MESSAGE_BEGIN : {
#ifdef DEBUG_MODE
        Serial.print("R: ");
        Serial.print(character);
#endif /* DEBUG_MODE */

        ignore_message = false;
        message_index = 0; // Clears the buffer
        break;
    }

    case MESSAGE_END : {
#ifdef DEBUG_MODE
        Serial.println(character);
#endif /* DEBUG_MODE */

        if (! ignore_message) {
            // Ignores characters until a MESSAGE_BEGIN is received
            ignore_message = true;

            // Processes the message
            processMessage();
        }

        break;
    }

    default : {
#ifdef DEBUG_MODE
        Serial.print(character);
#endif /* DEBUG_MODE */

        if (! ignore_message) {
            if (message_index == INPUT_MESSAGE_MAX_LENGTH)
                // The buffer is full
                ignore_message = true;
            else
                // Buffers the character
                message_buffer[message_index++] = character;
        }
    }
    }
}

void CommunicationModule::sendMessage(String message) {
#ifdef DEBUG_MODE
    Serial.print("T: ");
    Serial.println(message);
#endif /* DEBUG_MODE */

    // Parses from string to char array
    int length = message.length();
    char message_array[length + 1];

    forn (i, length)
    message_array[i] = message.charAt(i);

    message_array[length] = '\0';

    // Sends the message bytes
    bluetoothInterface.print(message_array);
}