#ifndef PRG_HPP
#define PRG_HPP

#include "CPU/CPU6502.h"
#include "JIT/Compiler.h"
#include "ROM/Loader.h"
#include <iostream>
#include <vector>

#define JIT_BUFFER_SZ 4096
#define INIT_ADDRESS 0x8000
#define KB_16 16384

class PRG
{
  public:
    PRG(const std::vector<uint8_t> &romData, CPU6502 &cpu)
        : romData(romData), cpu(cpu)
    {
    }

    bool load(uint8_t prgBanks)
    {
        size_t prgStart = 16;
        size_t prgSize = prgBanks * KB_16;

        if (prgSize < 16 + 16384)
        {
            printf(
                "\033[1;31m[SYSTEM] ROM is too small. ROM Size: %llu \033[0m\n",
                romData.size());

            return false;
        }

        for (size_t i = 0; i < prgSize; ++i)
        {
            uint16_t address = 0x8000 + i;
            cpu.setRAM(address, romData[prgStart + i]);

            if (prgBanks == 1 && address >= 0xC000)
            {
                cpu.setRAM(address, romData[prgStart + (i % 16384)]);
            }
        }

        return true;
    }

  private:
    const std::vector<uint8_t> &romData;
    CPU6502 &cpu;
};

#endif
