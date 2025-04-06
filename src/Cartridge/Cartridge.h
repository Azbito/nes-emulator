#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <vector>

class Cartridge
{
  public:
    Cartridge(const std::vector<uint8_t> &romData);

    uint8_t readPRG(uint16_t address);
    void writePRG(uint16_t address, uint8_t value);

  private:
    std::vector<uint8_t> prgROM;
};

#endif
