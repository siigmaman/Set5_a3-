#include "RandomStreamGen.h"

RandomStreamGen::RandomStreamGen() 
    : rng(std::random_device{}()), charDist(0, charset.size() - 1), lengthDist(5, 30) {}

std::string RandomStreamGen::generateString() {
    int len = lengthDist(rng);
    std::string s;
    for (int i = 0; i < len; ++i)
        s += charset[charDist(rng)];
    return s;
}

std::vector<std::string> RandomStreamGen::generateStream(size_t n) {
    std::vector<std::string> stream;
    stream.reserve(n);
    for (size_t i = 0; i < n; ++i)
        stream.push_back(generateString());
    return stream;
}

std::vector<std::vector<std::string>> RandomStreamGen::splitStream(const std::vector<std::string>& stream, int stepPercent) {
    std::vector<std::vector<std::string>> parts;
    size_t step = stream.size() * stepPercent / 100;
    for (size_t i = 0; i < stream.size(); i += step) {
        size_t end = std::min(i + step, stream.size());
        parts.push_back(std::vector<std::string>(stream.begin(), stream.begin() + (end - i)));
    }
    return parts;
}