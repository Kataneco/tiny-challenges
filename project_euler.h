#pragma once

inline uint64_t triangleNumber(double index) {
    return static_cast<uint64_t>((index + 1) * index / 2);
}

#define MAX_PRIME_BUF_SIZE 256
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

uint64_t getFactorCount(uint64_t num) {
    uint64_t result = 1;
    uint64_t factor_power = 2;
    if (isPrime(num)) return 2;

    if (~num & 1) {
        num /= 2;
        for (; ~num & 1; num /= 2)
            factor_power++;
        result *= factor_power;
    }

    for (uint64_t i = 3; i <= num; i += 2) {
        if (!check(i)) continue;
        if (num % i == 0) {
            num /= i;
            factor_power = 2;
            for (; num % i == 0; num /= i)
                factor_power++;
            result *= factor_power;
        }
    }

    return result;
}

uint64_t smallestTriangleNumberWithOverXAmountOfFactors(uint64_t X) {
    for (uint64_t i = 2; i < UINT64_MAX; i++)
        if (getFactorCount(triangleNumber(i)) >= X) return triangleNumber(i);
    return 0;
}
