#ifndef LIGHT_INTENSITY_QUEUE
#define LIGHT_INTENSITY_QUEUE

#include "Definitions.h"

class LightIntensityQueue {
public:
    static LightIntensity getBack();
    static LightIntensity getFront();
    static int getLength();
    static void initialize();
    static bool isEmpty();
    static bool isFull();
    static void pop();
    static void push(LightIntensity element);
private:
    static LightIntensity elements[LIGHT_INTENSITY_QUEUE_CAPACITY];
    static int head;
    static int tail;
};

#endif /* LIGHT_INTENSITY_QUEUE */
