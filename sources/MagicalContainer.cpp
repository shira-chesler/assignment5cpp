#include "MagicalContainer.hpp"

#include <stdexcept>
#include<iostream>

using namespace ariel;

void MagicalContainer::printDescIdx(){
    Node<int*> *curr = this->prime;
    while(curr->getIsFinal() == false){
        std::cout << curr->getIndex() << std::endl;
        curr = curr->getNext();
    }
    
}

//MAGIC CONTAINER CLASS

//if the main container has the element - return its psoition
//otherwise -1
int MagicalContainer::contains(int elem){
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

//constucror
MagicalContainer::MagicalContainer():ascending(nullptr), descending(nullptr), prime(nullptr), num_elem(0){
    Node<int>::insertAtPosition(new Node<int>(), 0, &(this->ascending));
    Node<int*>::insertAtPosition(new Node<int*>(), 0, &(this->descending));
    Node<int*>::insertAtPosition(new Node<int*>(), 0, &(this->prime));
}

//Destructor
MagicalContainer::~MagicalContainer(){

}

//adding an element to the container
void MagicalContainer::addElement(int elem){
    int position = contains(elem);
    if(position==-1) return;
    //__asm__("int3");
    Node<int>* newintnode = new Node<int>(elem);
    Node<int*>* newintstnode = new Node<int*>(newintnode->getDataPoint());
    Node<int>::insertAtPosition(newintnode, position, &(this->ascending));
    Node<int*>::insertAtPosition(newintstnode, num_elem - position, &(this->descending));
    if(isPrime(elem)){
        newintstnode = new Node<int*>(newintnode->getDataPoint());
        //std::cout << Node<int*>::findPosition(this->prime, newintnode->getDataPoint()) <<std::endl;
        Node<int*>::insertAtPosition(newintstnode, Node<int*>::findPosition(this->prime, newintnode->getDataPoint()) ,&(this->prime));
    }
    this->num_elem++;
}

//removing an element from the container
void MagicalContainer::removeElement(int elem){
    int elementposition = contains(elem);
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
    this->type = 1;
}

//constructor
MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& magic){
    this->cont = &magic;
    this->current = magic.ascending;
    this->type = 1;
}

//copy constructor
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& asci){
    this->cont = asci.cont;
    this->current = asci.cont->ascending;
    this->type = 1;
}

//move constructor
MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator&& asci) noexcept{
    this->cont = asci.cont;
    this->current = asci.cont->ascending;
    this->type = asci.type;
    asci.cont = nullptr;
    asci.current = nullptr;
}

//destructor
MagicalContainer::AscendingIterator::~AscendingIterator(){

}

//operator >
bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const{
    return this->current>other.current;
}

//operator <
bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const{
    return this->current<other.current;
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
    this->type = other.type;
    return (*this);
}

//move assignment operator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept{
    this->cont = other.cont;
    this->current = other.current;
    this->type = other.type;
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
    asci.current = Node<int>::getFinal(this->cont->ascending);
    return asci;
}



//PrimeIterator class
//default constructor
MagicalContainer::PrimeIterator::PrimeIterator(){
    this->cont = nullptr;
    this->current = nullptr;
    this->type = 2;
}

//constructor
MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& magic){
    this->cont = &magic;
    this->current = magic.prime;
    this->type = 2;
}

//copy constructor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& prmi){
    this->cont = prmi.cont;
    this->current = prmi.current;
    this->type = 2;
}

//move constructor
MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator&& prmi) noexcept{
    this->cont = prmi.cont;
    this->current = prmi.cont->prime;
    this->type = prmi.type;
    prmi.cont = nullptr;
    prmi.current = nullptr;
}

//destructor
MagicalContainer::PrimeIterator::~PrimeIterator(){

}

//operator >
bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const{
    return this->current>other.current;
}

//operator <
bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const{
    return this->current<other.current;
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
    this->type = other.type;
    return (*this);
}

//move assignment operator 
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept{
    this->cont = other.cont;
    this->current = other.current;
    this->type = other.type;
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
    prmi.current = Node<int*>::getFinal(this->cont->prime);
    return prmi;
}



