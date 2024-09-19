#pragma once
#include <random>
#include <algorithm>  // for std::find
#include <iterator>   // for std::distance

// Initialize an array with random integers between 1 and 1,000,000
void initialize_array(int* array, int size) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for (int i = 0; i < size; ++i) {
        array[i] = dis(gen);
    }
}

// Generate a random index as a needle for testing
int get_random_needle(int size) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);
    return dist(gen);
}

// Standard find function using std::find
int find_std(const int* array, int value, int size) 
{
    const int* it = std::find(array, array + size, value);
    return (it != array + size) ? std::distance(array, it) : -1;
}
