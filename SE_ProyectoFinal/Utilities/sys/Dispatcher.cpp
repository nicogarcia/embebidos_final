#include "Arduino.h"
#include "Dispatcher.h"
#include <avr/io.h>
#include <avr/interrupt.h>

Dispatcher_ Dispatcher;

Dispatcher_::Dispatcher_() {

    ReadyTasksQueue = ArrayQueue();

    init_timer2();
}

// Get system millis
unsigned long Dispatcher_::getMillis() {
    return millis();
}

// Initialize TIMER0 parameters
void Dispatcher_::init_timer2() {
    // Initialize timer0
    noInterrupts();           // Disable all interrupts

    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2  = 0;				  // Initialize counter

    OCR2A = 249;              // Compare match register 16MHz/64=250KHz --> 1ms*250KHz -1 = 249
    TCCR2A |= (1 << WGM21) ;   // CTC mode

    TCCR2B |= (1 << CS22);    // 64 prescaler

    TIMSK2 |= (1 << OCIE2A);  // Enable timer compare interrupt
    interrupts();             // Enable all interrupts
}

// Attach callback, FIXME: time and tick time could be the same
void Dispatcher_::attach(Task task) {
    //set the start_time (the current time)
    task.tick_time = getMillis() + task.time;
    attach(task, task.tick_time);
}

// Attach callback, FIXME: time and tick time could be the same
void Dispatcher_::attach(Task task, unsigned long priority) {
    PendingTasks.enqueue(task, priority);
}

// Check if there's a callback to call
//TODO: if  attach is executing when there are functions to be called,
void Dispatcher_::checkEvents() {
    while(ReadyTasksQueue.execute()) {}
}

void Dispatcher_::enqueueReadyFunction(fptr function) {
    ReadyTasksQueue.enqueue(function);
}

// Timer ISR to count millis
void TIMER2_COMPA_vect() {

    // Check PendingTasksQueue, if there are ready, move to ReadyQueue
    while(!Dispatcher.PendingTasks.isEmpty()) {
        Task current_task = Dispatcher.PendingTasks.front();

        // If tick_time has passed put callback in ReadyQueue, else, break loop
        if(millis() >= current_task.tick_time) {
            Dispatcher.ReadyTasksQueue.enqueue(current_task.callback);
            Dispatcher.PendingTasks.dequeue();
        } else
            break;
    }

}