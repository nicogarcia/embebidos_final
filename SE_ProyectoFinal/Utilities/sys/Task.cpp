#include "Task.h"

Task::Task() {
    time = 0;
    callback = NULL;
    tick_time = 0;
}

Task::Task(unsigned long time_, fptr callback_ ) {
    time = time_;
    callback = callback_;
    tick_time = 0;
}