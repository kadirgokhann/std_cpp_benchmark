#include "utils.hpp"

#include <string>
#include <chrono>
#include <iostream>

// Custom string to number function
int ston(const std::string& str) 
{
    volatile int sum = 0;
    for (char ch : str) 
    {
        sum = sum * 10 + (ch - '0');
    }
    return sum;
}

// Benchmark for custom ston function
void testSton() 
{
    std::string str = "2147483647";  // Max value for 32-bit signed integer
    volatile int result = 0;
    for (int i = 0; i < 1000000; ++i) 
    {
        result = ston(str);
    }
}

// Benchmark for standard std::stoi function
void testStdStoi() 
{
    std::string str = "2147483647";  // Max value for 32-bit signed integer
    volatile int result = 0;
    for (int i = 0; i < 1000000; ++i) 
    {
        result = std::stoi(str);
    }
}

int main(int argc, char** argv) 
{
    // Measure time for custom ston function
    auto start = std::chrono::high_resolution_clock::now();
    testSton();
    auto end = std::chrono::high_resolution_clock::now();
    auto durationSton = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Custom ston execution time: " << durationSton << " microseconds\n";

    // Measure time for std::stoi function
    start = std::chrono::high_resolution_clock::now();
    testStdStoi();
    end = std::chrono::high_resolution_clock::now();
    auto durationStdStoi = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "std::stoi execution time: " << durationStdStoi << " microseconds\n";

    return 0;
}
