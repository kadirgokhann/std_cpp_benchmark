#include "utils.hpp"
#include <immintrin.h>
#include <random>
#include <iostream>
#include <chrono>

#define N (1 << 12)  // 4096 elements, aligned to 32 bytes for SIMD
alignas(32) int a[N];

// SIMD-based find function using AVX2 instructions
int find_simd(int needle, const int* array) {
    __m256i needleVec = _mm256_set1_epi32(needle);  // Set all elements to needle
    for (int i = 0; i < N; i += 8) {
        __m256i dataVec = _mm256_load_si256((__m256i*)&array[i]);  // Load 8 integers
        __m256i cmpVec = _mm256_cmpeq_epi32(needleVec, dataVec);  // Compare
        int mask = _mm256_movemask_ps((__m256)cmpVec);  // Get comparison mask
        if (mask != 0) {
            return i + __builtin_ctz(mask);  // Return the position of the first match
        }
    }
    return -1;  // Return -1 if not found
}

// Benchmark for standard find function
static void testFindStd() {
    initialize_array(a, N);  // Initialize array with random values
    int needle = get_random_needle(N);
    int result = find_std(a, needle, N);  // Use standard find
    std::cout << "Standard find result: " << result << "\n";
}

// Benchmark for SIMD-based find function
static void testFindSIMD() {
    initialize_array(a, N);  // Initialize array with random values
    int needle = get_random_needle(N);
    int result = find_simd(needle, a);  // Use SIMD find
    std::cout << "SIMD find result: " << result << "\n";
}

int main() {
    // Measure time for standard find
    auto start_std = std::chrono::high_resolution_clock::now();
    testFindStd();
    auto end_std = std::chrono::high_resolution_clock::now();
    auto duration_std = std::chrono::duration_cast<std::chrono::microseconds>(end_std - start_std).count();
    std::cout << "Standard find execution time: " << duration_std << " microseconds\n";

    // Measure time for SIMD-based find
    auto start_simd = std::chrono::high_resolution_clock::now();
    testFindSIMD();
    auto end_simd = std::chrono::high_resolution_clock::now();
    auto duration_simd = std::chrono::duration_cast<std::chrono::microseconds>(end_simd - start_simd).count();
    std::cout << "SIMD find execution time: " << duration_simd << " microseconds\n";

    return 0;
}
