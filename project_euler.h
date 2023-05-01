#pragma once
#include <unordered_map>

uint64_t triangleNumber(double index) {
    return static_cast<uint64_t>((index + 1) * index / 2);
}

#define MAX_PRIME_BUF_SIZE 1024
uint64_t primeBuf[MAX_PRIME_BUF_SIZE] = {3, 5};
uint64_t size = 1;

bool isPrime(uint64_t num) {
    if (~num & 1) return num == 2;
    if (num == 1) return false;

    for (uint64_t i = 0; i <= size; i++)
        if (num == primeBuf[i]) return true;

    for (uint64_t i = primeBuf[size]; i * i <= num; i += 2)
        if (num % i == 0) return false;

    if (size < MAX_PRIME_BUF_SIZE - 1) primeBuf[size] = num;
    return true;
}

bool check(uint64_t num) {
    for (uint64_t i = 0; i <= size; i++)
        if (num == primeBuf[i]) return true;

    for (uint64_t i = primeBuf[size]; i * i <= num; i += 2)
        if (num % i == 0) return false;

    if (size < MAX_PRIME_BUF_SIZE - 1) primeBuf[size] = num;
    return true;
}

std::unordered_map<uint64_t, uint64_t> primeFactorize(uint64_t num) {
    if (num < 2) return std::unordered_map<uint64_t, uint64_t>{};
    if (isPrime(num)) return std::unordered_map<uint64_t, uint64_t>{{num, 1}};

    std::unordered_map<uint64_t, uint64_t> factors;

    if (~num & 1) {
        num /= 2;
        factors[2] = 1;
        for (;;) {
            if (~num & 1) {
                num /= 2;
                factors[2]++;
            } else break;
        }
    }

    for (uint64_t i = 3; i <= num; i += 2) {
        if (!check(i)) continue;
        if (num % i == 0) {
            num /= i;
            factors[i] = 1;
            for (;;) {
                if (num % i == 0) {
                    num /= i;
                    factors[i]++;
                } else break;
            }
        }
    }

    return factors;
}

uint64_t getFactorCount(uint64_t num) {
    uint64_t result = 1;
    for (const auto &f: primeFactorize(num))
        result *= f.second + 1;
    return result;
}

uint64_t smallestTriangleNumberWithOverXAmountOfFactors(uint64_t X) {
    for (uint64_t i = 1; i < UINT64_MAX; i++)
        if (getFactorCount(triangleNumber(i)) >= X) return triangleNumber(i);
    return 0;
}