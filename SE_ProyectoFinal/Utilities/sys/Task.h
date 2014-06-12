#ifndef TASK_H_
#define TASK_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include "Arduino.h"

typedef void (*fptr)();


// Represents a task to do in "time" miliseconds.

class Task {
public:

    Task();

    Task(unsigned long time , fptr callback);

    //The time in miliseconds to do the task starting in the time when the
    //task was created
    unsigned long time;

    //The time when the task was created, when the actual time is equals to the start time plus
    //the time then the task is execute
    unsigned long tick_time;

    //the function that the task execute
    fptr callback;
};



#endif /* TASK_H_ */