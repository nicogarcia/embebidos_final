#include "AuxiliarModule.h"

String AuxiliarModule::charArrayToString(char char_array[INPUT_MAX_LENGTH + 1]) {
    String string = "";

    int index = 0;
    char character = char_array[index];
    while (character != '\0' && index < INPUT_MAX_LENGTH) {
        // Appends the character to the string
        string += character;

        // Gets the next character
        character = char_array[++index];
    }

    return string;
}

bool AuxiliarModule::isValidPassword(Password password) {
    return isValidInput(password);
}

bool AuxiliarModule::isValidUsername(Username username) {
    return isValidInput(username);
}

bool AuxiliarModule::isValidInput(Input input) {
    // Gets the input length
    int length = input.length();

    if (length < INPUT_MIN_LENGTH)
        // Input too short
        return false;

    if (length > INPUT_MAX_LENGTH)
        // Input too long
        return false;

    forn (i, length)
    if (! isValidInputCharacter(input.charAt(i)))
        // The input has at least one invalid character
        return false;

    // Valid input
    return true;
}

bool AuxiliarModule::isValidInputCharacter(char character) {
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
