#include "MagicalContainer.hpp"

#include <stdexcept>
#include<iostream>

using namespace ariel;

//MAGIC CONTAINER CLASS

//if the container has the element - return -1,
//otherwise return the position it should be inserted into
int MagicalContainer::findPositionToInsert(int elem){
    if(exists(elem)>=0) return -1;
    return Node<int>::findPosition(this->ascending, elem);
}

//checks if the given element is prime
bool MagicalContainer::isPrime(int elem){
    if(elem <= 1) return false;
    for (int i = 2; i * i <= elem; i++) {
        if (elem % i == 0)
            return false;
    }
    return true;
}

//checks if the element exists in the container
int MagicalContainer::exists(int elem){
    int idx = 0;
    Node<int>* curr = this->ascending;
    while (curr->getIsFinal()!=true && *(curr->getDataPoint())!=elem)
    {
        idx++;
        curr = curr->getNext();
    }
    if(curr->getIsFinal()) return -1;
    return idx;
}

//constucror
MagicalContainer::MagicalContainer():ascending(nullptr), descending(nullptr), prime(nullptr), num_elem(0){
    //inserting end nodes to each list
    this->asc_end = new Node<int>();
    this->desc_end = new Node<int*>();
    this->prime_end = new Node<int*>();
    Node<int>::insertAtPosition(this->asc_end, 0, &(this->ascending));
    Node<int*>::insertAtPosition(this->desc_end, 0, &(this->descending));
    Node<int*>::insertAtPosition(this->prime_end, 0, &(this->prime));
}

//copy constructor
MagicalContainer::MagicalContainer(const MagicalContainer& magic)=default;

//move constructor
MagicalContainer::MagicalContainer(MagicalContainer&& magic) noexcept=default;

//assignment operator
MagicalContainer& MagicalContainer::operator=(const MagicalContainer& magic)=default;

//move assignment operator
MagicalContainer& MagicalContainer::operator=(MagicalContainer&& magic) noexcept=default;

//Destructor
MagicalContainer::~MagicalContainer(){
    Node<int>* current = this->ascending;
    while (!current->getIsFinal()) {
        Node<int>* next = current->getNext();
        delete current;
        current = next;
    }
    delete current;
    Node<int*>* curr = this->descending;
    while (!curr->getIsFinal()) {
        Node<int*>* next = curr->getNext();
        delete curr;
        curr = next;
    }
    delete curr;
    curr = this->prime;
    while (!curr->getIsFinal()) {
        Node<int*>* next = curr->getNext();
        delete curr;
        curr = next;
    }
    delete curr;
}

//adding an element to the container
void MagicalContainer::addElement(int elem){
    int position = findPositionToInsert(elem);
    if(position==-1) return;
    Node<int>* newintnode = new Node<int>(elem);
    Node<int*>* newintstnode = new Node<int*>(newintnode->getDataPoint());
    Node<int>::insertAtPosition(newintnode, position, &(this->ascending));
    Node<int*>::insertAtPosition(newintstnode, num_elem - position, &(this->descending));
    if(isPrime(elem)){
        newintstnode = new Node<int*>(newintnode->getDataPoint());
        Node<int*>::insertAtPosition(newintstnode, Node<int*>::findPosition(this->prime, newintnode->getDataPoint()) ,&(this->prime));
    }
    this->num_elem++;
}

//removing an element from the container
void MagicalContainer::removeElement(int elem){
    int elementposition = exists(elem); //if we would have to insert this elem
    if(elementposition == -1) throw std::runtime_error("element doesnt exist in container");
    Node<int>::removeAtPosition(elementposition, &(this->ascending));
    this->num_elem--;
    Node<int*>::removeAtPosition(num_elem - elementposition, &(this->descending));
    int primepos = Node<int*>::findPosition(this->prime, &elem);
    if(primepos!=-1) Node<int*>::removeAtPosition(primepos, &(this->prime));
}

//size of the magical container vector
int MagicalContainer::size(){
    return this->num_elem;
}



