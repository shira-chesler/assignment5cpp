#include "MagicalContainer.hpp"

using namespace ariel;

//MAGIC CONTAINER CLASS
int MagicalContainer::contains(int elem){
    return 0;
}
bool MagicalContainer::isPrime(int elem){
    return false;
}

MagicalContainer::MagicalContainer(){

}
void MagicalContainer::addElement(int elem){

}
void MagicalContainer::removeElement(int elem){

}
int MagicalContainer::size(){
    return 0;
}

// int MagicalContainer::getAt(int index){
//     return 0;
// }
// int* MagicalContainer::getAtPrime(int index){
//     return nullptr;
// }
// int* MagicalContainer::getAtAscending(int index){
//     return nullptr;
// }


//BASE ITERATOR CLASS        
MagicalContainer::BaseIterator::BaseIterator(){

}
MagicalContainer::BaseIterator::BaseIterator(MagicalContainer* cont, int pos){

}
MagicalContainer::BaseIterator::BaseIterator(const BaseIterator& bsi){

}
MagicalContainer::BaseIterator::~BaseIterator(){

}

bool MagicalContainer::BaseIterator::operator>(const BaseIterator &other) const{
    return false;
}
bool MagicalContainer::BaseIterator::operator<(const BaseIterator &other) const{
    return false;
}
bool MagicalContainer::BaseIterator::operator==(const BaseIterator &other) const{
    return false;
}
bool MagicalContainer::BaseIterator::operator!=(const BaseIterator &other) const{
    return false;
}

int MagicalContainer::BaseIterator::operator*(){
    return 0;
}

int* MagicalContainer::BaseIterator::getLocationPtr(){
    return nullptr;
}
void MagicalContainer::BaseIterator::setLocationPtr(int* newlocptr){

}
int MagicalContainer::BaseIterator::getPosition(){
    return 0;
}
void MagicalContainer::BaseIterator::setPosition(int newloc){

}


//AscendingIterator class
MagicalContainer::AscendingIterator::AscendingIterator(){

}
MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& magic){

}
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& asci){

}
MagicalContainer::AscendingIterator::~AscendingIterator(){

}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other){
    return (*this);
}
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
    return (*this);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin(){
    return (*this);
}
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end(){
    return (*this);
}


//PrimeIterator class
MagicalContainer::PrimeIterator::PrimeIterator(){

}
MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& magic){

}
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& asci){

}
MagicalContainer::PrimeIterator::~PrimeIterator(){

}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other){
    return (*this);
}
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++(){
    return (*this);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin(){
    return (*this);
}
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end(){
    return (*this);
}


//SideCrossIterator class
MagicalContainer::SideCrossIterator::SideCrossIterator(){

}
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& magic){

}
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& bsi){

}
MagicalContainer::SideCrossIterator::~SideCrossIterator(){

}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other){
    return (*this);
}
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++(){
    return (*this);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin(){
    return (*this);
}
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end(){
    return (*this);
}
