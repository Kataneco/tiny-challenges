#include <iostream>
#include <chrono>
#include "project_euler.h"

int main() {
    auto start = std::chrono::steady_clock::now();

    uint64_t result = smallestTriangleNumberWithOverXAmountOfFactors(500);

    auto end = std::chrono::steady_clock::now();
    auto time = end - start;

    std::cout << "Time elapsed: " << time / std::chrono::milliseconds(1) << std::endl;
    std::cout << result << std::endl;
}
