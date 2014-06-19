#ifndef EVENT_MODULE
#define EVENT_MODULE

#include "Definitions.h"

class EventModule {
public:
    static void checkEvent();
    static void initialize();
private:
    static Event current_event;
    static Time event_times[EVENT_COUNT];
    static void dhtMeasurementEvent();
    static void lightIntensityMeasurementEvent();
    static void ttlExpirationEvent();
    static void debugEvent(); // TODO: remove this
};

#endif /* EVENT_MODULE */
