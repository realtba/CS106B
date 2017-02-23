// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "HeapPriorityQueue.h"
#include "error.h"
#include <tgmath.h>

HeapPriorityQueue::HeapPriorityQueue() {
    this->queueSize = 0;
    this->queueCapacity = DEFAULT_CAPACITY_HPQ ;
    this->queue = new PQEntry[DEFAULT_CAPACITY_HPQ];
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete this->queue;
}

void HeapPriorityQueue::changePriority(string value, int newPriority) {

    int element=0;

    for(int i=1; i <= this->queueSize; i++){
       if(this->queue[i].value == value){
           element = i;
       }
    }
    if(element==0){
        cout << "Could not find an element in the heap with value: " + value;
        return;
    }
    this->queue[element].priority = newPriority;

    if(this->queue[element].priority < this->queue[element/2].priority){
        this->bubbleUp(element);
    }
    else if( this->queue[element].priority > this->queue[2*element].priority
             || this->queue[element].priority > this->queue[2*element +1].priority){
        this->bubbleDown(element);
    }


}

void HeapPriorityQueue::clear() {
    delete[] this->queue;
    this->queueSize = 0;
    this->queueCapacity = DEFAULT_CAPACITY_HPQ;
    this->queue = new PQEntry[DEFAULT_CAPACITY_HPQ];
}

void HeapPriorityQueue::bubbleUp(int element){
    int i = element;
    // bubble up
    while(i > 0){
        // parent index
        //int parent = floor(((float)i)/2);
        int parent =i/2;
        // check if we need to switch
        if(this->queue[i].priority <= this->queue[parent].priority){
            swap(i,parent);
            i = parent;
            continue;
        }
        else{
            break;
        }
    }
}
void HeapPriorityQueue::bubbleDown(int element){
    int i = element;
    while(i <= this->queueSize ){
        // there is a right child
        if(2*i+1 <= this->queueSize){
            //if left child is smaller and left child is smaller then right child
            // swap and continue
            if( this->queue[i] >= this->queue[2*i]
                &&  this->queue[2*i] <=  this->queue[2*i+1] ){
                this->swap(i,2*i);
                i = 2*i;
                continue;
            }
            // if right child is smaller and left child is smaller then left child
            // swap and continue
            // (Note: the second conditin is unnecassary, we keep it for symmetry)
            else if( this->queue[i] >=this->queue[2*i+1]
                     && this->queue[2*i+1] <= this->queue[2*i]){
                this->swap(i,2*i+1);
                i = 2*i+1;
                continue;
            }
            // both childs are bigger, we are done
            else{
                break;
            }
        }

        // there is only a left child i.e we are at the end of the tree
        else if(2*i == this->queueSize){

            // if the left child is smaller we need to switch
            if( this->queue[i] >= this->queue[2*i] ){
                this->swap(i,2*i);
            }
            break;
        }

        // there is no left and no right child -> we can stop the loop
        else{
            break;
        }
    }
}

string HeapPriorityQueue::dequeue() {

    if(this->isEmpty()){
        error("ERROR: Called dequeue on empty Queue");
        return "";
    }

    string result = this->queue[1].value;

    swap(1, this->queueSize);
    this->queueSize -=1;

    // bubble down
    bubbleDown(1);

    return result;
}

void HeapPriorityQueue::enqueue(string value, int priority) {

    // Check if we need to resize the array (queueSize+1 since queue[0] is left blank)
    if(this->queueSize+1 == this->queueCapacity){

        PQEntry* newQueue = new PQEntry[this->queueCapacity+DEFAULT_CAPACITY_HPQ];
        this->queueCapacity += DEFAULT_CAPACITY_HPQ;

        for(int i =1; i< this->queueSize+1; i++){
            newQueue[i] = this->queue[i];
        }

        delete[] this->queue;
        this->queue = newQueue;
    }

    // add the new element at the end of the heap and increase the length
    this->queue[queueSize+1].priority = priority;
    this->queue[queueSize+1].value = value;

    this->queueSize +=1;

   // bubble up
    this->bubbleUp(this->queueSize);
}

bool HeapPriorityQueue::isEmpty() const {
    // TODO: implement
    return false;   // remove this
}

string HeapPriorityQueue::peek() const {
    return this->queue[1].value;
}

int HeapPriorityQueue::peekPriority() const {
    return this->queue[1].priority;   // remove this
}

int HeapPriorityQueue::size() const {
    // TODO: implement
    return 0;   // remove this
}

void HeapPriorityQueue::swap(int i, int j){

    if(i < i || i> this->queueSize || j < 1 || j> this->queueSize ){
        error("ERROR: swap index out of range");
    }

    PQEntry dummy = this->queue[i];
    this->queue[i] = this->queue[j];
    this->queue[j] = dummy;
}

ostream& operator<<(ostream& out, const HeapPriorityQueue& queue) {
    out << "{";
    for(int i=1; i < queue.queueSize;i++){
        out << queue.queue[i] << ",";
    }
    out << "}";
    return out;
}
