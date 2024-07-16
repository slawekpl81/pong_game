#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <random>

namespace slk_defs
{
    template <typename T>
    int randomInt(T from, T to)
    {
        return rand() % ((int)to - (int)from + 1) + from;
    }

    float randomFloat(float min, float max)
    {
        std::random_device rd;                          // Obtain a random number from hardware
        std::mt19937 gen(rd());                         // Seed the generator
        std::uniform_real_distribution<> dis(min, max); // Define the range

        return dis(gen);
    }

    template <typename T>
    void printVar(std::string varName, T var)
    {
        std::cout << varName << ": " << var << std::endl;
    }

    template <typename T>
    T maxOfTwo(T &a, T &b)
    {
        return std::max(a, b);
    }
};