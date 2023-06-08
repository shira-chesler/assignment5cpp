#include "LinkedList.hpp"

//int* specialization decleration for finding a position to insert a certein element in ascending order
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
    return position;  // or any other appropriate error code
}