//AscendingIterator class
//default constructor
MagicalContainer::AscendingIterator::AscendingIterator(){
    this->cont = nullptr;
    this->current = nullptr;
}

//constructor
MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& magic){
    this->cont = &magic;
    this->current = magic.ascending;
}

//copy constructor
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& asci){
    this->cont = asci.cont;
    this->current = asci.cont->ascending;
}

//move constructor
MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator&& asci) noexcept{
    this->cont = asci.cont;
    this->current = asci.cont->ascending;
    asci.cont = nullptr;
    asci.current = nullptr;
}

//destructor
MagicalContainer::AscendingIterator::~AscendingIterator(){

}

//operator >
bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const{
    if(other.current->getIsFinal() == true && this->current->getIsFinal() == true ) return false; //both are at end
    if(other.current->getIsFinal() == true ) return false; // other at end
    if(this->current->getIsFinal()) return true; // this at end
    return *(this->current)>*(other.current);
}

//operator <
bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const{
    return other>(*this);
}

//operator ==
bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const{
    return !((*this)>other || (*this)<other);
}

//operator !=
bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const{
    return !((*this)==other);
}

//This section was meant in order to be allow comparing iterators of different type and throwing an exception
bool MagicalContainer::AscendingIterator::throwCompare() const {throw std::runtime_error("can't compare 2 iterators with different types"); return false;}
bool MagicalContainer::AscendingIterator::operator>(const PrimeIterator &other) const {return throwCompare();}
bool MagicalContainer::AscendingIterator::operator<(const PrimeIterator &other) const {return throwCompare();}
bool MagicalContainer::AscendingIterator::operator==(const PrimeIterator &other) const {return throwCompare();}
bool MagicalContainer::AscendingIterator::operator!=(const PrimeIterator &other) const {return throwCompare();}
bool MagicalContainer::AscendingIterator::operator>(const SideCrossIterator &other) const {return throwCompare();}
bool MagicalContainer::AscendingIterator::operator<(const SideCrossIterator &other) const {return throwCompare();}
bool MagicalContainer::AscendingIterator::operator==(const SideCrossIterator &other) const {return throwCompare();}
bool MagicalContainer::AscendingIterator::operator!=(const SideCrossIterator &other) const {return throwCompare();}

//assignment operator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other){
    if(this->cont != other.cont) throw std::runtime_error("can't assign between two different containers");
    this->cont = other.cont;
    this->current = other.current;
    return (*this);
}

//move assignment operator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept{
    this->cont = other.cont;
    this->current = other.current;
    other.cont = nullptr;
    other.current = nullptr;
    return (*this);
}

//operator *
int MagicalContainer::AscendingIterator::operator*(){
    if(this->current->getIsFinal() == true) throw std::runtime_error("out of range iterator");
    return *(this->current->getDataPoint());
}

//++ operator
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
    if(this->current->getIsFinal() == true) throw std::runtime_error("out of range");
    this->current = this->current->getNext();
    return (*this);
}

//iterator to the beginning of the container
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin(){
    MagicalContainer::AscendingIterator asci(*(this->cont));
    return asci;
}

//iterator to the end of the container
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end(){
    MagicalContainer::AscendingIterator asci(*(this->cont));
    asci.current = this->cont->asc_end;
    return asci;
}



//PrimeIterator class
//default constructor
MagicalContainer::PrimeIterator::PrimeIterator(){
    this->cont = nullptr;
    this->current = nullptr;
}

//constructor
MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& magic){
    this->cont = &magic;
    this->current = magic.prime;
}

//copy constructor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& prmi){
    this->cont = prmi.cont;
    this->current = prmi.current;
}

//move constructor
MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator&& prmi) noexcept{
    this->cont = prmi.cont;
    this->current = prmi.cont->prime;
    prmi.cont = nullptr;
    prmi.current = nullptr;
}

//destructor
MagicalContainer::PrimeIterator::~PrimeIterator(){

}

