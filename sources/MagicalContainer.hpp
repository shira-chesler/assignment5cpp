#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
#include <stdexcept>
#include "LinkedList.hpp"

namespace ariel {
    class MagicalContainer{
        private:
        Node<int> *ascending;
        Node<int> *asc_end;
        Node<int*> *descending;
        Node<int*> *desc_end;
        Node<int*> *prime;
        Node<int*> *prime_end;
        int num_elem;

        int findPositionToInsert(int elem);
        int exists(int elem);
        bool isPrime(int elem);

        public:
        MagicalContainer();
        MagicalContainer(const MagicalContainer& magic);
        MagicalContainer(MagicalContainer&& magic) noexcept;
        MagicalContainer& operator=(const MagicalContainer& magic);
        MagicalContainer& operator=(MagicalContainer&& magic) noexcept;
        ~MagicalContainer();
        void addElement(int elem);
        void removeElement(int elem);
        int size();


        class AscendingIterator;
        class PrimeIterator;
        class SideCrossIterator;
        
        class AscendingIterator{
            private:
                const MagicalContainer* cont;
                Node<int> *current;
                bool throwCompare() const;

            public:
            AscendingIterator();
            AscendingIterator(const MagicalContainer& magic);
            AscendingIterator(const AscendingIterator& asci);
            AscendingIterator(AscendingIterator&& asci) noexcept;
            ~AscendingIterator();

            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;

            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;

            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;

            AscendingIterator &operator=(const AscendingIterator &other);
            AscendingIterator &operator=(AscendingIterator &&other) noexcept;

            int operator*();
            
            AscendingIterator &operator++();

            AscendingIterator begin();
            AscendingIterator end();
        };

        class PrimeIterator{
            private:
                const MagicalContainer* cont;
                Node<int*> *current;
                bool throwCompare() const;

            public:
            PrimeIterator();
            PrimeIterator(const MagicalContainer& magic);
            PrimeIterator(const PrimeIterator& prmi);
            PrimeIterator(PrimeIterator&& prmi) noexcept;
            ~PrimeIterator();

            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;

            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;

            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;

            PrimeIterator &operator=(const PrimeIterator &other);
            PrimeIterator &operator=(PrimeIterator &&other) noexcept;

            int operator*();

            PrimeIterator &operator++();

            PrimeIterator begin();
            PrimeIterator end();
        };

        class SideCrossIterator{
            private:
                const MagicalContainer* cont;
                Node<int> *current_front;
                Node<int*> *current_back;
                bool is_front;

            public:
            SideCrossIterator();
            SideCrossIterator(const MagicalContainer& magic);
            SideCrossIterator(const SideCrossIterator& prmi);
            SideCrossIterator(SideCrossIterator&& prmi) noexcept;
            ~SideCrossIterator();

            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;

            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            
            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;

            SideCrossIterator &operator=(const SideCrossIterator &other);
            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept;

            int operator*();

            SideCrossIterator &operator++();

            SideCrossIterator begin();
            SideCrossIterator end();
        };
    };
}


#endif