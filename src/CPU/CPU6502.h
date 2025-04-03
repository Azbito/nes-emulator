#ifndef CPU6502_H
#define CPU6502_H

#include "PPU/PPU.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>

class CPU6502
{
  public:
    uint8_t A, X, Y, P, SP;
    uint16_t PC;
    uint8_t RAM[0x10000];

    enum Flags
    {
        C = 0x01,
        Z = 0x02,
        I = 0x04,
        D = 0x08,
        B = 0x10,
        U = 0x20,
        V = 0x40,
        N = 0x80
    };

    CPU6502(PPU &ppuRef);

    void updateZNFlags(uint8_t value);
    void pushToStack(uint8_t value);
    void pushToStack16(uint16_t value);

    bool isNegativeFlagClean();

    void writeMemory(uint16_t address, uint8_t value);
    uint8_t readMemory(uint16_t address);

    uint8_t status() const;

    void setStatus(uint8_t status);
    void setFlag(uint8_t flag, bool value);

    bool isFlagSet(uint8_t flag) const;

  private:
    PPU *ppu;
};

#endif
