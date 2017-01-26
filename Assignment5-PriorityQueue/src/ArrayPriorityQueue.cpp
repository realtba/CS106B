// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "ArrayPriorityQueue.h"

ArrayPriorityQueue::ArrayPriorityQueue() {

    this->queueSize = 0;
    this->queueCapacity = DEFAULT_CAPACITY;
    this->queue = new PQEntry[DEFAULT_CAPACITY];
}

ArrayPriorityQueue::~ArrayPriorityQueue() {
   delete [] this->queue;
}

void ArrayPriorityQueue::changePriority(string value, int newPriority) {

    for(int i=0; i< this->queueSize; i++){
        if(this->queue[i].value == value){
            this->queue[i].priority = newPriority;
        }
    }
}


void ArrayPriorityQueue::clear() {
    delete[] this->queue;
    this->queue = new PQEntry[DEFAULT_CAPACITY];
    this->queueCapacity = DEFAULT_CAPACITY;
    this->queueSize = 0;
}

int ArrayPriorityQueue::getHighestPriorityIndex() const{

        int highestPriority = this->queue[0].priority;
        int element = 0;

        for(int i=0; i< this->queueSize; i++){
                int prio = this->queue[i].priority;
                if(prio > highestPriority){
                    element = i;
                    highestPriority = prio;
                }
        }
        return element;
}

string ArrayPriorityQueue::dequeue() {

    int element = this->getHighestPriorityIndex();
    string value = this->queue[element].value;

    for(int i = element; i < this->queueSize-1; i++ ){
        this->queue[i] = this->queue[i+1];
    }

    this->queueSize--;

    return value;
}

void ArrayPriorityQueue::enqueue(string value, int priority) {

    if(this->queueSize == this->queueCapacity){

        PQEntry* dummy = new PQEntry[this->queueCapacity + DEFAULT_CAPACITY];

        for(int i = 0; i < this->queueSize; i++){
            dummy[i] = this->queue[i];
        }

        delete[] this->queue;
        this->queue = dummy;
        this->queueCapacity += DEFAULT_CAPACITY;
    }

    this->queue[this->queueSize].priority = priority;
    this->queue[this->queueSize].value = value;
    this->queueSize++;

}

bool ArrayPriorityQueue::isEmpty() const {
    return (this->size()==0);
}

string ArrayPriorityQueue::peek() const {

    return queue[this->getHighestPriorityIndex()].value;
}

int ArrayPriorityQueue::peekPriority() const {

    return queue[this->getHighestPriorityIndex()].priority;
}

int ArrayPriorityQueue::size() const {

    return this->queueSize;   // remove this
}

ostream& operator<<(ostream& out, const ArrayPriorityQueue& queue) {
    out << "{";
    for(int i=0; i < queue.size();i++){
        out << queue.queue[i] << ",";
    }
    out << "}";
    return out;
}
