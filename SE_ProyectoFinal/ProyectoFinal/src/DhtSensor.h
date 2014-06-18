#ifndef DHT_SENSOR
#define DHT_SENSOR

#include "Definitions.h"

class DhtSensor {
public:
    static Humidity getHumidity();
    static Temperature getTemperature();
    static void measure();
private:
    static dht sensor;
    static Humidity humidity;
    static Temperature temperature;
};

#endif /* DHT_SENSOR */
