#include "sources/MagicalContainer.hpp"

using namespace ariel;
int main(){
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);
    container.addElement(6);
    // //container.printDescIdx();
    // MagicalContainer::PrimeIterator it(container);
    // std::cout << *it << std::endl;
    // ++it;
    // std::cout << *it << std::endl;
    // ++it;
    // std::cout << *it << std::endl;
    // ++it;

    MagicalContainer::SideCrossIterator itStart1(container);
    MagicalContainer::SideCrossIterator itStart2(container);

    ++itStart1;
    std::cout << (itStart1 < itStart2) << std::endl;
    std::cout << (itStart1 > itStart2) << std::endl;
}