//operator >
bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const{
    if(other.current->getIsFinal() == true && this->current->getIsFinal() == true ) return false; //this and other are at end
    if(other.current->getIsFinal() == true ) return false; //other at end
    if(this->current->getIsFinal()) return true; //this at end
    return *(this->current)>*(other.current);
}

//operator <
bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const{
    return other>(*this);
}

//operator ==
bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const{
    return !((*this)>other || (*this)<other);
}

//operator !=
bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const{
    return !((*this)==other);
}

//This section was meant in order to be allow comparing iterators of different type and throwing an exception
bool MagicalContainer::PrimeIterator::throwCompare() const {throw std::runtime_error("can't compare 2 iterators with different types"); return false;}
bool MagicalContainer::PrimeIterator::operator>(const AscendingIterator &other) const {return other<(*this);}
bool MagicalContainer::PrimeIterator::operator<(const AscendingIterator &other) const {return other>(*this);}
bool MagicalContainer::PrimeIterator::operator==(const AscendingIterator &other) const {return other==(*this);}
bool MagicalContainer::PrimeIterator::operator!=(const AscendingIterator &other) const {return other!=(*this);}
bool MagicalContainer::PrimeIterator::operator>(const SideCrossIterator &other) const {return throwCompare();}
bool MagicalContainer::PrimeIterator::operator<(const SideCrossIterator &other) const {return throwCompare();}
bool MagicalContainer::PrimeIterator::operator==(const SideCrossIterator &other) const {return throwCompare();}
bool MagicalContainer::PrimeIterator::operator!=(const SideCrossIterator &other) const {return throwCompare();}

//assignment operator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other){
    if(this->cont != other.cont) throw std::runtime_error("can't assign between two different containers");
    this->cont = other.cont;
    this->current = other.current;
    return (*this);
}

//move assignment operator 
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept{
    this->cont = other.cont;
    this->current = other.current;
    other.cont = nullptr;
    other.current = nullptr;
    return (*this);
}

//operator *
int MagicalContainer::PrimeIterator::operator*(){
    if(this->current->getIsFinal()) throw std::runtime_error("out of range iterator");
    return **(this->current->getDataPoint());
}

//++ operator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
    if(this->current->getIsFinal()) throw std::runtime_error("out of range");
    this->current = this->current->getNext();
    return (*this);
}

//iterator to the beginning of the container
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin(){
    MagicalContainer::PrimeIterator prmi(*(this->cont));
    return prmi;
}

//iterator to the end of the container
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end(){
    MagicalContainer::PrimeIterator prmi(*(this->cont));
    prmi.current = this->cont->prime_end;
    return prmi;
}



//SideCross class - 
//this class is implemented with two pointers - one to the "beginning of the container" and the other one to the
// "end of the container" (represented by an ascending and descending liked lists) which are flipped by the boolean is_front.

//default constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(){
    this->cont = nullptr;
    this->current_front = nullptr;
    this->current_back = nullptr;
    this->is_front = true;
}

//constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& magic){
    this->cont = &magic;
    this->current_front = cont->ascending;
    this->current_back = cont->descending;
    this->is_front = true;
}

//copy constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& sdci){
    this->cont = sdci.cont;
    this->current_front = sdci.current_front;
    this->current_back = sdci.current_back;
    this->is_front = sdci.is_front;
}

//move constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& sdci) noexcept{
    this->cont = sdci.cont;
    this->current_front = sdci.current_front;
    this->current_back = sdci.current_back;
    this->is_front = sdci.is_front;
    sdci.cont = nullptr;
    sdci.current_front = nullptr;
    sdci.current_back = nullptr;
}

//destructor
MagicalContainer::SideCrossIterator::~SideCrossIterator(){

}

