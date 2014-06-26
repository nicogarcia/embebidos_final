#include "AuxiliarModule.h"

bool AuxiliarModule::isValidPassword(char* password) {
    return isValidInputParameter(password);
}

bool AuxiliarModule::isValidRequest(char* request) {
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

bool AuxiliarModule::isValidUsername(char* username) {
    return isValidInputParameter(username);
}

bool AuxiliarModule::isValidInputParameter(char* input_parameter) {
    // Gets the input parameter length
    int length = strlen(input_parameter);

    if(length < INPUT_PARAMETER_MIN_LENGTH)
        // Input parameter too short
        return false;

    if(length > INPUT_PARAMETER_MAX_LENGTH)
        // Input parameter too long
        return false;

    forn(i, length)
    if(! isValidInputParameterCharacter(input_parameter[i]))
        // The input parameter has at least one invalid character
        return false;

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

void AuxiliarModule::stringToCharArray(String string, char *array) {
    forn(i, string.length())
    array[i] = string.charAt(i);

    array[string.length() + 1] = '\0';
}
