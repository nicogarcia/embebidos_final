#include "CommunicationModule.h"

SoftwareSerial CommunicationModule::bluetoothInterface(DIGITAL_PIN_SOFTWARE_SERIAL_RECEPTION, DIGITAL_PIN_SOFTWARE_SERIAL_TRANSMISSION);
bool CommunicationModule::ignore_message;
char CommunicationModule::message_buffer[INPUT_MESSAGE_MAX_LENGTH];
int CommunicationModule::message_buffer_index;

#ifdef DEBUG_MODE
void CommunicationModule::debug() {
    // Fills the message buffer one character at a time
    // This is the closest way to the reality that the system can be tested
    // Remember to define EEPROM_INITIALIZATION_MODE to avoid strange behaviours

    // Example 1
    //
    // $LOGIN#admin#12345*
    // $CHANGE_PASSWORD#admin#admin*
    // $LOGOUT#admin*
    // $LOGIN#admin#admin*
    //
    // Expected responses:
    // $1#7*
    // $1*
    // $1*
    // $1#7*
    char message[] = "$2#admin#12345*$1#admin#admin*$3#admin*$2#admin#admin*";

    // Example 2
    //
    // $LOGIN#admin#12345*
    // $ADD_USER#admin#user#us*
    // $ADD_USER#admin#user#user*
    // $ADD_USER#admin#user#user2*
    // $LOGOUT#admin*
    // $LOGIN#user#user*
    // $REQUEST_USERS#user*
    // $REQUEST_USERS#admin*
    // $TOGGLE_LOCK#user*
    //
    // Expected responses:
    // $1#7*
    // $0#0*
    // $1*
    // $0#11*
    // $1*
    // $1#7*
    // $0#10*
    // $0#10*
    // $1*
    //char message[] = "$2#admin#12345*$0#admin#user#us*$0#admin#user#user*$0#admin#user#user2*$3#admin*$2#user#user*$7#user*$7#admin*$9#user*";

    // Example 3
    //
    // $LOGIN#admin#12345*
    // $REFRESH_TTL#user*
    // $REFRESH_TTL#admin*
    // $TOGGLE_LIGHT#admin*
    // $TOGGLE_LOCK#admin*
    // $REQUEST_STATE#admin*
    //
    // Expected responses:
    // $1#7*
    // $0#10*
    // $1*
    // $1*
    // $1*
    // $1#6#3#2#<temperature>#<humidity>*
    //char message[] = "$2#admin#12345*$4#user*$4#admin*$8#admin*$9#admin*$6#admin*";

    // REQUEST_USERS not working properly
    // Example 4
    //
    // $LOGIN#admin#12345*
    // $ADD_USER#admin#user0#pwd*
    // $ADD_USER#admin#user1#pwd*
    // $ADD_USER#admin#user2#pwd*
    // $REMOVE_USER#admin#user1*
    // $REMOVE_USER#admin#user1*
    // $ADD_USER#admin#user2#pwd*
    // $ADD_USER#admin#user1#pwd*
    // $REQUEST_USERS#admin*
    //
    // Expected responses:
    // $1#7*
    // $1*
    // $1*
    // $1*
    // $1*
    // $0#12*
    // $0#11*
    // $1*
    // $1#3#user0#user2#user1*
    //char message[] = "$2#admin#12345*$0#admin#user0#pwd*$0#admin#user1#pwd*$0#admin#user2#pwd*$5#admin#user1*$5#admin#user1*$0#admin#user2#pwd*$0#admin#user1#pwd*$7#admin*";


    int length = strlen(message);
    forn (i, length) {
        processCharacter(message[i]);
    }

}
#endif // DEBUG_MODE

void CommunicationModule::initialize() {
    ignore_message = true;
    message_buffer_index = 0;

    // Initializes the bluetooth interface
    bluetoothInterface.begin(BAUD_RATE_BLUETOOTH_INTERFACE);

#ifdef DEBUG_MODE
    // Initializes the monitor interface
    Serial.begin(BAUD_RATE_MONITOR_INTERFACE);

    // Clears the input serial buffer
    while (Serial.available() > 0)
        Serial.read();

    Serial.println("Hello from SISAD");
    Serial.flush();
#endif // DEBUG_MODE
}

void CommunicationModule::readRequest() {
#ifdef DEBUG_MODE
    while (Serial.available() > 0)
        // There are characters unread
        processCharacter(Serial.read());
#endif // DEBUG_MODE

    while (bluetoothInterface.available() > 0)
        // There are characters unread
        processCharacter(bluetoothInterface.read());
}

void CommunicationModule::sendErrorResponse(OutputParameter error_parameter) {
    // Response
    Response response = ERROR;

    // Sends the message
    bluetoothInterface.print(MESSAGE_BEGIN);
    bluetoothInterface.print(response);
    bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
    bluetoothInterface.print(error_parameter);
    bluetoothInterface.print(MESSAGE_END);

#ifdef DEBUG_MODE
    Serial.print("T: ");
    Serial.print(MESSAGE_BEGIN);
    Serial.print(response);
    Serial.print(MESSAGE_INPUTS_SEPARATOR);
    Serial.print(error_parameter);
    Serial.println(MESSAGE_END);
    Serial.flush();
#endif // DEBUG_MODE
}

void CommunicationModule::sendLoginResponse(OutputParameter logged_in_parameter) {
    // Response
    Response response = SUCCESS;

    // Sends the message
    bluetoothInterface.print(MESSAGE_BEGIN);
    bluetoothInterface.print(response);
    bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
    bluetoothInterface.print(logged_in_parameter);
    bluetoothInterface.print(MESSAGE_END);

#ifdef DEBUG_MODE
    Serial.print("T: ");
    Serial.print(MESSAGE_BEGIN);
    Serial.print(response);
    Serial.print(MESSAGE_INPUTS_SEPARATOR);
    Serial.print(logged_in_parameter);
    Serial.println(MESSAGE_END);
    Serial.flush();
#endif // DEBUG_MODE
}

