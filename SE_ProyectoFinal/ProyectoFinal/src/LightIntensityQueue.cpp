#include "LightIntensityQueue.h"

int LightIntensityQueue::head;
LightIntensity LightIntensityQueue::light_intensities[LIGHT_INTENSITY_QUEUE_CAPACITY];
int LightIntensityQueue::tail;

LightIntensity LightIntensityQueue::getBack() {
    if (isEmpty())
        // The queue is empty
        return 0;

    return light_intensities[tail];
}

LightIntensity LightIntensityQueue::getFront() {
    if (isEmpty())
        // The queue is empty
        return 0;

    return light_intensities[head];
}

int LightIntensityQueue::getLength() {
    if (head < 0 || tail < 0)
        // The queue is empty
        return 0;

    if (tail < head)
        return tail - head + 1 + LIGHT_INTENSITY_QUEUE_CAPACITY;
    else
        return tail - head + 1;
}

void LightIntensityQueue::initialize() {
    head = -1;
    tail = -1;
}

bool LightIntensityQueue::isEmpty() {
    return getLength() == 0;
}

bool LightIntensityQueue::isFull() {
    return getLength() == LIGHT_INTENSITY_QUEUE_CAPACITY;
}

void LightIntensityQueue::pop() {
    if (isEmpty())
        // The queue is empty
        return;

    if (getLength() == 1) {
        // The queue has exactly 1 light intensity
        head = -1;
        tail = -1;
    } else
        head = (head + 1) % LIGHT_INTENSITY_QUEUE_CAPACITY;
}

void LightIntensityQueue::push(LightIntensity light_intensity) {
    if (isFull())
        // The queue is full
        return;

    if (isEmpty()) {
        // The queue is empty
        head = 0;
        tail = 0;
    } else
        tail = (tail + 1) % LIGHT_INTENSITY_QUEUE_CAPACITY;

    light_intensities[tail] = light_intensity;
}
