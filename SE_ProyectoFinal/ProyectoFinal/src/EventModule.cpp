#include "EventModule.h"

Event EventModule::current_event = 0;
Time EventModule::event_times[EVENT_COUNT];

void EventModule::checkEvent() {
    //Check Bluetooth
    if (CommunicationModule::BTSerial.available())
        CommunicationModule::bluetoothEvent();


    // Get's the current time
    Time current_time = millis();

    if (event_times[current_event] > current_time)
        // The timer overflowed
        event_times[current_event] = 0;

    if (current_time - event_times[current_event] > EVENT_CHECK_PERIODS[current_event]) {
        // It's time to check the current event

        switch (current_event) {
        case DHT_MEASUREMENT : {
            dhtMeasurementEvent();
            break;
        }

        case LIGHT_INTENSITY_MEASUREMENT : {
            lightIntensityMeasurementEvent();
            break;
        }

        case TTL_EXPIRATION : {
            ttlExpirationEvent();
            break;
        }
        }

        // Sets the current time as the current event time
        event_times[current_event] = current_time;
    }

    // Sets the next event
    current_event = (current_event + 1) % EVENT_COUNT;
}

void EventModule::initializeSystem() {
    // Serial initialization tasks
    Serial.begin(BAUD_RATE);
    CommunicationModule::BTSerial.begin(BT_BAUD_RATE);
    Serial.println("Hello world, SISAD!");

    // State initialization tasks
    StateModule::closeLock();
    StateModule::disableLight();
    StateModule::measureLightIntensity();
    StateModule::measureTemperatureAndHumidity();

    // User initialization tasks
    // TODO: to define: are we going to use some non-volatile storage?
    UserModule::addUser(ADMIN_DEFAULT_USERNAME, ADMIN_DEFAULT_PASSWORD, ADMIN);

    // TODO: debug commands (remove them)
    Input input[INPUT_MAX_COUNT];

    input[0] = ADMIN_DEFAULT_USERNAME;
    input[1] = ADMIN_DEFAULT_PASSWORD;
    RequestModule::serveRequest(LOGIN, input);

    /*input[0] = ADMIN_DEFAULT_USERNAME;
    RequestModule::serveRequest(TOGGLE_LIGHT, input);

    input[0] = ADMIN_DEFAULT_USERNAME;
    RequestModule::serveRequest(TOGGLE_LOCK, input);

    input[0] = ADMIN_DEFAULT_USERNAME;
    RequestModule::serveRequest(REQUEST_STATE, input);*/
    input[0] = ADMIN_DEFAULT_USERNAME;
    input[1] = "fede";
    input[2] = "fedepw";
    RequestModule::serveRequest(ADD_USER, input);

    input[0] = ADMIN_DEFAULT_USERNAME;
    RequestModule::serveRequest(LOGOUT, input);

    input[0] = "fede";
    input[1] = "fedepw";
    RequestModule::serveRequest(LOGIN, input);

    input[0] = "fede";
    RequestModule::serveRequest(REQUEST_STATE, input);

    // Initializes the event times
    forn (i, EVENT_COUNT)
    event_times[i] = 0;
}

void EventModule::dhtMeasurementEvent() {
    // Measures the temperature and humidity
    StateModule::measureTemperatureAndHumidity();
}

void EventModule::lightIntensityMeasurementEvent() {
    // Measures the light intensity
    StateModule::measureLightIntensity();

    if (! StateModule::isLightDisabled()) {
        // Light is enabled

        // Gets the light intensity
        LightIntensity light_intensity = StateModule::getLightIntensity();

        if (light_intensity < LIGHT_INTENSITY_THRESHOLD)
            // The environment is too dark
            StateModule::turnOnLight();
        else
            // The environment is iluminated
            StateModule::turnOffLight();
    }
}

void EventModule::ttlExpirationEvent() {
    // Removes users whose TTLs have expired
    UserModule::autoLogoutUsers();

    // Decrements the TTLs of the remaining users
    UserModule::decrementUserTtls();
}
