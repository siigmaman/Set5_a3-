#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <filesystem>
#include "RandomStreamGen.h"
#include "HashFuncGen.h"
#include "HyperLogLog.h"

size_t exactCount(const std::vector<std::string>& stream, HashFuncGen& hashGen) {
    std::unordered_set<uint32_t> s;
    for (auto& str : stream) s.insert(hashGen.hash(str));
    return s.size();
}

int main() {
    std::filesystem::create_directories("data");

    RandomStreamGen gen;
    HashFuncGen hashGen;

    size_t streamSize = 50000;
    auto stream = gen.generateStream(streamSize);
    
    int stepPercent = 10;
    auto steps = gen.splitStream(stream, stepPercent);

    int B = 10;
    HyperLogLog hll(B);

    std::ofstream out("data/results.csv");
    if (!out.is_open()) {
        std::cerr << "Error(";
        return 1;
    }

    out << "Step,Ft0,Nt\n";

    std::vector<std::string> processed;

    for (size_t i = 0; i < steps.size(); ++i) {
        processed.insert(processed.end(), steps[i].begin(), steps[i].end());

        for (auto& s : steps[i]) hll.add(hashGen.hash(s));

        size_t Ft0 = exactCount(processed, hashGen);

        double Nt = hll.estimate();

        out << (i+1)*stepPercent << "," << Ft0 << "," << Nt << "\n";
        std::cout << "Step " << (i+1)*stepPercent << "%: Ft0=" << Ft0 << ", Nt=" << Nt << "\n";
    }

    out.close();
    std::cout << "Результаты сохранены в data/results.csv\n";

    return 0;
}