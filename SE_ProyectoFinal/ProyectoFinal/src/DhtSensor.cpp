#include "DhtSensor.h"

dht DhtSensor::sensor;
Humidity DhtSensor::humidity;
Temperature DhtSensor::temperature;

Humidity DhtSensor::getHumidity() {
    return humidity;
}

Temperature DhtSensor::getTemperature() {
    return temperature;
}

void DhtSensor::measure() {
    // Measures the humidity and temperature
    int result = sensor.read11(PIN_DHT_SENSOR);

    if (result == DHTLIB_OK) {
        // The measurement is correct
        humidity = (Humidity) sensor.humidity;
        temperature = (Temperature) sensor.temperature;
    } else {
        // There was a problem with the measurement
        humidity = UNKNOWN_HUMIDITY;
        temperature = UNKNOWN_TEMPERATURE;
    }
}
