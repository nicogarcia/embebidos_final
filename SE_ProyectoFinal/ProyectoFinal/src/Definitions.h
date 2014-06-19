#ifndef DEFINITIONS
#define DEFINITIONS

#include <Arduino.h>
#include "../lib/dht.h" // TODO: can be added to search path? (relative path)

#define forn(i, n) for (int i = 0; i < (int) (n); ++i)
#define forsn(i, s, n) for (int i = (int) (s); i < (int) (n); ++i)

typedef int Event;
typedef int Parameter;
typedef int Request;
typedef int Response;
typedef int Role;
typedef int Ttl;

typedef unsigned long int Time;

typedef int LightIntensity; // TODO: is it an int?
typedef int Humidity;
typedef int Temperature;

typedef String Input;
typedef String Username;
typedef String Password;

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
    TTL_EXPIRATION,
    DEBUG_EVENT, // TODO: remove this event
    EVENT_COUNT // This element should always be kept in the last position
};

enum Parameters {
    INVALID_INPUT = 0,
    LIGHT_DISABLED = 1,
    LIGHT_ENABLED = 2,
    LOCK_CLOSED = 3,
    LOCK_OPENED = 4,
    LOGGED_IN = 5,
    LOGIN_TABLE_FULL = 6,
    NOT_LOGGED_IN = 7,
    UNAUTHORIZED = 8,
    USER_ALREADY_EXISTS = 9,
    USER_NOT_FOUND = 10,
    USER_TABLE_FULL = 11
};

enum Requests {
    ADD_USER = 0,
    CHANGE_PASSWORD = 1,
    LOGIN = 2,
    REFRESH_TTL = 3,
    REMOVE_USER = 4,
    REQUEST_STATE = 5,
    REQUEST_USERS = 6,
    TOGGLE_LIGHT = 7,
    TOGGLE_LOCK = 8
};

enum Responses {
    ERROR = 0,
    SUCCESS = 1
};

enum Roles {
    ADMIN,
    USER
};

static const int INPUT_MAX_COUNT = 3;
static const int INPUT_MIN_LENGTH = 3;
static const int INPUT_MAX_LENGTH = 16;

static const int USER_TABLE_CAPACITY = 16; // Maximum number of users in the system
static const int LOGIN_TABLE_CAPACITY = 16; // Maximum number of logged in users

static const Ttl INITIAL_TTL = 40;

static const Username ADMIN_DEFAULT_USERNAME = "admin";
static const Password ADMIN_DEFAULT_PASSWORD = "12345";

static const char MESSAGE_BEGIN = '$';
static const char MESSAGE_PARAMETERS_SEPARATOR = '#';
static const char MESSAGE_END = '*';

static const uint8_t DHT_SENSOR_PIN = 2;

static const LightIntensity LIGHT_INTENSITY_THRESHOLD = 512; // TODO: calibrate this

static const Time EVENT_CHECK_PERIODS[EVENT_COUNT] = {
    // Milliseconds
    // The order of the elements is important
    2000, // DHT_MEASUREMENT
    1000, // LIGHT_INTENSITY_MEASUREMENT
    5000, // TTL_EXPIRATION
    2000 // TODO: remove this
};

#include "AuxiliarModule.h"
#include "CommunicationModule.h"
#include "DhtSensor.h"
#include "EventModule.h"
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
