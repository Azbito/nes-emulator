#ifndef UTILS_HPP //#pragma once
#define UTILS_HPP

#include <string>

namespace utils {

inline std::string uint8ToString(uint8_t value) {
    return std::to_string(value);
}

inline std::string hexToString(uint32_t n, uint8_t d) {
    std::string s(d, '0');
    for (int i = d - 1; i >= 0; i--, n >>= 4)
        s[i] = "0123456789ABCDEF"[n & 0xF];
    return "0x" + s;
}

inline std::string toHexString(uint16_t value, int width) {
    std::stringstream ss;
    ss << std::uppercase << std::hex << std::setfill('0') << std::setw(width) << (int)value;
    return ss.str();
}

inline std::string toFlagString(uint8_t flags) {
    std::string flagStr;
    flagStr += (flags & 0x80) ? "N" : "-";
    flagStr += (flags & 0x40) ? "V" : "-";
    flagStr += (flags & 0x20) ? " " : "-";
    flagStr += (flags & 0x10) ? "B" : "-";
    flagStr += (flags & 0x08) ? "D" : "-";
    flagStr += (flags & 0x04) ? "I" : "-";
    flagStr += (flags & 0x02) ? "Z" : "-";
    flagStr += (flags & 0x01) ? "C" : "-";
    return flagStr;
}

}  // namespace utils

#endif  // UTILS_HPP
