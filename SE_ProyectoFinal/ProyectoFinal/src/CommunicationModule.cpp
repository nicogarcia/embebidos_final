#include "CommunicationModule.h"

void serialEvent() {
#ifndef DEBUG_MODE
    CommunicationModule::serialEvent();
#endif /* DEBUG_MODE */
}

#ifdef DEBUG_MODE
SoftwareSerial CommunicationModule::bluetoothInterface = SoftwareSerial(PIN_SOFTWARE_SERIAL_RECEPTION, PIN_SOFTWARE_SERIAL_TRANSMISSION);
#else /* DEBUG_MODE */
HardwareSerial CommunicationModule::bluetoothInterface = Serial;
#endif /* DEBUG_MODE */

bool CommunicationModule::ignore_message;
char CommunicationModule::message_buffer[MESSAGE_MAX_LENGTH];
int CommunicationModule::message_index;
int CommunicationModule::message_inputs;

void CommunicationModule::initialize() {
    ignore_message = true;
    message_index = 0;
    message_inputs = 0;

    // Initializes the bluetooth interface
    bluetoothInterface.begin(BAUD_RATE_BLUETOOTH);

#ifdef DEBUG_MODE
    // Initializes the terminal interface
    Serial.begin(BAUD_RATE_TERMINAL);
    Serial.println("Hello from SISAD");
#endif /* DEBUG_MODE */
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

void CommunicationModule::sendRequestUsersResponse(int user_count, Username usernames[CAPACITY_USER_TABLE]) {
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

void CommunicationModule::serialEvent() {
    while (bluetoothInterface.available() > 0)
        // There are characters unread
        readCharacter();
}

void CommunicationModule::processMessage() {
    // TODO: procesa el mensaje del buffer. El mensaje est� entre [0, message_length)
    // Tener en cuenta que en el buffer no est�n ni MESSAGE_BEGIN ni MESSAGE_END, s�lo los
    // datos y los separadores
    /*
    String format = "%i";
    int i = 0;
    while(message_inputs < i) {
        format = format + "#%s";
        i++;
    }
    */

    //TODO: do it generic?

    Request request = 0;
    Input inputs[INPUT_MAX_COUNT];
    forn (i, INPUT_MAX_COUNT)
    inputs[i] = "";

    message_buffer[message_index] = '\0';
    switch(message_inputs) {
    case 1: {
        sscanf(message_buffer, "%i#%s", request, &inputs[0]);
        break;
    }
    case 2: {
        sscanf(message_buffer, "%i#%s#%s", request, &inputs[0], &inputs[1]);
        break;
    }
    case 3: {
        sscanf(message_buffer, "%i#%s#%s#%s", request, &inputs[0], &inputs[1], &inputs[2]);
    }
    }

    RequestModule::serveRequest(request, inputs);
}

void CommunicationModule::readCharacter() {
    char character = bluetoothInterface.read();

    switch (character) {
    case MESSAGE_BEGIN : {
        ignore_message = false;
        message_index = 0; // Clears the buffer
        message_inputs = 0; // Resets the number of inputs
        break;
    }

    case MESSAGE_END : {
        if (! ignore_message) {
            // Processes the message
            processMessage();

            // Ignores characters until a MESSAGE_BEGIN is received
            ignore_message = true;
        }

        break;
    }

    default : {
        if (! ignore_message) {
            if (message_index == MESSAGE_MAX_LENGTH)
                // The buffer is full
                ignore_message = true;
            else {
                // Buffers the character
                message_buffer[message_index++] = character;

                if (character == MESSAGE_PARAMETERS_SEPARATOR)
                    // The character is a message parameters separator
                    message_inputs++;
            }
        }
    }
    }
}

void CommunicationModule::sendMessage(String message) {
    // TODO: actually send the message (Serial)
    Serial.println(message); // TODO: to debug, remove this and use bluetoothInterface
}
