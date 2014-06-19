#include "EventModule.h"

Event EventModule::current_event = 0;
Time EventModule::event_times[EVENT_COUNT];

void EventModule::checkEvent() {
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

        // TODO: remove this
        case DEBUG_EVENT : {
            debugEvent();
            break;
        }
        }

        // Sets the current time as the current event time
        event_times[current_event] = current_time;
    }

    // Sets the next event
    current_event = (current_event + 1) % EVENT_COUNT;
}

void EventModule::initialize() {
    forn (i, EVENT_COUNT)
    event_times[i] = 0;
}

void EventModule::dhtMeasurementEvent() {
    // Measures the temperature and humidity
    StateModule::measureTemperatureAndHumidity();
}

void EventModule::lightIntensityMeasurementEvent() {
    // TODO: what to do

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
    UserModule::autoLogout();

    // Decrements the TTLs of the remaining users
    UserModule::decrementTtls();
}

// TODO: remove this
void EventModule::debugEvent() {
    Serial.println("------");
    Serial.println("T: " + String(StateModule::getTemperature()));
    Serial.println("H: " + String(StateModule::getHumidity()));
}
