#include "UserModule.h"

void UserModule::addUser(Username username, Password password, Role role) {
    UserTable::addEntry(username, password, role);
}

bool UserModule::authenticateUser(Username username, Password password) {
    UserTableEntry *entry = UserTable::getEntry(username);
    if(entry == NULL)
        return false;

    return strcmp(password, entry->password) == 0;
}

void UserModule::autoLogoutUsers() {
    // Gets the login table entries
    LoginTableEntry *entries = LoginTable::getEntries();

    forn(i, LoginTable::getLength()) {
        if(entries[i].ttl <= 0) {
            // The entry has expired
            LoginTable::removeEntry(i);
            i--; // The next index to check is the same of the entry that was removed
        }
    }
}

void UserModule::changeUserPassword(Username username, Password password) {
    Role role = UserTable::getEntry(username)->role;
    UserTable::removeEntry(username);
    UserTable::addEntry(username, password, role);
}

void UserModule::decrementUserTtls() {
    // Gets the login table length and entries
    uint8_t length = LoginTable::getLength();
    LoginTableEntry *entries = LoginTable::getEntries();

    // Decrements the TTLs
    forn(i, length) {
        entries[i].ttl--;
    }
}

Role UserModule::getUserRole(Username username) {
    return UserTable::getEntry(username)->role;
}

uint8_t UserModule::getUserUsernames(Username usernames[CAPACITY_USER_TABLE]) {
    uint8_t user_count = 0;

    // Gets the user table length and entries
    uint8_t length = UserTable::getLength();
    UserTableEntry *entries = UserTable::getEntries();

    forn(i, length) {
        if(entries[i].role != ADMIN)
            // The user is not an administrator
            strcpy(usernames[user_count++], entries[i].username);
    }

    return user_count;
}

void UserModule::initialize() {
    // Modules initializations
    LoginTable::initialize();
    UserTable::initialize();

    if(UserTable::isEmpty()) {
        // There are no users: adds a default administrator
        addUser(ADMIN_DEFAULT_USERNAME, ADMIN_DEFAULT_PASSWORD, ADMIN);
    }
}

bool UserModule::isLoginTableFull() {
    return LoginTable::isFull();
}

bool UserModule::isUserLoggedIn(Username username) {
    return LoginTable::getEntry(username) != NULL;
}

bool UserModule::isUserTableFull() {
    return UserTable::isFull();
}

void UserModule::loginUser(Username username) {
    LoginTable::addEntry(username, INITIAL_TTL);
}

void UserModule::logoutUser(Username username) {
    LoginTable::removeEntry(username);
}

void UserModule::refreshUserTtl(Username username) {
    LoginTableEntry *entry = LoginTable::getEntry(username);
    entry->ttl = INITIAL_TTL;
}

void UserModule::removeUser(Username username) {
    LoginTable::removeEntry(username);
    UserTable::removeEntry(username);
}

bool UserModule::userExists(Username username) {
    return UserTable::getEntry(username) != NULL;
}
