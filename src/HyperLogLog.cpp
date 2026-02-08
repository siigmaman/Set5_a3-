#include "HyperLogLog.h"
#include <algorithm>
#include <cmath>

HyperLogLog::HyperLogLog(int B_) : B(B_), m(1 << B_), M(m, 0) {}

int HyperLogLog::rho(uint32_t w) {
    int r = 1;
    while ((w & 0x80000000) == 0 && r <= 32 - B) {
        w <<= 1;
        ++r;
    }
    return r;
}

void HyperLogLog::add(uint32_t x) {
    uint32_t idx = x >> (32 - B);
    uint32_t w = x << B;
    M[idx] = std::max(M[idx], rho(w));
}

double HyperLogLog::estimate() const {
    double Z = 0.0;
    for (auto v : M) Z += 1.0 / (1 << v);
    double alpha = 0.7213 / (1 + 1.079 / m);
    return alpha * m * m / Z;
}