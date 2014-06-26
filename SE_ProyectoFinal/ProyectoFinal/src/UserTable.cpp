#include "UserTable.h"
#include <avr/eeprom.h>


UserTableEntry UserTable::entries[CAPACITY_USER_TABLE];
uint8_t UserTable::length;

void UserTable::addEntry(Username username, Password password, Role role) {
    if (length == CAPACITY_USER_TABLE)
        // The table is full
        return;

    // Creates a new entry
    entries[length].username = username;
    entries[length].password = password;
    entries[length].role = role;
    length++;

    updateEEPROM(entries[length-1].username,entries[length-1].password,role,length-1);
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

void UserTable::initialize() {
#ifdef FIRST_USE_MODE
    eeprom_write_byte((uint8_t*)EEPROM_TABLE_LENGTH_ADDRESS,0);
#endif //FIRTS_USE_MODE

    length = 0;
    readEEPROM();
}

bool UserTable::isEmpty() {
    return length == 0;
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
    updateEEPROM(entries[index].username,entries[index].password,entries[index].role,index);
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

    //Buffer to put the string
    char aux[INPUT_PARAMETER_MAX_LENGTH+1];


    while (!eeprom_is_ready())
        ;
    eeprom_write_byte(EEPROM_TABLE_LENGTH_ADDRESS, length);

    //address eeprom memory to put the username
    uint16_t base_address = EEPROM_TABLE_LENGTH_ADDRESS + EEPROM_TABLE_LENGTH_LENGTH + index*EEPROM_USER_LENGTH;
    AuxiliarModule::stringToCharArray(username,aux);

    while (!eeprom_is_ready())
        ;
    eeprom_write_block(aux, (void *)base_address, username.length());
    //write null char
    eeprom_write_byte((uint8_t*)base_address+username.length(),0);

    base_address += INPUT_PARAMETER_MAX_LENGTH + 1;

    while (!eeprom_is_ready())
        ;
    AuxiliarModule::stringToCharArray(password,aux);
    eeprom_write_block(aux, (void *)base_address, password.length());
    //write null char
    eeprom_write_byte((uint8_t*)base_address+password.length(),0);


    base_address+= INPUT_PARAMETER_MAX_LENGTH + 1;


    eeprom_write_byte((uint8_t*)base_address,role);

}


void UserTable::readEEPROM() {
    while (!eeprom_is_ready())
        ;
    length = eeprom_read_word(EEPROM_TABLE_LENGTH_ADDRESS);

//TODO: Write 0 in EEPROM_TABLE_LENGTH_ADDRESS EEPROM address

    char username[INPUT_PARAMETER_MAX_LENGTH + 1];
    char password[INPUT_PARAMETER_MAX_LENGTH + 1];
    uint8_t role;

    uint16_t baseaddress = EEPROM_TABLE_LENGTH_ADDRESS + EEPROM_TABLE_LENGTH_LENGTH;


    //For each user
    forn(i,length) {

        while (!eeprom_is_ready())
            ;
        eeprom_read_block(username,(void*)baseaddress,INPUT_PARAMETER_MAX_LENGTH + 1);

        //update baseaddress to read the password
        baseaddress+= INPUT_PARAMETER_MAX_LENGTH + 1;
        while(!eeprom_is_ready())
            ;
        eeprom_read_block(password,(void*)baseaddress,INPUT_PARAMETER_MAX_LENGTH + 1);

        //update baseaddress to read the role
        baseaddress+=INPUT_PARAMETER_MAX_LENGTH + 1;

        //Read the user role
        while (!eeprom_is_ready())
            ;
        role = eeprom_read_byte((uint8_t*)baseaddress);


        //add the user
        entries[i].username = String(username);
        entries[i].password = String(password);
        entries[i].role = role;

        //update base address
        baseaddress+=1;
    }
}

