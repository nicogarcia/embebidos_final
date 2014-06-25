#include "SecurityModule.h"

bool SecurityModule::authorizeRequest(Request request, InputParameter input_parameters[INPUT_PARAMETER_MAX_COUNT]) {
    // Finds out if the user is logged in
    bool is_user_logged_in = UserModule::isUserLoggedIn(input_parameters[0]);

    if (request == LOGIN)
        // It is a login request
        // The request is authorized only if the user is not already logged in
        return ! is_user_logged_in;

    if (! is_user_logged_in)
        // The user is not logged in
        return false;

    switch (request) {
    case CHANGE_PASSWORD :
    case LOGOUT :
    case REFRESH_TTL :
    case REQUEST_STATE :
    case TOGGLE_LIGHT :
    case TOGGLE_LOCK :
        return true; // It is a non-administrator request
    }

    if (UserModule::getUserRole(input_parameters[0]) != ADMIN)
        // The user is not an administrator
        return false;

    if (request == REMOVE_USER)
        // It is a remove user request
        // The request is authorized only if the user to be removed is not an administrator
        return UserModule::getUserRole(input_parameters[1]) != ADMIN;

    switch (request) {
    case ADD_USER :
    case REQUEST_USERS :
        return true; // It is an administrator request
    default :
        return false; // Invalid request
    }
}
