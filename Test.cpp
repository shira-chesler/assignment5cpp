#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace ariel;

TEST_CASE("Initialization of MagicalContainer") {
    MagicalContainer mc;
    CHECK(mc.size() == 0);
}

TEST_CASE("Add and remove elements from MagicalContainer (+removing an existing elment doesnt throws)") {
    MagicalContainer mc;
    mc.addElement(5);
    CHECK(mc.size() == 1);

    mc.addElement(8);
    CHECK(mc.size() == 2);

    mc.addElement(27);
    CHECK(mc.size() == 3);

    CHECK_NOTHROW(mc.removeElement(5));
    CHECK(mc.size() == 2);

    CHECK_NOTHROW(mc.removeElement(27));
    CHECK(mc.size() == 1);

    mc.addElement(9);
    CHECK(mc.size() == 2);

    CHECK_NOTHROW(mc.removeElement(8));
    CHECK(mc.size() == 1);

    CHECK_NOTHROW(mc.removeElement(9));
    CHECK(mc.size() == 0);
}

TEST_CASE("Erasing a non existing member throws an exception"){
    MagicalContainer mc;
    mc.addElement(5);
    mc.addElement(8);
    mc.addElement(27);
    CHECK_THROWS(mc.removeElement(45));
    CHECK_THROWS(mc.removeElement(268));
}

TEST_CASE("Adding two same elments ignores the second"){
    MagicalContainer mc;
    mc.addElement(5);
    CHECK(mc.size() == 1);

    mc.addElement(8);
    CHECK(mc.size() == 2);

    mc.addElement(27);
    CHECK(mc.size() == 3);

    mc.addElement(8);
    CHECK(mc.size() == 3);

    mc.addElement(93); //if its an element we have never seen before, proceed to make the size larger
    CHECK(mc.size() == 4);

}

TEST_CASE("Test each iterator individually") {
    MagicalContainer mc;

    mc.addElement(1);
    mc.addElement(8);
    mc.addElement(4);
    mc.addElement(5);
    mc.addElement(14);
    mc.addElement(17);

    SUBCASE("AscendingIterator") {
        MagicalContainer::AscendingIterator it = MagicalContainer::AscendingIterator(mc).begin();
        SUBCASE("basic check ++ and * operators"){
            CHECK(*it == 1);
            ++it;
            CHECK(*it == 4);
            ++it;
            CHECK(*it == 5);
            ++it;
            CHECK(*it == 8);
            ++it;
            CHECK(*it == 14);
            ++it;
            CHECK(*it == 17);
        }
        SUBCASE("Comparing two iterators"){
            MagicalContainer::AscendingIterator it2 = MagicalContainer::AscendingIterator(mc).begin();
            ++it2;
            ++it2;
            ++it2;
            ++it2;
            
            CHECK_FALSE(it2 > it);
            CHECK(it > it2); 

            ++it2;

            CHECK(it == it2);
        }
    }

    SUBCASE("PrimeIterator") {
        MagicalContainer::PrimeIterator it = MagicalContainer::PrimeIterator(mc).begin();
        SUBCASE("basic check ++ and * operators"){
            CHECK(*it == 2);
            ++it;
            CHECK(*it == 17);
        }
        SUBCASE("comparing two iterators"){
            MagicalContainer::PrimeIterator it2 = MagicalContainer::PrimeIterator(mc).begin();
            CHECK(it > it2);
            CHECK_FALSE(it < it2);
            CHECK_FALSE(it == it2);
            ++it2;
            CHECK(it == it2);
        }
    }

    SUBCASE("SideCrossIterator") {
        MagicalContainer::SideCrossIterator it = MagicalContainer::SideCrossIterator(mc).begin();
        SUBCASE("basic check ++ and * operators"){
            CHECK(*it == 1);
            ++it;
            CHECK(*it == 17);
            ++it;
            CHECK(*it == 4);
            ++it;
            CHECK(*it == 14);
            ++it;
            CHECK(*it == 5);
            ++it;
            CHECK(*it == 8);
        }

        MagicalContainer::SideCrossIterator it2 = MagicalContainer::SideCrossIterator(mc).begin();
        SUBCASE("comparing two iterators"){
            ++it2;
            ++it2;
            ++it2;
            ++it2;
            
            CHECK_FALSE(it2 > it);
            CHECK(it > it2); 

            ++it2;

            CHECK(it == it2);
        }
    }
}