//SideCross class
//default constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(){
    this->cont = nullptr;
    this->current_front = nullptr;
    this->current_back = nullptr;
    this->is_front = true;
    this->type = 3;
}

//constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& magic){
    this->cont = &magic;
    this->current_front = cont->ascending;
    this->current_back = cont->descending;
    this->is_front = true;
    this->type = 3;
}

//copy constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& sdci){
    this->cont = sdci.cont;
    this->current_front = sdci.current_front;
    this->current_back = sdci.current_back;
    this->is_front = sdci.is_front;
    this->type = 3;
}

//move constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& sdci) noexcept{
    this->cont = sdci.cont;
    this->current_front = sdci.current_front;
    this->current_back = sdci.current_back;
    this->is_front = sdci.is_front;
    this->type = 3;
    sdci.cont = nullptr;
    sdci.current_front = nullptr;
    sdci.current_back = nullptr;
}

//destructor
MagicalContainer::SideCrossIterator::~SideCrossIterator(){

}

//operator >
bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const{
    if((other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) && (this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true)) return false;
    if(other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) return false;
    if(this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true) return true;
    if(this->is_front && other.is_front){
        return ((2*this->current_front->getIndex())+1) > ((2*other.current_front->getIndex())+1);
    } else if (this->is_front && (!other.is_front)){
        return ((2*this->current_front->getIndex())+1) > (2*other.current_back->getIndex());
    } else if ((!this->is_front) && other.is_front){
        return (2*this->current_back->getIndex()) > ((2*other.current_front->getIndex())+1);
    } else{
        return (2*this->current_back->getIndex()) > (2*other.current_back->getIndex());
    }
}

//operator <
bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const{
    if((other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) && (this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true)) return false;
    if(other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) return true;
    if(this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true) return false;
    if(this->is_front && other.is_front){
        return ((2*this->current_front->getIndex())+1) < ((2*other.current_front->getIndex())+1);
    } else if (this->is_front && (!other.is_front)){
        return ((2*this->current_front->getIndex())+1) < (2*other.current_back->getIndex());
    } else if ((!this->is_front) && other.is_front){
        return (2*this->current_back->getIndex()) < ((2*other.current_front->getIndex())+1);
    } else{
        return (2*this->current_back->getIndex()) < (2*other.current_back->getIndex());
    }
}

//operator ==
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const{
    if((other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) && (this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true)) return true;
    if(other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) return false;
    if(this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true) return false;
    return !((*this)>other || (*this)<other);
}

//operator !=
bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const{
    if((other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) && (this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true)) return false;
    if(other.current_back->getIsFinal() == true || other.current_front->getIsFinal() == true) return true;
    if(this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true) return true;
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
    this->type = 3;
    return (*this);
}

//move assignment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept{
    this->cont = other.cont;
    this->current_front = other.current_front;
    this->current_back = other.current_back;
    this->is_front = other.is_front;
    this->type = other.type;
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
    // (this->cont->num_elem%2 == 1) &&
    // std::cout << this->current_front->getIndex() << "   " <<this->current_back->getIndex() << std::endl;
    if(this->current_back->getIsFinal() == true || this->current_front->getIsFinal() == true) throw std::runtime_error("out of range");
    if(this->current_back->getIndex() + this->current_front->getIndex() >= this->cont->num_elem-1){
        this->current_back = Node<int*>::getFinal(this->cont->descending); 
        this->current_front = Node<int>::getFinal(this->cont->ascending);
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
    //if((this->cont->num_elem%2==1 && this->current_back->getIndex()==(this->cont->num_elem/2)) && ((this->current_front->getIndex()==this->cont->num_elem/2)+1)){
    // if(this->current_back->getIndex() + this->current_front->getIndex() >= this->cont->num_elem){
    //     this->current_back = Node<int*>::getFinal(this->cont->descending); 
    //     this->current_front = Node<int>::getFinal(this->cont->ascending);
    // }
    // std::cout << this->current_front->getIndex() << "   " <<this->current_back->getIndex() << std::endl;
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
    sdci.current_front = Node<int>::getFinal(this->cont->ascending);
    sdci.current_back = Node<int*>::getFinal(this->cont->descending);
    return sdci;
}