#ifndef UTILS_HPP
#define UTILS_HPP

#include "CPU/CPU6502.h"
#include <string>

namespace utils
{

inline std::string uint8ToString(uint8_t value)
{

    return std::to_string(value);
}

inline std::string hexToString(uint8_t opcode)
{
    char buffer[5];
    snprintf(buffer, sizeof(buffer), "[%02X]", opcode);
    return buffer;
}

} // namespace utils

#endif // UTILS_HPP
