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


    // TODO: debug code
    Input inputs[INPUT_MAX_COUNT];

    strcpy(inputs[0] , "2"); // LOGIN
    strcpy(inputs[1] , ADMIN_DEFAULT_USERNAME);
    strcpy(inputs[2] , ADMIN_DEFAULT_PASSWORD);
    RequestModule::serveRequest(inputs);

    /*
        strcpy(inputs[0] , "0"); // ADD_USER
        strcpy(inputs[1] , ADMIN_DEFAULT_USERNAME);
        strcpy(inputs[2] , "lala");
        strcpy(inputs[3] , "lala");
        RequestModule::serveRequest(inputs);
    	*/

    strcpy(inputs[0] , "7"); // REQUEST_USERS
    strcpy(inputs[1] , ADMIN_DEFAULT_USERNAME);
    RequestModule::serveRequest(inputs);

    /*
        strcpy(inputs[0] , "2"); // LOGIN
        strcpy(inputs[1] , ADMIN_DEFAULT_USERNAME);
        strcpy(inputs[2] , ADMIN_DEFAULT_PASSWORD);
        RequestModule::serveRequest(inputs);
    	*/

    /*
        strcpy(inputs[0] , "0"); // ADD_USER
        strcpy(inputs[1] , ADMIN_DEFAULT_USERNAME);
        strcpy(inputs[2] , "lala");
        strcpy(inputs[3] , "lala");
        RequestModule::serveRequest(inputs);
    	*/
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
