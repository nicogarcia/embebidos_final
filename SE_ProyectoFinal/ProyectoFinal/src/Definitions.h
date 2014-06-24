#ifndef DEFINITIONS
#define DEFINITIONS

#define DEBUG_MODE

#include <Arduino.h>
#include "SoftwareSerial.h"
#include "../lib/dht.h" // TODO: can be added to search path? (relative path)

#define forn(i, n) for (int i = 0; i < (int) (n); ++i)
#define forsn(i, s, n) for (int i = (int) (s); i < (int) (n); ++i)

typedef uint8_t Event;
typedef uint8_t Parameter;
typedef uint8_t Request;
typedef uint8_t Response;
typedef uint8_t Role;

typedef int Humidity;
typedef int LightIntensity;
typedef int Temperature;
typedef int Ttl;

typedef unsigned long int Time;

typedef String Input;
typedef String Password;
typedef String Username;

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
#ifdef DEBUG_MODE
    BLUETOOTH_CHECK,
#endif /* DEBUG_MODE */
    DHT_MEASUREMENT,
    LIGHT_INTENSITY_MEASUREMENT,
    TTL_EXPIRATION,
    EVENT_COUNT // This element should always be kept in the last position
};

enum Parameters {
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

static const uint8_t PIN_DHT_SENSOR = 2;
static const uint8_t PIN_LIGHT = 13;
static const uint8_t PIN_LIGHT_SENSOR = 3;
static const uint8_t PIN_LOCK = 12;
static const uint8_t PIN_SOFTWARE_SERIAL_RECEPTION = 7;
static const uint8_t PIN_SOFTWARE_SERIAL_TRANSMISSION = 6;

static const int REQUEST_MAX_LENGTH = 2;

static const int INPUT_MAX_COUNT = 3;
static const int INPUT_MIN_LENGTH = 3;
static const int INPUT_MAX_LENGTH = 16;

static const int MESSAGE_MAX_LENGTH = REQUEST_MAX_LENGTH + INPUT_MAX_COUNT * INPUT_MAX_LENGTH + INPUT_MAX_COUNT;

static const char MESSAGE_BEGIN = '$';
static const char MESSAGE_PARAMETERS_SEPARATOR = '#';
static const char MESSAGE_END = '*';

static const long int BAUD_RATE_BLUETOOTH = 9600;
static const long int BAUD_RATE_TERMINAL = 9600;

static const int CAPACITY_USER_TABLE = 16; // Maximum number of users in the system
static const int CAPACITY_LOGIN_TABLE = 16; // Maximum number of logged in users

static const Ttl INITIAL_TTL = 40;

static const Username ADMIN_DEFAULT_USERNAME = "admin";
static const Password ADMIN_DEFAULT_PASSWORD = "12345";

static const Humidity UNKNOWN_HUMIDITY = -1;
static const LightIntensity UNKNOWN_LIGHT_INTENSITY = -1;
static const Temperature UNKNOWN_TEMPERATURE = 0;

static const LightIntensity LIGHT_INTENSITY_THRESHOLD = 280;

static const Time EVENT_CHECK_PERIODS[EVENT_COUNT] = {
    // Milliseconds
    // The order of the elements is important
#ifdef DEBUG_MODE
    0, // BLUETOOTH_CHECK
#endif /* DEBUG_MODE */
    2000, // DHT_MEASUREMENT
    1000, // LIGHT_INTENSITY_MEASUREMENT
    5000 // TTL_EXPIRATION
};

#include "AuxiliarModule.h"
#include "CommunicationModule.h"
#include "DhtSensor.h"
#include "Light.h"
#include "LightSensor.h"
#include "Lock.h"
#include "LoginTable.h"
#include "MainModule.h"
#include "RequestModule.h"
#include "SecurityModule.h"
#include "StateModule.h"
#include "UserModule.h"
#include "UserTable.h"

#endif /* DEFINITIONS */
