#include "CommunicationModule.h"

void serialEvent() {
    // TODO: serialEvent()
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

void CommunicationModule::sendRequestStateResponse(Parameter lock_parameter, Parameter light_parameter, Temperature temperature, Humidity humidity) {
    // Response
    Response response = SUCCESS;

    // Builds the message
    String message = "";
    message += MESSAGE_BEGIN;
    message += response;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += lock_parameter;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += light_parameter;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += temperature;
    message += MESSAGE_PARAMETERS_SEPARATOR;
    message += humidity;
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
    Serial.println("sendMessage");
}
