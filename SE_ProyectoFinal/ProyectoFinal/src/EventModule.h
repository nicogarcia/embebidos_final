#ifndef EVENT_MODULE
#define EVENT_MODULE

#include "Definitions.h"

class EventModule {
public:
    static void checkEvent();
    static void initializeSystem();
private:
    static Event current_event;
    static Time event_times[EVENT_COUNT];
#ifdef DEBUG_MODE
    static void bluetoothCheckEvent();
#endif /* DEBUG_MODE */
    static void dhtMeasurementEvent();
    static void lightIntensityMeasurementEvent();
    static void ttlExpirationEvent();
};

#endif /* EVENT_MODULE */
