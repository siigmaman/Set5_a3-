#include "HashFuncGen.h"
#include <functional>

uint32_t HashFuncGen::hash(const std::string& s) {
    return static_cast<uint32_t>(std::hash<std::string>{}(s));
}