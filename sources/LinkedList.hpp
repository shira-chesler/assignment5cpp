#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include<stdexcept>
#include<iostream>

template <typename T>
class Node{
    Node<T>* next;
    T data;
    int index = -1;
    bool final = false;

    void static incrementFromPos(Node<T>* head, int position);
    void static decreaseFromPos(Node<T>* head, int position);

    public:
    Node();
    Node(T data);
    void setIndex(int idx);
    void setNext(Node<T>* next);
    bool operator>(const Node<T> &other) const;
    bool operator<(const Node<T> &other) const;
    void static insertAtPosition(Node<T>* toAdd, int position, Node<T>** head);
    void static removeAtPosition(int position, Node<T>** head);
    int static findPosition(Node<T>* head, T newdata);
    T* getDataPoint() {return &data;}
    Node<T>* getNext(){return next;}
    int getIndex() {return index;}
    bool getIsFinal(){return final;}
};

//default constructor
template <typename T>
Node<T>::Node(){

}

//constructor
template <typename T>
Node<T>::Node(T data){
    this->data = data;
}

//index setter
template <typename T>
void Node<T>::setIndex(int idx){
    this->index = idx;
}

//next setter
template <typename T>
void Node<T>::setNext(Node<T>* next){ 
    this->next = next;
}

//operator > (comparing by index)
template <typename T>
bool Node<T>::operator>(const Node<T> &other) const{
    return this->index > other.index;
}

//operator > (comparing by index)
template <typename T>
bool Node<T>::operator<(const Node<T> &other) const{
    return this->index < other.index;
}

//function to insert a node at a given position
template <typename T>
void Node<T>::insertAtPosition(Node<T>* toAdd, int position, Node<T>** head) {
    if (position < 0) {
        // Invalid position
        return;
    }

    if (*head == nullptr) {
        // Empty list, update head pointer
        toAdd->next = nullptr;
        toAdd->index = 0;
        *head = toAdd;
        toAdd->final = true;
        return;
    }
    
    // toAdd->end = Node<T>::getFinal(*head);
    toAdd->index = position;
    if (position == 0) {
        // Insert at the beginning
        toAdd->next = *head;
        *head = toAdd;
        Node<T>::incrementFromPos(*head, 1);
        return;
    }

    Node<T>* currentNode = *head;
    int currentIndex = 0;

    while (!static_cast<bool>(currentNode->final) && currentIndex < position - 1) {
        currentNode = currentNode->next;
        currentIndex++;
    }

    if (static_cast<bool>(currentNode->final)) {
        throw std::runtime_error("ERROR!");
        return;
    }

    toAdd->next = currentNode->next;
    currentNode->next = toAdd;
    Node<T>::incrementFromPos(*head, position+1);
}

//finding a position to insert a certein element in ascending order
template <typename T>
int Node<T>::findPosition(Node<T>* head, T newdata){
    if (static_cast<bool>(head->final)) {
        return 0;
    }

    Node<T>* currentNode = head;
    int position = 0;

    while (!static_cast<bool>(currentNode->final)) {
        if (currentNode->data >= newdata) {
            break;
        }

        currentNode = currentNode->next;
        position++;
    }

    return position;
}

//increment indexes of all nodes from a certein position (include)
template <typename T>
void Node<T>::incrementFromPos(Node<T>* head, int position) {
    Node<T>* currentNode = head;
    int idx = 0;
    while (!static_cast<bool>(currentNode->final)) {
        if (idx<position) {
            idx++;
        }
        else{currentNode->index++;}
        currentNode = currentNode->next;
    }
}

//decreases indexes of all nodes from a certein position (include)
template <typename T>
void Node<T>::decreaseFromPos(Node<T>* head, int position) {
    Node<T>* currentNode = head;
    int idx = 0;
    while (!static_cast<bool>(currentNode->final)) {
        if (idx<position) {
            idx++;
        }
        else{currentNode->index--;}
        currentNode = currentNode->next;
    }
}

//function to delete a node at a given position
template <typename T>
void Node<T>::removeAtPosition(int position, Node<T>** head) {
    if (position < 0) {
        // Invalid position
        return;
    }

    if (static_cast<bool>((*head)->final)) {
        return;
    }

    if (position == 0) {
        // Remove the head node
        Node<T>* temp = *head;
        *head = (*head)->next;
        delete temp;
        Node<T>::decreaseFromPos(*head, 1);
        return;
    }

    Node<T>* currentNode = *head;
    int currentIndex = 0;

    while (!static_cast<bool>(currentNode->final) && currentIndex < position - 1) {
        currentNode = currentNode->next;
        currentIndex++;
    }

    if (static_cast<bool>(currentNode->final) || static_cast<bool>(currentNode->next->final)) {
        // Invalid position
        throw std::runtime_error("element doesn't exists");
    }

    Node<T>* nodeToDelete = currentNode->next;
    currentNode->next = nodeToDelete->next;
    delete nodeToDelete;
    Node<T>::decreaseFromPos(currentNode->next, position + 1);
}

//int* specialization decleration for finding a position to insert a certein element in ascending order
template <>
int Node<int*>::findPosition(Node<int*>* head, int* newdata);

#endif