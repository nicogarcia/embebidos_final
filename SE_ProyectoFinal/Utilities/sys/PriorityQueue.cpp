#include "PriorityQueue.h"

// Heap implementation based on
// https://gist.github.com/martinkunev/1365481

PriorityQueue::PriorityQueue() {
    count = 0;
}

void PriorityQueue::enqueue( PQ_Type element , unsigned long priority) {
    unsigned int index, parent;

    // Ignore data if queue is null
    if (count == PQ_MAX_SIZE)
        return;

    PQ_Elem new_element = { element, priority };

    // Find out where to put the element and put it
    for(index = count++; index; index = parent) {
        parent = (index - 1) >> 1;
        if (pq_data[parent] >= new_element) break;
        pq_data[index] = pq_data[parent];
    }
    pq_data[index] = new_element;
}

PQ_Type PriorityQueue::dequeue() {
    unsigned int index, swap, other;

    // Remove the biggest element
    PQ_Elem temp = pq_data[--count];

    // Reorder the elements
    for(index = 0; 1; index = swap) {
        // Find the child to swap with
        swap = (index << 1) + 1;
        if (swap >= count) break; // If there are no children, the heap is reordered
        other = swap + 1;
        if ((other < count) && (pq_data[other] >= pq_data[swap])) swap = other;
        if (temp >= pq_data[swap]) break; // If the bigger child is less than or equal to its parent, the heap is reordered

        pq_data[index] = pq_data[swap];
    }
    pq_data[index] = temp;

    return temp.value;
}

PQ_Type PriorityQueue::front() {
    return pq_data[0].value;
}

bool PriorityQueue::isEmpty() {
    return count == 0;
}
