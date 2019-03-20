//
//  tests.cpp
//  DSTD
//
//  Created by Artyom Rudakov on 3/20/19.
//  Copyright © 2019 Artyom Rudakov. All rights reserved.
//

#include "DCollection.hpp"

int main() {
    using namespace dstd;
    
    std::cout << "Hello, DSTD!\n";
    vector<int> vectorOfInts = { 1, 2, 3, 4, 5 };
    vectorOfInts.filter(LAr( i0 <= 3 )).forEach(printInLine);
    printOnNewLine(vectorOfInts.reduce(0, plus));
    
    return 0;
}