void CommunicationModule::sendRequestStateResponse(OutputParameter lock_closed_parameter, OutputParameter light_off_parameter, OutputParameter light_disabled_parameter, Temperature temperature, Humidity humidity) {
    // Response
    Response response = SUCCESS;

    // Sends the message
    bluetoothInterface.print(MESSAGE_BEGIN);
    bluetoothInterface.print(response);
    bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
    bluetoothInterface.print(lock_closed_parameter);
    bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
    bluetoothInterface.print(light_off_parameter);
    bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
    bluetoothInterface.print(light_disabled_parameter);
    bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
    bluetoothInterface.print(temperature);
    bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
    bluetoothInterface.print(humidity);
    bluetoothInterface.print(MESSAGE_END);

#ifdef DEBUG_MODE
    Serial.print("T: ");
    Serial.print(MESSAGE_BEGIN);
    Serial.print(response);
    Serial.print(MESSAGE_INPUTS_SEPARATOR);
    Serial.print(lock_closed_parameter);
    Serial.print(MESSAGE_INPUTS_SEPARATOR);
    Serial.print(light_off_parameter);
    Serial.print(MESSAGE_INPUTS_SEPARATOR);
    Serial.print(light_disabled_parameter);
    Serial.print(MESSAGE_INPUTS_SEPARATOR);
    Serial.print(temperature);
    Serial.print(MESSAGE_INPUTS_SEPARATOR);
    Serial.print(humidity);
    Serial.println(MESSAGE_END);
    Serial.flush();
#endif // DEBUG_MODE
}

void CommunicationModule::sendRequestUsersResponse(int user_count, Username usernames[CAPACITY_USER_TABLE]) {
    // Response
    Response response = SUCCESS;

    // Sends the message
    bluetoothInterface.print(MESSAGE_BEGIN);
    bluetoothInterface.print(response);
    bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
    bluetoothInterface.print(user_count);
    forn (i, user_count) {
        bluetoothInterface.print(MESSAGE_INPUTS_SEPARATOR);
        bluetoothInterface.print(usernames[i]);
    }
    bluetoothInterface.print(MESSAGE_END);

#ifdef DEBUG_MODE
    Serial.print("T: ");
    Serial.print(MESSAGE_BEGIN);
    Serial.print(response);
    Serial.print(MESSAGE_INPUTS_SEPARATOR);
    Serial.print(user_count);
    forn (i, user_count) {
        Serial.print(MESSAGE_INPUTS_SEPARATOR);
        Serial.print(usernames[i]);
    }
    Serial.println(MESSAGE_END);
    Serial.flush();
#endif // DEBUG_MODE
}

void CommunicationModule::sendSuccessResponse() {
    // Response
    Response response = SUCCESS;

    // Sends the message
    bluetoothInterface.print(MESSAGE_BEGIN);
    bluetoothInterface.print(response);
    bluetoothInterface.print(MESSAGE_END);

#ifdef DEBUG_MODE
    Serial.print("T: ");
    Serial.print(MESSAGE_BEGIN);
    Serial.print(response);
    Serial.println(MESSAGE_END);
    Serial.flush();
#endif // DEBUG_MODE
}

void CommunicationModule::processCharacter(char character) {
    switch(character) {
    case MESSAGE_BEGIN : {
#ifdef DEBUG_MODE
        Serial.print("R: ");
        Serial.print(character);
#endif // DEBUG_MODE

        ignore_message = false;
        message_buffer_index = 0; // Clears the buffer
        break;
    }

    case MESSAGE_END : {
#ifdef DEBUG_MODE
        Serial.println(character);
        Serial.flush();
#endif // DEBUG_MODE

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
#endif // DEBUG_MODE

        if (! ignore_message) {
            if (message_buffer_index == INPUT_MESSAGE_MAX_LENGTH)
                // The buffer is full
                ignore_message = true;
            else
                // Buffers the character
                message_buffer[message_buffer_index++] = character;
        }
    }
    }
}

void CommunicationModule::processMessage() {
    Input inputs[INPUT_MAX_COUNT];
    int input_lengths[INPUT_MAX_COUNT];

    // Initializes the input lengths
    forn (i, INPUT_MAX_COUNT) {
        input_lengths[i] = 0;
    }

    int input_length = 0;
    int inputs_index = 0;
    forn (i, message_buffer_index) {
        // Reads a character from the message buffer
        char character = message_buffer[i];

        if (character == MESSAGE_INPUTS_SEPARATOR) {
            // The character is a separator

            // Adds the input length
            input_lengths[inputs_index] = input_length;

            inputs_index++;
            input_length = 0;

            if (inputs_index == INPUT_MAX_COUNT) {
                // There are too many inputs
                sendErrorResponse(INVALID_INPUT);
                return;
            }
        } else {
            if (input_length == INPUT_MAX_LENGTH) {
                // The input is too long
                sendErrorResponse(INVALID_INPUT);
                return;
            }

            // Appends the character
            inputs[inputs_index][input_length++] = character;
        }
    }

    // Adds the last input length
    input_lengths[inputs_index] = input_length;

    // Appends a null character to the inputs
    forn (i, INPUT_MAX_COUNT) {
        inputs[i][input_lengths[i]] = '\0';
    }

    // Serves the request
    RequestModule::serveRequest(inputs);
}
