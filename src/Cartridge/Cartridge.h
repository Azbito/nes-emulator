#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <vector>

#include "PPU/PPU.h"

class Cartridge {
public:
    Cartridge(const std::vector<uint8_t> &romData);

    const std::vector<uint8_t> &getCHRROM() const;
    const std::vector<uint8_t> &getPRGROM() const;

    uint8_t readPRG(uint16_t address);
    void writePRG(uint16_t address, uint8_t value);

private:
    std::vector<uint8_t> prgROM;
    std::vector<uint8_t> chrROM;
};

#endif
