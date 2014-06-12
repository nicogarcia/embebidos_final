#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include "Task.h"

typedef Task PQ_Type;
typedef unsigned long Prio_Type;

// Priority queue, min on top
class PriorityQueue {
public:
    // Queue max size
    static const unsigned int PQ_MAX_SIZE = 30;

    PriorityQueue();

    // Queue common interface methods
    void enqueue(PQ_Type element, Prio_Type priority);
    PQ_Type dequeue();
    PQ_Type front();
    bool isEmpty();

private:
    typedef struct pq_el {
        PQ_Type value;
        Prio_Type priority;

        // Greater than operator (on purpose assigned <= )
        bool operator>=(const struct pq_el& el) {
            return this->priority <= el.priority;
        }
        // Assignment operator
        void operator=(const struct pq_el& el) {
            this->value = el.value;
            this->priority = el.priority;
        }
    } PQ_Elem;

    // Queue count
    unsigned int count;

    // Queue data
    PQ_Elem pq_data[PQ_MAX_SIZE];
};

#endif /* PRIORITYQUEUE_H_ */