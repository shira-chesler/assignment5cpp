#include "LinkedList.hpp"

template <>
int Node<int*>::findPosition(Node<int*>* head, int* newdata){
    if (head->final == true) {
        return 0;
    }

    Node<int*>* currentNode = head;
    int position = 0;

    while (currentNode->final != true) {
        if (*(currentNode->data) >= *newdata) {
            // Found the position where data is greater or equal
            return position;
        }

        currentNode = currentNode->next;
        position++;
    }

    // If the position is not found, you can return an appropriate error code or value
    return -1;  // or any other appropriate error code
}

template <>
bool Node<int*>::operator>(const Node<int*> &other) const{
    return this->index>other.index;
}

template <>
bool Node<int*>::operator<(const Node<int*> &other) const{
    return this->index<other.index;
}