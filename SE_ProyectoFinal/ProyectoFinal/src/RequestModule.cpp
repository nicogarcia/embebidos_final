#include "RequestModule.h"

void RequestModule::serveRequest(Request request, Input inputs[INPUT_MAX_COUNT]) {
    // Validates the inputs
    if (! validateInputs(request, inputs)) {
        // The input is invalid
        CommunicationModule::sendErrorResponse(INVALID_INPUT);
        return;
    }

    // Authorizes the request
    if (! SecurityModule::authorizeRequest(request, inputs)) {
        // The request has not been authorized
        CommunicationModule::sendErrorResponse(UNAUTHORIZED);
        return;
    }

    // Serves the request
    switch (request) {
    case ADD_USER : {
        addUser(inputs[1], inputs[2]);
        break;
    }

    case CHANGE_PASSWORD : {
        changePassword(inputs[0], inputs[1]);
        break;
    }

    case LOGIN : {
        login(inputs[0], inputs[1]);
        break;
    }

    case LOGOUT : {
        logout(inputs[0]);
        break;
    }

    case REFRESH_TTL : {
        refreshTtl(inputs[0]);
        break;
    }

    case REMOVE_USER : {
        removeUser(inputs[1]);
        break;
    }

    case REQUEST_STATE : {
        requestState();
        break;
    }

    case REQUEST_USERS : {
        requestUsers();
        break;
    }

    case TOGGLE_LIGHT : {
        toggleLight();
        break;
    }

    case TOGGLE_LOCK : {
        toggleLock();
        break;
    }
    }
}

void RequestModule::addUser(Username username, Password password) {
    if (UserModule::userExists(username)) {
        // The user already exists
        CommunicationModule::sendErrorResponse(USER_ALREADY_EXISTS);
        return;
    }

    if (UserModule::isUserTableFull()) {
        // The user table is full
        CommunicationModule::sendErrorResponse(USER_TABLE_FULL);
        return;
    }

    // Adds the user to the system
    UserModule::addUser(username, password, USER);

    // Sends a success response
    CommunicationModule::sendSuccessResponse();
}

void RequestModule::changePassword(Username username, Password password) {
    // Changes the user password
    UserModule::changeUserPassword(username, password);

    // Sends a success response
    CommunicationModule::sendSuccessResponse();
}

void RequestModule::login(Username username, Password password) {
    if (UserModule::isLoginTableFull()) {
        // The login table is full
        CommunicationModule::sendErrorResponse(LOGIN_TABLE_FULL);
        return;
    }

    // Authenticates the user
    bool user_authenticated = UserModule::authenticateUser(username, password);

    if (user_authenticated)
        // The user was authenticated
        UserModule::loginUser(username);

    Parameter logged_in_parameter = user_authenticated ? LOGGED_IN : NOT_LOGGED_IN;

    // Sends a success response with the result of the operation
    CommunicationModule::sendLoginResponse(logged_in_parameter);
}

void RequestModule::logout(Username username) {
    // The user is logged out
    UserModule::logoutUser(username);

    // Sends a success response
    CommunicationModule::sendSuccessResponse();
}

void RequestModule::refreshTtl(Username username) {
    // Refreshes the user TTL
    UserModule::refreshUserTtl(username);

    // Sends a success response
    CommunicationModule::sendSuccessResponse();
}

void RequestModule::removeUser(Username username) {
    if (! UserModule::userExists(username)) {
        // The user doesn't exist
        CommunicationModule::sendErrorResponse(USER_NOT_FOUND);
        return;
    }

    // Removes the user
    UserModule::removeUser(username);

    // Sends a success response
    CommunicationModule::sendSuccessResponse();
}

void RequestModule::requestState() {
    // Gets the information of the state of the system
    Parameter lock_closed_parameter = StateModule::isLockClosed() ? LOCK_CLOSED : LOCK_OPENED;
    Parameter light_off_parameter = StateModule::isLightOff() ? LIGHT_OFF : LIGHT_ON;
    Parameter light_disabled_parameter = StateModule::isLightDisabled() ? LIGHT_DISABLED : LIGHT_ENABLED;
    Temperature temperature = StateModule::getTemperature();
    Humidity humidity = StateModule::getHumidity();

    // Sends a success response with the information of the state of the system
    CommunicationModule::sendRequestStateResponse(lock_closed_parameter, light_off_parameter, light_disabled_parameter, temperature, humidity);
}

void RequestModule::requestUsers() {
    // Gets the usernames of the users of the system
    Username usernames[CAPACITY_USER_TABLE];
    int user_count = UserModule::getUserUsernames(usernames);

    // Sends a success response with the usernames
    CommunicationModule::sendRequestUsersResponse(user_count, usernames);
}

void RequestModule::toggleLight() {
    // Disables / enables the light
    StateModule::toggleLight();

    // Sends a success response
    CommunicationModule::sendSuccessResponse();
}

void RequestModule::toggleLock() {
    // Closes / opens the lock
    StateModule::toggleLock();

    // Sends a success response
    CommunicationModule::sendSuccessResponse();
}

bool RequestModule::validateInputs(Request request, Input inputs[INPUT_MAX_COUNT]) {
    if (! AuxiliarModule::isValidUsername(inputs[0]))
        // The petitioner username is invalid
        return false;

    switch (request) {
    case LOGOUT :
    case REFRESH_TTL :
    case REQUEST_STATE :
    case REQUEST_USERS :
    case TOGGLE_LIGHT :
    case TOGGLE_LOCK :
        return true;

    case ADD_USER : {
        if (! AuxiliarModule::isValidUsername(inputs[1]))
            return false;

        if (! AuxiliarModule::isValidPassword(inputs[2]))
            return false;

        return true;
    }

    case CHANGE_PASSWORD : {
        if (! AuxiliarModule::isValidPassword(inputs[1]))
            return false;

        return true;
    }

    case LOGIN : {
        if (! AuxiliarModule::isValidPassword(inputs[1]))
            return false;

        return true;
    }

    case REMOVE_USER : {
        if (! AuxiliarModule::isValidUsername(inputs[1]))
            return false;

        return true;
    }

    default :
        return false; // Invalid request
    }
}
