#ifndef MAIN_MODULE
#define MAIN_MODULE

#include "Definitions.h"

void setup();
void loop();

class MainModule {
public:
    static void checkEvent();
    static void initialize();
    static void resetEventTime(Event event);
private:
    static Event current_event;
    static Time event_times[EVENT_COUNT];
    static void dhtMeasurementEvent();
    static void lightIntensityMeasurementEvent();
    static void lockClosingEvent();
    static void ttlExpirationEvent();
};

#endif // MAIN_MODULE
