#pragma once
#include <vector>
#include <cstdint>

class HyperLogLog {
private:
    int B;        
    int m;
    std::vector<int> M;

    int rho(uint32_t w);

public:
    HyperLogLog(int B_);
    void add(uint32_t x);
    double estimate() const;
};