//operator >
bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const{
    if((other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) && (this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true)) return false; // both this and other at end
    if(other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) return false; // other at end
    if(this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true) return true; // this at end
    if(this->is_front && other.is_front){ // both at front
        if(this->current_front->getIndex() == 0) return other.current_front->getIndex()==0 ? false : true; // special case where this at index 0
        return this->current_front->getIndex() > other.current_front->getIndex(); // compute by index
    } else if (this->is_front && (!other.is_front)){ // this at front (went through odd num of elments) other at back (went through even num of elments)
        if(this->current_front->getIndex()==0) return other.current_back->getIndex()==0 ? false : true; // special case where this at index 0
        return ((2*this->current_front->getIndex())+1) > (2*other.current_back->getIndex()); // compute by index
    } else if ((!this->is_front) && other.is_front){ // this at end (went through even num of elments) other at front (went through odd num of elments)
        if(this->current_back->getIndex() == 0) return other.current_front->getIndex()==0 ? true : false; // special case where this at index 0
        return (2*this->current_back->getIndex()) > ((2*other.current_front->getIndex())+1); // compute by index
    } else{ // both at end
        if(this->current_back->getIndex() == 0) return other.current_back->getIndex()==0 ? false : true; // special case where this at index 0
        return this->current_back->getIndex() > other.current_back->getIndex(); // compute by index
    }
}

//operator <
bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const{
    return other>(*this);
}

//operator ==
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const{
    return !((*this)>other || (*this)<other);
}

//operator !=
bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const{
    return !((*this)==other);
}

//This section was meant in order to be allow comparing iterators of different type and throwing an exception
bool MagicalContainer::SideCrossIterator::operator>(const AscendingIterator &other) const {return other<(*this);}
bool MagicalContainer::SideCrossIterator::operator<(const AscendingIterator &other) const {return other>(*this);}
bool MagicalContainer::SideCrossIterator::operator==(const AscendingIterator &other) const {return other==(*this);}
bool MagicalContainer::SideCrossIterator::operator!=(const AscendingIterator &other) const {return other!=(*this);}
bool MagicalContainer::SideCrossIterator::operator>(const PrimeIterator &other) const {return other<(*this);}
bool MagicalContainer::SideCrossIterator::operator<(const PrimeIterator &other) const {return other>(*this);}
bool MagicalContainer::SideCrossIterator::operator==(const PrimeIterator &other) const {return other==(*this);}
bool MagicalContainer::SideCrossIterator::operator!=(const PrimeIterator &other) const {return other!=(*this);}

//assignment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other){
    if(this->cont != other.cont) throw std::runtime_error("can't assign between two different containers");
    this->cont = other.cont;
    this->current_front = other.current_front;
    this->current_back = other.current_back;
    this->is_front = other.is_front;
    return (*this);
}

//move assignment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept{
    this->cont = other.cont;
    this->current_front = other.current_front;
    this->current_back = other.current_back;
    this->is_front = other.is_front;
    other.cont = nullptr;
    other.current_front = nullptr;
    other.current_back = nullptr;
    return (*this);
}

//operator *
int MagicalContainer::SideCrossIterator::operator*(){
    if(this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true) throw std::runtime_error("out of range iterator");
    if(this->is_front) {return *current_front->getDataPoint();}
    return *(*(current_back->getDataPoint()));
}

//++ operator
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
    if(this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true) throw std::runtime_error("out of range");
    if(this->current_back->getIndex() + this->current_front->getIndex() >= this->cont->num_elem-1){ // covered all elements
        this->current_back = this->cont->desc_end; // get both back
        this->current_front = this->cont->asc_end; // and front to be end
        return (*this);
    }
    if(this->is_front) {
        this->current_front = current_front->getNext();
        this->is_front = false;
    }
    else{
        this->current_back = current_back->getNext();
        this->is_front = true;
    }
    return (*this);
}

//iterator to the beginning of the container
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin(){
    MagicalContainer::SideCrossIterator sdci(*(this->cont));
    return sdci;
}

//iterator to the end of the container
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end(){
    MagicalContainer::SideCrossIterator sdci(*(this->cont));
    sdci.current_front = this->cont->asc_end;
    sdci.current_back = this->cont->desc_end;
    return sdci;
}