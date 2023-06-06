#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
#include <stdexcept>
#include "LinkedList.hpp"

namespace ariel {
    class MagicalContainer{
        private:
        Node<int> *ascending;
        Node<int*> *descending;
        Node<int*> *prime;
        int num_elem;

        int contains(int elem);
        //int contains(std::vector<int*> const &vec, int* point);
        bool isPrime(int elem);

        public:
        MagicalContainer();
        MagicalContainer(const MagicalContainer& magic);
        MagicalContainer(MagicalContainer&& magic);
        MagicalContainer& operator=(const MagicalContainer& magic);
        MagicalContainer& operator=(MagicalContainer&& magic);
        ~MagicalContainer();
        void addElement(int elem);
        void removeElement(int elem);
        int size();
        //void printDescIdx();


        //itertors
        // template <typename T, typename NodeType>
        // class BaseIterator{
        //     private:
            // const MagicalContainer* cont;
            // int type;
            // Node<NodeType> *current;

        //     public:
        //     bool operator>(const BaseIterator<T, NodeType> &other) const{
        //         if (this->type != other.getType()) throw std::runtime_error("iterators to different conteiners cannot be comparised");
        //         return ((*current) > (*other.getCurr()));
        //     }
        //     bool operator<(const BaseIterator<T, NodeType> &other) const{
        //         if (this->type != other.getType()) throw std::runtime_error("iterators to different conteiners cannot be comparised");
        //         return ((*current) < (*other.getCurr()));
        //     }
        //     bool operator==(const BaseIterator<T, NodeType> &other) const{
        //         if (this->type != other.getType()) throw std::runtime_error("iterators to different conteiners cannot be comparised");
        //         return (!((*this)>other) && !((*this)<other));
        //     }
        //     bool operator!=(const BaseIterator<T, NodeType> &other) {
        //         if (this->type != other.getType()) throw std::runtime_error("iterators to different conteiners cannot be comparised");
        //         return !((*this)==other);
        //     }

        //     T &operator=(const T &other){
        //         this->cont = other.cont;
        //         this->type = other.type;
        //         this->current = other.current;
        //     }

        //     T &operator=(const T &&other) noexcept{
        //         this->cont = other.cont;
        //         this->current = other.current;
        //         other.setCont(nullptr);
        //         other.setCurr(nullptr);
        //     }

        //     virtual int operator*()=0;

        //     Node<NodeType>* getCurr() const {return this->current};

        //     const MagicalContainer* getCont()const {return cont;}

        //     void setCont(const MagicalContainer* magic){this->cont = magic;}

        //     void setCurr(Node<NodeType>* setto){this->current = setto;}

        //     int getType() const{return this->type;}

        //     //void SetPos(int pos){this->position = pos;}

        // };
        class AscendingIterator;
        class PrimeIterator;
        class SideCrossIterator;
        
        class AscendingIterator{
            private:
                const MagicalContainer* cont;
                int type;
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
                int type;
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
                int type;
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