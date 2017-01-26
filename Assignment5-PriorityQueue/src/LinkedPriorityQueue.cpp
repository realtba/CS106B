// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "LinkedPriorityQueue.h"

LinkedPriorityQueue::LinkedPriorityQueue() {
    this->start = NULL;

}

LinkedPriorityQueue::~LinkedPriorityQueue() {
    ListNode* current=this->start;

    while(current != NULL){
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    ListNode* element = this->start;

    while(element != NULL){
        if(element->value == value){
            element->priority = newPriority;
            return;
        }
        element= element->next;
    }
}

void LinkedPriorityQueue::clear() {

    ListNode* current=this->start;

    while(current != NULL){
        ListNode* next = current->next;
        delete current;
        current = next;
    }

    this->start = NULL;
}

string LinkedPriorityQueue::dequeue() {

    ListNode* newStart = this->start->next;
    string value = this->start->value;
    delete this->start;
    this->start = newStart;
    return value;
}

void LinkedPriorityQueue::enqueue(string value, int priority) {

    if(!this->start){
        this->start = new ListNode(value, priority, NULL);
        return;
    }

    ListNode* current = this->start;
    ListNode* prev = NULL;

    while(current !=NULL){
        if(current->priority > priority){
            ListNode *newNode = new ListNode(value, priority, current);

            if(prev){
                prev->next = newNode;
            }
            else{
                this->start = newNode;
            }
            return;
        }

        prev = current;
        current = current->next;
    }

    prev->next = new ListNode(value, priority, NULL);

}

bool LinkedPriorityQueue::isEmpty() const {

    return (this->start==NULL);
}

string LinkedPriorityQueue::peek() const {
    return this->start->value;
}

int LinkedPriorityQueue::peekPriority() const {
    return this->start->priority;
}

int LinkedPriorityQueue::size() const {
    ListNode* current = this->start;
    int size = 0;
    while(current){
        size++;
        current = current->next;
    }
    return size;   // remove this
}

ostream& operator<<(ostream& out, const LinkedPriorityQueue& queue) {
    out << "{" ;
    ListNode* current = queue.start;
    while(current){
        out << current->value;
        if(current->next){
            out << " ; ";
        }
        current = current->next;
    }
    out << "}";
    return out;
}