TEST_CASE("Test each iterator individually but bigger - checks all items were reached by the correct order (.end() is correct as well)") {
    MagicalContainer mc;

    for(int i = 1; i <= 100; i++) {
        mc.addElement(i);
    }

    SUBCASE("AscendingIterator") {
        MagicalContainer::AscendingIterator it = MagicalContainer::AscendingIterator(mc).begin();
        MagicalContainer::AscendingIterator itend = MagicalContainer::AscendingIterator(mc).end();
        int expected_value = 1;

        while(it != itend) {
            CHECK(*it == expected_value);
            ++it;
            ++expected_value;
        }
        CHECK(expected_value == mc.size() + 1); // Ensure all elements were traversed
    }

    SUBCASE("PrimeIterator") {
        MagicalContainer::PrimeIterator it = MagicalContainer::PrimeIterator(mc).begin();
        MagicalContainer::PrimeIterator endit = MagicalContainer::PrimeIterator(mc).end();
        std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
        std::size_t index = 0;

        while(it != endit) {
            CHECK(*it == primes[index]);
            ++it;
            ++index;
        }
        CHECK(index == primes.size()); // Ensure all elements were traversed
    }

    SUBCASE("SideCrossIterator") {
        MagicalContainer::SideCrossIterator it = MagicalContainer::SideCrossIterator(mc).begin();
        MagicalContainer::SideCrossIterator endit = MagicalContainer::SideCrossIterator(mc).end();
        int expected_value_front = 1;
        int expected_value_back = 100;

        int index = 0;
        while(it != endit) {
            if (index % 2 == 0) {
                CHECK(*it == expected_value_front);
                ++expected_value_front;
            } else {
                CHECK(*it == expected_value_back);
                --expected_value_back;
            }
            ++it;
            ++index;
        }
        CHECK(index == mc.size()); // Ensure all elements were traversed
    }
}


TEST_CASE("Test with no valid elements for iterator") {
    MagicalContainer mc;
    SUBCASE("AscendingIterator"){CHECK(MagicalContainer::AscendingIterator(mc).begin()==MagicalContainer::AscendingIterator(mc).end());}
    SUBCASE("SideCrossIterator"){CHECK(MagicalContainer::SideCrossIterator(mc).begin()==MagicalContainer::SideCrossIterator(mc).end());}
    mc.addElement(8);
    mc.addElement(33);
    mc.addElement(15);
    mc.addElement(14);
    mc.addElement(706);
    SUBCASE("PrimeIterator"){CHECK(MagicalContainer::PrimeIterator(mc).begin()==MagicalContainer::PrimeIterator(mc).end());}
}

TEST_CASE("Test comparing iterators pointing to different containers throws") {
    MagicalContainer mc1, mc2;

    // Fill containers with some data
    for(int i = 1; i <= 100; i++) {
        mc1.addElement(i);
        mc2.addElement(i * 2);
    }

    SUBCASE("AscendingIterator"){
        MagicalContainer::AscendingIterator it1 = MagicalContainer::AscendingIterator(mc1).begin();
        MagicalContainer::AscendingIterator endit1 = MagicalContainer::AscendingIterator(mc1).begin();
        MagicalContainer::AscendingIterator it2 = MagicalContainer::AscendingIterator(mc1).begin();
        MagicalContainer::AscendingIterator endit2 = MagicalContainer::AscendingIterator(mc1).begin();

        while(it1 != endit1 && it2 != endit2) {
            CHECK_THROWS((void)(it1 == it2));
            CHECK_THROWS((void)(it1 > it2));
            CHECK_THROWS((void)(it1 < it2));
            CHECK_THROWS((void)(it1 != it2));
            ++it1;
            ++it2;
        }
    }

    SUBCASE("SideCrossIterator"){
        MagicalContainer::SideCrossIterator it1 = MagicalContainer::SideCrossIterator(mc1).begin();
        MagicalContainer::SideCrossIterator endit1 = MagicalContainer::SideCrossIterator(mc1).begin();
        MagicalContainer::SideCrossIterator it2 = MagicalContainer::SideCrossIterator(mc1).begin();
        MagicalContainer::SideCrossIterator endit2 = MagicalContainer::SideCrossIterator(mc1).begin();

        while(it1 != endit1 && it2 != endit2) {
            CHECK_THROWS((void)(it1 == it2));
            CHECK_THROWS((void)(it1 > it2));
            CHECK_THROWS((void)(it1 < it2));
            CHECK_THROWS((void)(it1 != it2));
            ++it1;
            ++it2;
        }
    }

    SUBCASE("PrimeIterator"){
        MagicalContainer::PrimeIterator it1 = MagicalContainer::PrimeIterator(mc1).begin();
        MagicalContainer::PrimeIterator endit1 = MagicalContainer::PrimeIterator(mc1).begin();
        MagicalContainer::PrimeIterator it2 = MagicalContainer::PrimeIterator(mc1).begin();
        MagicalContainer::PrimeIterator endit2 = MagicalContainer::PrimeIterator(mc1).begin();

        while(it1 != endit1 && it2 != endit2) {
            CHECK_THROWS((void)(it1 == it2));
            CHECK_THROWS((void)(it1 > it2));
            CHECK_THROWS((void)(it1 < it2));
            CHECK_THROWS((void)(it1 != it2));
            ++it1;
            ++it2;
        }
    }
}