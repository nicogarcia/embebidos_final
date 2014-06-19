#include "MainModule.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Hello world, SISAD!");

    EventModule::initialize();

    StateModule::closeLock();
    StateModule::disableLight();
    StateModule::measureLightIntensity();
    StateModule::measureTemperatureAndHumidity();

    // TODO: to define: are we going to use some non-volatile storage?
    UserModule::addUser(ADMIN_DEFAULT_USERNAME, ADMIN_DEFAULT_PASSWORD, ADMIN);

    // TODO: add debug commands
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
}

void loop() {
    EventModule::checkEvent();
}
