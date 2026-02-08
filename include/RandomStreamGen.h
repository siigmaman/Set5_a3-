#pragma once
#include <string>
#include <vector>
#include <random>

class RandomStreamGen {
private:
    std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-";
    std::mt19937 rng;
    std::uniform_int_distribution<> charDist;
    std::uniform_int_distribution<> lengthDist;

public:
    RandomStreamGen();
    std::string generateString();
    std::vector<std::string> generateStream(size_t n);
    std::vector<std::vector<std::string>> splitStream(const std::vector<std::string>& stream, int stepPercent);
};