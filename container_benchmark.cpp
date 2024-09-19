#include <vector>
#include <list>
#include <deque>
#include <set>
#include <numeric>
#include <iostream>
#include <chrono>

constexpr size_t N = 1 << 18;  // 262,144 elements

// Benchmark for vector iteration
static void  testVector() 
{
    std::vector<int> vec(N);
    std::iota(vec.begin(), vec.end(), 0);  // Fill vector with increasing values
    
    volatile int sum = 0;
    for (volatile const auto& elem : vec) 
    {
        sum = sum + elem;
    }
}

// Benchmark for list iteration
static void testList() 
{
    std::list<int> lst(N);
    std::iota(lst.begin(), lst.end(), 0);  // Fill list with increasing values
    
    volatile int sum = 0;
    for (volatile const auto& elem : lst) 
    {
        sum = sum + elem;
    }
}

// Benchmark for deque iteration
static void testDeque() 
{
    std::deque<int> deq(N);
    std::iota(deq.begin(), deq.end(), 0);  // Fill deque with increasing values
    
    volatile int sum = 0;
    for (volatile const auto& elem : deq) 
    {
        sum = sum + elem;
    }
}

// Benchmark for set iteration
static void testSet() 
{
    std::set<int> st;
    for (int i = 0; i < N; ++i)
    {
        st.insert(i);  // Fill set with increasing values
    }
    
    volatile int sum = 0;
    for (volatile const auto& elem : st) 
    {
        sum = sum + elem;
    }
}

int main(int argc, char** argv) 
{
    // Measure time for testVector
    auto start = std::chrono::high_resolution_clock::now();
    testVector();
    auto end = std::chrono::high_resolution_clock::now();
    auto durationVec = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "testVector execution time: " << durationVec << " microseconds\n";

    // Measure time for testList
    start = std::chrono::high_resolution_clock::now();
    testList();
    end = std::chrono::high_resolution_clock::now();
    auto durationList = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "testList execution time: " << durationList << " microseconds\n";

    // Measure time for testDeque
    start = std::chrono::high_resolution_clock::now();
    testDeque();
    end = std::chrono::high_resolution_clock::now();
    auto durationDeque = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "testDeque execution time: " << durationDeque << " microseconds\n";

    // Measure time for testSet
    start = std::chrono::high_resolution_clock::now();
    testSet();
    end = std::chrono::high_resolution_clock::now();
    auto durationSet = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "testSet execution time: " << durationSet << " microseconds\n";

    return 0;
}
