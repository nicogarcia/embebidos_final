#include "MainModule.h"

void setup() {
    MainModule::initialize();
}

void loop() {
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

        switch (current_event) {
#ifdef DEBUG_MODE
        case BLUETOOTH_CHECK : {
            bluetoothCheckEvent();
            break;
        }
#endif /* DEBUG_MODE */

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
    // Pin modes
    pinMode(PIN_LIGHT, OUTPUT);
    pinMode(PIN_LOCK, OUTPUT);

    // Communication initialization tasks
    CommunicationModule::initialize();
#ifdef DEBUG_MODE
    Serial.begin(BAUD_RATE_TERMINAL);
    Serial.println("Hello from SISAD");
#endif /* DEBUG_MODE */

    // State initialization tasks
    StateModule::closeLock();
    StateModule::disableLight();
    StateModule::measureLightIntensity();
    StateModule::measureTemperatureAndHumidity();

    // Adds a default administrator
    UserModule::addUser(ADMIN_DEFAULT_USERNAME, ADMIN_DEFAULT_PASSWORD, ADMIN); // TODO: to define: are we going to use some non-volatile storage?

    // Initializes the event times
    forn (i, EVENT_COUNT)
    event_times[i] = 0;
}

#ifdef DEBUG_MODE
void MainModule::bluetoothCheckEvent() {
    CommunicationModule::serialEvent();
}
#endif /* DEBUG_MODE */

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
        LightIntensity light_intensity = StateModule::getLightIntensity();

        if (light_intensity < LIGHT_INTENSITY_THRESHOLD)
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
