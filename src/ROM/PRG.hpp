#ifndef PRG_HPP
#define PRG_HPP

#include "CPU/CPU6502.h"
#include <iostream>
#include <vector>

#define KB_16 16384

class PRG
{
  public:
    PRG(const std::vector<uint8_t> &romData, CPU6502 &cpu)
        : romData(romData), cpu(cpu)
    {
    }

    bool load()
    {
        size_t size = romData.size();

        if (size == KB_16)
        {
            for (size_t i = 0; i < KB_16; ++i)
            {
                cpu.writeMemory(0x8000 + i, romData[i]);
                cpu.writeMemory(0xC000 + i, romData[i]);
            }
        }
        else if (size == 2 * KB_16)
        {
            for (size_t i = 0; i < KB_16; ++i)
            {
                cpu.writeMemory(0x8000 + i, romData[i]);
                cpu.writeMemory(0xC000 + i, romData[KB_16 + i]);
            }
        }
        else
        {
            printf("\033[1;31m[SYSTEM] Unsupported PRG-ROM size: %llu\033[0m\n",
                   size);
            return false;
        }

        return true;
    }

  private:
    const std::vector<uint8_t> &romData;
    CPU6502 &cpu;
};

#endif
