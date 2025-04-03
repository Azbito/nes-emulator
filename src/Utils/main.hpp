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

} // namespace utils

#endif // UTILS_HPP
