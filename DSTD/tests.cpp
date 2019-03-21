//
//  tests.cpp
//  DSTD
//
//  Created by Artyom Rudakov on 3/20/19.
//  Copyright © 2019 Artyom Rudakov. All rights reserved.
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


int main() {
    using namespace dstd;
    
    std::cout << "Hello, DSTD!\n";
    vector<int> vectorOfInts = { 1, 2, 3, 4, 5 };
    vectorOfInts.filter(LAr( i0 <= 3 )).forEach(printInLine);
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
    
    return 0;
}
