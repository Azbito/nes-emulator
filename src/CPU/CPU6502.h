#ifndef CPU6502_H
#define CPU6502_H

#include "PPU/PPU.h"
#include <cstdint>
#include <cstring>
#include <iostream>

class CPU6502
{
  public:
    uint8_t A, X, Y, P, SP;
    uint16_t PC;
    uint32_t cycles;
    uint8_t RAM[65536];

    enum Flags
    {
        FLAG_CARRY = 1 << 0,
        FLAG_ZERO = 1 << 1,
        FLAG_INTERRUPT = 1 << 2,
        FLAG_DECIMAL = 1 << 3,
        FLAG_BREAK = 1 << 4,
        FLAG_UNKNOW = 1 << 5,
        FLAG_OVERFLOW = 1 << 6,
        FLAG_NEGATIVE = 1 << 7
    };

    CPU6502(PPU &ppuRef);

    void updateZNFlags(uint8_t value);
    void pushToStack(uint8_t value);
    void pushToStack16(uint16_t value);
    uint8_t popStack();

    bool isNegativeFlagClean();
    void clock();

    void writeMemory(uint16_t address, uint8_t value);
    uint8_t readMemory(uint16_t address);

    void setStatus(uint8_t status);
    void setFlag(uint8_t flag, bool value);
    bool getFlag(uint8_t flag);
    bool isFlagSet(uint8_t flag) const;
    void reset();

  private:
    PPU *ppu;
};
#endif
