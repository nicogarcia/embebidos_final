#ifndef DEFINITIONS
#define DEFINITIONS

#define DEBUG_MODE
//#define EEPROM_INITIALIZATION_MODE

#include <Arduino.h>
#include "SoftwareSerial.h"
#include <avr/eeprom.h>
#include "../lib/dht.h"

#define forn(i, n) for (int i = 0; i < (int) (n); ++i)
#define forsn(i, s, n) for (int i = (int) (s); i < (int) (n); ++i)

static const int REQUEST_MIN_LENGTH = 1;
static const int REQUEST_MAX_LENGTH = 2;

static const int INPUT_PARAMETER_MAX_COUNT = 3;
static const int INPUT_PARAMETER_MIN_LENGTH = 3;
static const int INPUT_PARAMETER_MAX_LENGTH = 16;

static const int INPUT_MAX_COUNT = 4;
static const int INPUT_MAX_LENGTH = max(REQUEST_MAX_LENGTH, INPUT_PARAMETER_MAX_LENGTH);

static const int INPUT_MESSAGE_MAX_LENGTH = REQUEST_MAX_LENGTH + INPUT_PARAMETER_MAX_COUNT * INPUT_PARAMETER_MAX_LENGTH + INPUT_PARAMETER_MAX_COUNT;

typedef uint8_t Event;
typedef uint8_t OutputParameter;
typedef uint8_t Request;
typedef uint8_t Response;
typedef uint8_t Role;

typedef int Humidity;
typedef int LightIntensity;
typedef int Temperature;
typedef int Ttl;

typedef unsigned long int Time;

typedef char InputParameter[INPUT_PARAMETER_MAX_LENGTH + 1];
typedef char Input[INPUT_MAX_LENGTH + 1];

typedef InputParameter Password;
typedef InputParameter Username;

typedef struct {
    Username username;
    Ttl ttl;
} LoginTableEntry;

typedef struct {
    Username username;
    Password password;
    Role role;
} UserTableEntry;

enum Events {
    // The order of the elements is important
    DHT_MEASUREMENT,
    LIGHT_INTENSITY_MEASUREMENT,
    LOCK_CLOSING,
    TTL_EXPIRATION,
    EVENT_COUNT // This element should always be kept in the last position
};

enum OutputParameters {
    INVALID_INPUT = 0,
    LIGHT_DISABLED = 1,
    LIGHT_ENABLED = 2,
    LIGHT_OFF = 3,
    LIGHT_ON = 4,
    LOCK_CLOSED = 5,
    LOCK_OPENED = 6,
    LOGGED_IN = 7,
    LOGIN_TABLE_FULL = 8,
    NOT_LOGGED_IN = 9,
    UNAUTHORIZED = 10,
    USER_ALREADY_EXISTS = 11,
    USER_NOT_FOUND = 12,
    USER_TABLE_FULL = 13
};

enum Requests {
    ADD_USER = 0,
    CHANGE_PASSWORD = 1,
    LOGIN = 2,
    LOGOUT = 3,
    REFRESH_TTL = 4,
    REMOVE_USER = 5,
    REQUEST_STATE = 6,
    REQUEST_USERS = 7,
    TOGGLE_LIGHT = 8,
    TOGGLE_LOCK = 9
};

enum Responses {
    ERROR = 0,
    SUCCESS = 1
};

enum Roles {
    ADMIN,
    USER
};

static const uint8_t ANALOG_PIN_LIGHT_SENSOR = 3;
static const uint8_t DIGITAL_PIN_DHT_SENSOR = 2;
static const uint8_t DIGITAL_PIN_LIGHT = 11;
static const uint8_t DIGITAL_PIN_LOCK = 12;
static const uint8_t DIGITAL_PIN_SOFTWARE_SERIAL_RECEPTION = 7;
static const uint8_t DIGITAL_PIN_SOFTWARE_SERIAL_TRANSMISSION = 6;

static const long int BAUD_RATE_BLUETOOTH_INTERFACE = 9600;
static const long int BAUD_RATE_MONITOR_INTERFACE = 9600;

static const char MESSAGE_BEGIN = '$';
static const char MESSAGE_INPUTS_SEPARATOR = '#';
static const char MESSAGE_END = '*';

static const int CAPACITY_USER_TABLE = 8; // Maximum number of users in the system
static const int CAPACITY_LOGIN_TABLE = 8; // Maximum number of logged in users

static const uint16_t USER_TABLE_EEPROM_LENGTH_ADDRESS = 0;
static const uint16_t USER_TABLE_EEPROM_LENGTH_SIZE = sizeof(uint8_t);
static const uint16_t USER_TABLE_EEPROM_ENTRIES_ADDRESS = USER_TABLE_EEPROM_LENGTH_ADDRESS + USER_TABLE_EEPROM_LENGTH_SIZE;
static const uint16_t USER_TABLE_EEPROM_ENTRY_SIZE = sizeof(UserTableEntry);

static const Ttl INITIAL_TTL = 24;

static Username ADMIN_DEFAULT_USERNAME = "admin";
static Password ADMIN_DEFAULT_PASSWORD = "12345";

static const Humidity HUMIDITY_UNKNOWN = -1;
static const Temperature TEMPERATURE_UNKNOWN = 0;

static const LightIntensity LIGHT_INTENSITY_AVERAGE_THRESHOLD = 100;
static const LightIntensity LIGHT_INTENSITY_MAX = 1023;
static const LightIntensity LIGHT_INTENSITY_QUEUE_CAPACITY = 10;

static const Time EVENT_CHECK_PERIODS[EVENT_COUNT] = {
    // Milliseconds
    // The order of the elements is important
    2000, // DHT_MEASUREMENT
    200, // LIGHT_INTENSITY_MEASUREMENT
    5000, // LOCK_CLOSING
    5000 // TTL_EXPIRATION
};

#include "AuxiliarModule.h"
#include "CommunicationModule.h"
#include "DhtSensor.h"
#include "Light.h"
#include "LightIntensityQueue.h"
#include "LightSensor.h"
#include "Lock.h"
#include "LoginTable.h"
#include "MainModule.h"
#include "RequestModule.h"
#include "SecurityModule.h"
#include "StateModule.h"
#include "UserModule.h"
#include "UserTable.h"
#include "UserTableEeprom.h"

#endif // DEFINITIONS