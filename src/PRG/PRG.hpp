#ifndef PRG_HPP
#define PRG_HPP

#include "CPU/CPU6502.h"
#include "JIT/Compiler.h"
#include "ROM/Loader.h"
#include <iostream>
#include <vector>

#define JIT_BUFFER_SZ 4096
#define INIT_ADDRESS 0x8000
#define MB_16 16384

class PRGLoader
{
  public:
    PRGLoader(const std::vector<uint8_t> &romData, CPU6502 &cpu)
        : romData(romData), cpu(cpu)
    {
    }

    bool loadPRG(uint8_t prgBanks)
    {
        size_t prgStart = 16;
        size_t prgSize = prgBanks * MB_16;

        if (prgStart + prgSize > romData.size())
        {
            std::cerr << "ROM file too small." << std::endl;
            return false;
        }

        for (size_t i = 0; i < prgSize; ++i)
        {
            uint16_t address = 0x8000 + i;
            cpu.RAM[address] = romData[prgStart + i];

            if (prgBanks == 1 && address >= 0xC000)
            {
                cpu.RAM[address] = romData[prgStart + (i % 16384)];
            }
        }

        return true;
    }

  private:
    const std::vector<uint8_t> &romData;
    CPU6502 &cpu;
};

#endif
