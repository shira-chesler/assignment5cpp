#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>

namespace ariel {
    class MagicalContainer{
        private:
        std::vector<int> TheContainer;
        std::vector<int*> PrimeIterPoints;
        std::vector<int*> AscendingIterPoints;
        std::vector<int*> CrossIterPoints;

        int contains(int elem);
        bool isPrime(int elem);

        public:
        MagicalContainer();
        void addElement(int elem);
        void removeElement(int elem);
        int size();

        //int getAt(int index);
        //int* getAtPrime(int index);
        //int* getAtAscending(int index);
        //int* getAtCross(int index);


        //itertors
        class BaseIterator{ //the class needs to be pure
        private:
        MagicalContainer* cont;
        int position;

        public:
        BaseIterator();
        BaseIterator(MagicalContainer* cont, int pos);
        BaseIterator(const BaseIterator& bsi);
        ~BaseIterator();

        bool operator>(const BaseIterator &other) const;
        bool operator<(const BaseIterator &other) const;
        bool operator==(const BaseIterator &other) const;
        bool operator!=(const BaseIterator &other) const;

        int operator*();

        int* getLocationPtr();
        void setLocationPtr(int* newlocptr);
        int getPosition();
        void setPosition(int newloc);
    };

    class AscendingIterator : public BaseIterator{
        public:
        AscendingIterator();
        AscendingIterator(const MagicalContainer& magic);
        AscendingIterator(const AscendingIterator& asci);
        ~AscendingIterator();

        AscendingIterator &operator=(const AscendingIterator &other);
        AscendingIterator &operator++();

        AscendingIterator begin();
        AscendingIterator end();
    };

    class PrimeIterator : public BaseIterator{
        public:
        PrimeIterator();
        PrimeIterator(const MagicalContainer& magic);
        PrimeIterator(const PrimeIterator& asci);
        ~PrimeIterator();

        PrimeIterator &operator=(const PrimeIterator &other);
        PrimeIterator &operator++();

        PrimeIterator begin();
        PrimeIterator end();
    };

    class SideCrossIterator : public BaseIterator{
        public:
        SideCrossIterator();
        SideCrossIterator(const MagicalContainer& magic);
        SideCrossIterator(const SideCrossIterator& bsi);
        ~SideCrossIterator();

        SideCrossIterator &operator=(const SideCrossIterator &other);
        SideCrossIterator &operator++();

        SideCrossIterator begin();
        SideCrossIterator end();
    };
    };

}


#endif 