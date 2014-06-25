#include "UserTable.h"
#include <avr/eeprom.h>


UserTableEntry UserTable::entries[CAPACITY_USER_TABLE];
int UserTable::length = 0;

void UserTable::addEntry(Username username, Password password, Role role) {
    if (length == CAPACITY_USER_TABLE)
        // The table is full
        return;

    // Creates a new entry
    entries[length].username = username;
    entries[length].password = password;
    entries[length].role = role;
    length++;
}

UserTableEntry *UserTable::getEntries() {
    return entries;
}

UserTableEntry *UserTable::getEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if (index < 0)
        // The entry has not been found
        return NULL;

    return &entries[index];
}

int UserTable::getEntryIndex(Username username) {
    // Searches for the entry
    forn (i, length)
    if (username == entries[i].username)
        // The entry has been found
        return i;

    // The entry has not been found
    return -1;
}

int UserTable::getLength() {
    return length;
}

bool UserTable::isFull() {
    return length == CAPACITY_USER_TABLE;
}

void UserTable::removeEntry(int index) {
    if (index < 0 || index >= CAPACITY_USER_TABLE)
        // Invalid index
        return;

    //If it's the last one, doesn't do anything, else replace for the last one
    entries[index] = entries[length - 1];

    length--;
}

void UserTable::removeEntry(Username username) {
    // Searches for the entry index
    int index = getEntryIndex(username);

    if (index < 0)
        // The entry has not been found
        return;

    // Actually removes the entry
    removeEntry(index);
}

void UserTable::updateEEPROM( Username username,Password password, Role role, int index) {

    int usernameAddresses[INPUT_MAX_LENGTH+1];//plus 1 for null char
    int passwordAddresses[INPUT_MAX_LENGTH+1];
    //Buffer to put the string
    char aux[INPUT_MAX_LENGTH+1];


    if (eeprom_is_ready())
        eeprom_write_byte(EEPROM_TABLE_LENGTH_ADDRESS, length);

    //address eeprom memory to put the username
    uint16_t base_address = EEPROM_TABLE_LENGTH_ADDRESS + EEPROM_TABLE_LENGTH_LENGTH + index*EEPROM_USER_LENGTH;

    if (eeprom_is_ready()) {
        username.toCharArray(aux,username.length()+1);
        //set of address for username
        forn(i,username.length()+1)
        usernameAddresses[i] = base_address + i;
        eeprom_write_block(aux, usernameAddresses, username.length()+1);
    }


    if (eeprom_is_ready()) {
        base_address += INPUT_MAX_LENGTH + 1;
        password.toCharArray(aux,password.length()+1);
        //set of address for password
        forn(i,password.length()+1)
        passwordAddresses[i] = base_address + i;
        eeprom_write_block(aux, passwordAddresses, password.length()+1);
    }

    base_address+= INPUT_MAX_LENGTH + 1;
    //
    if (eeprom_is_ready())
        eeprom_write_byte((uint8_t*)base_address,role);

}


void UserTable::readEEPROM() {
    if (eeprom_is_ready())
        length = eeprom_read_word(EEPROM_TABLE_LENGTH_ADDRESS);

    if (length == 0)
        ;

    char username[INPUT_MAX_LENGTH + 1];
    char password[INPUT_MAX_LENGTH + 1];
    int role;

    int address[INPUT_MAX_LENGTH + 1];

    uint16_t baseaddress = EEPROM_TABLE_LENGTH_ADDRESS + EEPROM_TABLE_LENGTH_LENGTH;


    //For each user
    forn(i,length) {

        if (eeprom_is_ready()) {
            //get username address
            forn(j,INPUT_MAX_LENGTH + 1)
            address[j] = baseaddress + j;
            eeprom_read_block(username,address,INPUT_MAX_LENGTH + 1);
        }

        if(eeprom_is_ready()) {
            //update baseaddress to read the password
            baseaddress+= INPUT_MAX_LENGTH + 1;
            forn(j,INPUT_MAX_LENGTH + 1)
            address[j] = baseaddress + j;
            eeprom_read_block(password,address,INPUT_MAX_LENGTH + 1);
        }
        //Read the user role
        if (eeprom_is_ready()) {
            //update baseaddress to read the role
            baseaddress+=INPUT_MAX_LENGTH + 1;
            role = eeprom_read_byte((uint8_t*)baseaddress);
        }

        //add the user
        addEntry(username,password,role);

        //update base address
        baseaddress+=1;
    }
}

