#include "AuxiliarModule.h"

bool AuxiliarModule::isValidPassword(Input password) {
    return isValidInputParameter(password);
}

bool AuxiliarModule::isValidRequest(Input request) {
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

bool AuxiliarModule::isValidUsername(Input username) {
    return isValidInputParameter(username);
}

bool AuxiliarModule::isValidInputParameter(Input input_parameter) {
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

bool AuxiliarModule::isValidInputParameterCharacter(char character) {
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
