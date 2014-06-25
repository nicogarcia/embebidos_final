#include "AuxiliarModule.h"

bool AuxiliarModule::isValidPassword(String password) {
    return isValidInputParameter(password);
}

bool AuxiliarModule::isValidRequest(String request) {
    // Gets the request length
    int length = request.length();

    if (length < REQUEST_MIN_LENGTH)
        // Request too short
        return false;

    if (length > REQUEST_MAX_LENGTH)
        // Request too long
        return false;

    forn (i, length) {
        char character = request.charAt(i);

        if (character < '0' || character > '9')
            // The character is not a decimal digit
            return false;
    }

    // Valid request
    return true;
}

bool AuxiliarModule::isValidUsername(String username) {
    return isValidInputParameter(username);
}

bool AuxiliarModule::isValidInputParameter(String input_parameter) {
    // Gets the input parameter length
    int length = input_parameter.length();

    if (length < INPUT_PARAMETER_MIN_LENGTH)
        // Input parameter too short
        return false;

    if (length > INPUT_PARAMETER_MAX_LENGTH)
        // Input parameter too long
        return false;

    forn (i, length)
    if (! isValidInputParameterCharacter(input_parameter.charAt(i)))
        // The input parameter has at least one invalid character
        return false;

    // Valid input parameter
    return true;
}

bool AuxiliarModule::isValidInputParameterCharacter(char character) {
    if (character >= 'a' && character <= 'z')
        // a-z
        return true;

    if (character >= 'A' && character <= 'Z')
        // A-Z
        return true;

    if (character >= '0' && character <= '9')
        // 0-9
        return true;

    if (character == '_')
        // _ (underscore)
        return true;

    // Invalid character
    return false;
}

void AuxiliarModule::stringToCharArray( String string, char *array ) {
    forn (i, string.length())
    array[i] = string.charAt(i);

    array[string.length()+1] = '\0';
}
