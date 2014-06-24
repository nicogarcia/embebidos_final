#include "MainModule.h"

void setup() {
    MainModule::initialize();
}

void loop() {
#ifdef DEBUG_MODE
    CommunicationModule::serialEvent();
#endif /* DEBUG_MODE */

    MainModule::checkEvent();
}

Event MainModule::current_event = 0;
Time MainModule::event_times[EVENT_COUNT];

void MainModule::checkEvent() {
    // TODO: remove
    Serial.println(StateModule::getLightIntensityAverage());

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

void MainModule::initialize() {
    // Modules initializations
    CommunicationModule::initialize();
    StateModule::initialize();
    UserModule::initialize();

    // Initializes the event times
    forn (i, EVENT_COUNT)
    event_times[i] = 0;

    // TODO: add debug commands
    Input input[INPUT_MAX_COUNT];

    input[0] = ADMIN_DEFAULT_USERNAME;
    input[1] = ADMIN_DEFAULT_PASSWORD;
    RequestModule::serveRequest(LOGIN, input);

    input[0] = ADMIN_DEFAULT_USERNAME;
    RequestModule::serveRequest(TOGGLE_LIGHT, input);

    input[0] = ADMIN_DEFAULT_USERNAME;
    RequestModule::serveRequest(REQUEST_STATE, input);
}

void MainModule::dhtMeasurementEvent() {
    // Measures the temperature and humidity
    StateModule::measureTemperatureAndHumidity();
}

void MainModule::lightIntensityMeasurementEvent() {
    // Measures the light intensity
    StateModule::measureLightIntensity();

    if (! StateModule::isLightDisabled()) {
        // Light is enabled

        // Gets the light intensity
        LightIntensity light_intensity = StateModule::getLightIntensityAverage();

        if (light_intensity < LIGHT_INTENSITY_AVERAGE_THRESHOLD)
            // The environment is too dark
            StateModule::turnOnLight();
        else
            // The environment is iluminated
            StateModule::turnOffLight();
    }
}

void MainModule::ttlExpirationEvent() {
    // Removes users whose TTLs have expired
    UserModule::autoLogoutUsers();

    // Decrements the TTLs of the remaining users
    UserModule::decrementUserTtls();
}
