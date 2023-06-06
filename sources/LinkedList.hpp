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
    void setIndex(int i);
    void setNext(Node<T>* next);
    bool operator>(const Node<T> &other) const;
    bool operator<(const Node<T> &other) const;
    //bool operator>(const Node<int*> &other) const;
    //bool operator<(const Node<int*> &other) const;
    void static insertAtPosition(Node<T>* toAdd, int position, Node<T>** head);
    void static removeAtPosition(int position, Node<T>** head);
    //int static findPosition(Node<int*>* head, int* newdata);//specialization
    int static findPosition(Node<T>* head, T newdata);
    T* getDataPoint() {return &data;}
    Node<T>* getNext(){return next;}
    int getIndex() {return index;}
    bool getIsFinal(){return final;}
    Node<T> static *getFinal(Node<T>* head);
};

template <typename T>
Node<T>::Node(){

}

template <typename T>
Node<T>::Node(T data){
    this->data = data;
}

template <typename T>
void Node<T>::setIndex(int i){
    this->index = i;
}

template <typename T>
void Node<T>::setNext(Node<T>* next){
    this->next = next;
}

template <typename T>
bool Node<T>::operator>(const Node<T> &other) const{
    return this->data > other.data;
}

template <typename T>
bool Node<T>::operator<(const Node<T> &other) const{
    return this->data < other.data;
}

template <>
bool Node<int*>::operator>(const Node<int*> &other) const;

template <>
bool Node<int*>::operator<(const Node<int*> &other) const;

template <typename T>
Node<T>* Node<T>::getFinal(Node<T>* head){
    if(head==nullptr) throw std::runtime_error("ERROR!3");
    Node<T>* currentNode = head;
    while (currentNode->final != true) {
        currentNode = currentNode->next;
    }
    return currentNode;
}


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

    while (currentNode->final != true && currentIndex < position - 1) {
        currentNode = currentNode->next;
        currentIndex++;
    }

    if (currentNode->final == true) {
        throw std::runtime_error("ERROR!");
        return;
    }

    toAdd->next = currentNode->next;
    currentNode->next = toAdd;
    Node<T>::incrementFromPos(*head, position+1);
}

template <typename T>
int Node<T>::findPosition(Node<T>* head, T newdata){
    if (head->final == true) {
        return 0;
    }

    Node<T>* currentNode = head;
    int position = 0;

    while (currentNode->final != true) {
        if (currentNode->data >= newdata) {
            break;
        }

        currentNode = currentNode->next;
        position++;
    }

    return position;
}

template <typename T>
void Node<T>::incrementFromPos(Node<T>* head, int position) {
    //__asm__("int3");
    Node<T>* currentNode = head;
    int idx = 0;
    while (currentNode->final != true) {
        if (idx<position) {
            idx++;
        }
        else{currentNode->index++;}
        currentNode = currentNode->next;
    }
}

template <typename T>
void Node<T>::decreaseFromPos(Node<T>* head, int position) {
    Node<T>* currentNode = head;
    int idx = 0;
    while (currentNode->final != true) {
        if (idx<position) {
            idx++;
        }
        else{currentNode->index--;}
        currentNode = currentNode->next;
    }
}

template <typename T>
void Node<T>::removeAtPosition(int position, Node<T>** head) {
    if (position < 0) {
        // Invalid position
        return;
    }

    if ((*head)->final == true) {
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

    while (currentNode->final != true && currentIndex < position - 1) {
        currentNode = currentNode->next;
        currentIndex++;
    }

    if (currentNode->final == true || currentNode->next->final == true) {
        // Invalid position
        throw std::runtime_error("element doesn't exists");
    }

    Node<T>* nodeToDelete = currentNode->next;
    currentNode->next = nodeToDelete->next;
    delete nodeToDelete;
    Node<T>::decreaseFromPos(currentNode->next, position + 1);
}

template <>
int Node<int*>::findPosition(Node<int*>* head, int* newdata);

#endif