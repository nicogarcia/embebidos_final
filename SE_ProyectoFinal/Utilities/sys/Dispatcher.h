#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Task.h"
#include "ArrayQueue.h"
#include "PriorityQueue.h"

// Define C extern for ISR
extern "C" void TIMER2_COMPA_vect(void) __attribute__((signal));

// Take account of the system time is always less than 2**32 millis
// 2**32 millis are 50 days
class Dispatcher_ {
public:
    Dispatcher_();
    // Get system millis
    unsigned long getMillis();

    // Checks if there's a callback to execute
    void checkEvents();

    // Attach callback to pending queue
    void attach(Task task);
    void attach(Task task, unsigned long priority);
    // Enqueue ready callback to execute
    void enqueueReadyFunction(fptr function);
private:
    // Initialize TIMER2 parameters
    void init_timer2();

    // A queue of functions to be called
    ArrayQueue ReadyTasksQueue;

    // A queue for pending tasks
    PriorityQueue PendingTasks;

    // Timer ISR to count millis
    friend void TIMER2_COMPA_vect();
};

extern Dispatcher_ Dispatcher;

#endif /* DISPATCHER_H_ */