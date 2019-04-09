//
//  tests.cpp
//  DSTD
//
//  Created by Artyom Rudakov on 3/20/19.
//  Copyright © 2019 Artyom Rudakov.
//  MIT license - see LICENSE.md
//

#include <iostream>
template <class _T1, class _T2>
std::ostream& operator << (std::ostream & os, const std::pair<_T1, _T2> & pair) {
    return os << "(" << pair.first << ", " << pair.second << ")";
}
#include "DCollection.hpp"

template <class Collection>
void print(Collection && collection) {
    collection.forEach(dstd::printInLine);
    printf("\n");
};

struct Person {
    std::string name;
    short age;
    unsigned id;
    
    bool operator < (const Person & other) const {
        return id < other.id;
    }
    
    friend std::ostream& operator <<(std::ostream & os, const Person & p) {
        return os << "(" << p.name << ", " << p.age << ")";
    }
};

void mappingSpeedTest();

int main() {
    using namespace dstd;
    
    std::cout << "Hello, DSTD!\n";
    vector<int> vectorOfInts = { 1, 2, 3, 4, 5 };
    vectorOfInts.filter(lessOrEqualTo(3)).forEach(printInLine);
    printOnNewLine(vectorOfInts.reduce(0, plus)) << "\n";
    print(vectorOfInts.map(LAr( i0 + 0.5; )));
    
    map<std::string, short> crowd = {
        // Name        Age
        { "Artyom",    19 },
        { "Brian",     27 },
        { "Charlotte", 17 },
        { "Michael",   48 },
        { "Joe",       13 },
        { "Kara",      21 }
    };
    print(crowd);
    print(crowd.filter(LAr(i0.second >= 21)));
    printf("Average age in crowd: %.1f\n",
           crowd.reduce(0.0, bLAr(i0 + i1.second)) / crowd.size());
    
    set<Person> people = {
        // Name     Age ID
        { "Kara",   21, 579102694 },
        { "Markus", 25, 684842971 },
        { "Connor", 23, 313248317 },
        { "Alice",  9,  0xa9 }
    };
    print(people.filter(LAr(i0.age >= 21)));
    print(people.map(LAr(i0.name)));
    printf("Average age: %.1f\n",
           people.reduce(0.0, bLAr(i0 + i1.age)) / people.size());
    
    mappingSpeedTest();
    return 0;
}

#include "TestsSupporting.hpp"
void mappingSpeedTest() {
    using namespace dstd;
    genericTest("Mapping speed test", [&] {
        // Test Setup
        std::ofstream log("logs/MappingTest4", std::ios::out);
        timeP startGlobal = now
        size_t sampleSize = 10e6;
        short testCount = 10;
        
        struct Entity {
            double iterative, declarative;
            Entity operator + (const Entity & other) const {
                return {iterative + other.iterative, declarative + other.declarative};
            }
            Entity operator / (const int scalar) const {
                return {iterative / scalar, declarative / scalar};
            }
        };
        vector<Entity> statistic(testCount);
        
        std::cout << "Filling vector...\n\n";
        vector<int> vectorOfInts(sampleSize, 10);
        vectorOfInts.forEach(LA { i0 *= rand(); });
        
        // Test Body
        for (short it = 1; it <= testCount; ++ it) {
            timeP startIt, stopIt, startDec, stopDec;
            
            genericTest("Iterative mapping[" + std::to_string(it) + "]", [&] {
                startIt = now
                vector<double> vectorOfDoubles;
                for (auto & integer : vectorOfInts) {
                    vectorOfDoubles.push_back(integer + 0.25);
                }
                stopIt = now
                std::cout << vectorOfDoubles.size() << "\n";
            });
            
            genericTest("Declarative mapping[" + std::to_string(it) + "]", [&] {
                startDec = now
                auto vectorOfDoubles = vectorOfInts.map([](auto & i0) -> auto {
                    return i0 + 0.5;
                });
                stopDec = now
                std::cout << vectorOfDoubles.size() << "\n";
            });
            
            double diffIt  = tConvert(startIt, stopIt),
                   diffDec = tConvert(startDec, stopDec);
            
            log << " Time passed while loop[" << it << "]: " << diffIt  << "\n";
            log << " Time passed while map [" << it << "]: " << diffDec << paragraph;
            statistic.push_back({diffIt, diffDec});
        }
        
        Entity average = statistic.reduce(Entity{0, 0}, plus) / testCount;
        timeP stopGlobal = now
        log << "Made " << testCount << " tests\n"
        << "with sample size: " << sampleSize << "\n"
        << "Iterative   average: " << average.iterative   << " sec.\n"
        << "Declarative average: " << average.declarative << " sec.\n"
        
        << "Global time: " << tConvert(startGlobal, stopGlobal) << " sec.\n";
        
        if (average.declarative > average.iterative) {
            log << "Loop is faster than map by "
            << 1 - average.iterative / average.declarative << " percents.\n";
        } else {
            log << "map is faster than loop by "
            << 1 - average.declarative / average.iterative << " percents.\n";
        }
    });
}
