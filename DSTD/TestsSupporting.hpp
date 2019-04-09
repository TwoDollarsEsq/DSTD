//
//  TestsSupporting.hpp
//
//  Created by Artyom Rudakov on 1/16/19.
//  Copyright © 2019 Artyom Rudakov.
//  MIT license - see LICENSE.md
//

#pragma once
#include <iostream>
#include <chrono>
#include <fstream>
#define paragraph "\n\n"

template <typename closure>
void genericTest(std::string name, closure action) {
    std::cout << name << " began:" << std::endl;
    action();
    std::cout << name << " ended." << paragraph;
}

// Time management
#define now std::chrono::high_resolution_clock::now();
#define timeP std::chrono::high_resolution_clock::time_point
#define aTime std::chrono::duration<double> time
#define tConvert(start, end)  std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count()

