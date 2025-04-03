#ifndef LOADER_H
#define LOADER_H

#include "ROM/ROM.hpp"
#include <cstdint>
#include <fstream>
#include <vector>

class ROMLoader
{
  public:
    ROMLoader() = default;

    bool load(const std::string &filename, ROM &rom);
    bool verify(const std::vector<uint8_t> &data) const;
};

#endif
