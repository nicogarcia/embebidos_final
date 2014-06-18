#include "UserModule.h"

void UserModule::addUser(Username username, Password password, Role role) {
    UserTable::addEntry(username, password, role);
}

bool UserModule::authenticateUser(Username username, Password password) {
    UserTableEntry *entry = UserTable::getEntry(username);
    if (entry == NULL)
        return false;

    return password == entry->password;
}

void UserModule::autoLogout() {
    LoginTable::removeExpiredEntries();
}

void UserModule::changeUserPassword(Username username, Password password) {
    Role role = UserTable::getEntry(username)->role;
    UserTable::removeEntry(username);
    UserTable::addEntry(username, password, role);
}

void UserModule::decrementTtls() {
    LoginTable::decrementTtls();
}

Role UserModule::getUserRole(Username username) {
    return UserTable::getEntry(username)->role;
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
