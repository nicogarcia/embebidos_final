#include "SecurityModule.h"

bool SecurityModule::authorizeRequest(Request request, Input input_parameters[INPUT_PARAMETER_MAX_COUNT]) {
    // Finds out if the user is logged in
    bool is_user_logged_in = UserModule::isUserLoggedIn(input_parameters[0]);

    if(request == LOGIN)
        // It is a login request
        // The request is authorized only if the user is not already logged in
        return ! is_user_logged_in;

    if(! is_user_logged_in)
        // The user is not logged in
        return false;

    switch(request) {
    case CHANGE_PASSWORD :
    case LOGOUT :
    case REFRESH_TTL :
    case REQUEST_STATE :
    case TOGGLE_LIGHT :
    case TOGGLE_LOCK :
        return true; // It is a non-administrator request
    }

    if(UserModule::getUserRole(input_parameters[0]) != ADMIN)
        // The user is not an administrator
        return false;

    if(request == REMOVE_USER)
        // It is a remove user request
        // The request is authorized only if the user to be removed is not an administrator
        return UserModule::getUserRole(input_parameters[1]) != ADMIN;

    switch(request) {
    case ADD_USER :
    case REQUEST_USERS :
        return true; // It is an administrator request
    default :
        return false; // Invalid request
    }
}

bool SecurityModule::isValidPassword(Input password) {
    return isValidInputParameter(password);
}

bool SecurityModule::isValidRequest(Input request) {
    // Gets the request length
    int length = strlen(request);

    if(length < REQUEST_MIN_LENGTH)
        // Request too short
        return false;

    if(length > REQUEST_MAX_LENGTH)
        // Request too long
        return false;

    forn(i, length) {
        char character = request[i];

        if(character < '0' || character > '9')
            // The character is not a decimal digit
            return false;
    }

    // Valid request
    return true;
}

bool SecurityModule::isValidUsername(Input username) {
    return isValidInputParameter(username);
}

bool SecurityModule::isValidInputParameter(Input input_parameter) {
    // Gets the input parameter length
    int length = strlen(input_parameter);

    if(length < INPUT_PARAMETER_MIN_LENGTH)
        // Input parameter too short
        return false;

    if(length > INPUT_PARAMETER_MAX_LENGTH)
        // Input parameter too long
        return false;

    forn(i, length) {
        if(! isValidInputParameterCharacter(input_parameter[i]))
            // The input parameter has at least one invalid character
            return false;
    }

    // Valid input parameter
    return true;
}

bool SecurityModule::isValidInputParameterCharacter(char character) {
    if(character >= 'a' && character <= 'z')
        // a-z
        return true;

    if(character >= 'A' && character <= 'Z')
        // A-Z
        return true;

    if(character >= '0' && character <= '9')
        // 0-9
        return true;

    if(character == '_')
        // _ (underscore)
        return true;

    // Invalid character
    return false;
}
