#include "MainModule.h"

void setup() {
    MainModule::initialize();
}

void loop() {
    CommunicationModule::readRequest();
    MainModule::checkEvent();
}

Event MainModule::current_event = 0;
Time MainModule::event_times[EVENT_COUNT];

void MainModule::checkEvent() {
    // Get's the current time
    Time current_time = millis();

    if (event_times[current_event] > current_time)
        // The timer overflowed
        event_times[current_event] = 0;

    if (current_time - event_times[current_event] > EVENT_CHECK_PERIODS[current_event]) {
        // It's time to check the current event

        switch(current_event) {
        case LOCK_CLOSING : {
            lockClosingEvent();
            break;
        }

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
    forn (i, EVENT_COUNT) {
        event_times[i] = 0;
    }

#ifdef DEBUG_MODE
    CommunicationModule::debug();
#endif // DEBUG_MODE
}

void MainModule::resetEventTime(Event event) {
    // Sets the current time as the event time
    event_times[event] = millis();
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

void MainModule::lockClosingEvent() {
    // Closes the lock
    StateModule::closeLock();
}

void MainModule::ttlExpirationEvent() {
    // Removes users whose TTLs have expired
    UserModule::autoLogoutUsers();

    // Decrements the TTLs of the remaining users
    UserModule::decrementUserTtls();
}
