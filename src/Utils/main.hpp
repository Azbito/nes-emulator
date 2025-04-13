#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

#include "CPU/CPU6502.h"

namespace utils {

inline std::string uint8ToString(uint8_t value) {
    return std::to_string(value);
}

std::string hexToString(uint32_t n, uint8_t d) {
    std::string s(d, '0');
    for (int i = d - 1; i >= 0; i--, n >>= 4)
        s[i] = "0123456789ABCDEF"[n & 0xF];
    return "0x" + s;
}
}  // namespace utils

#endif  // UTILS_HPP
