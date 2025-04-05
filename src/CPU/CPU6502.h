#ifndef CPU6502_H
#define CPU6502_H

#include "PPU/PPU.h"
#include <cstdint>
#include <cstring>
#include <iostream>

class CPU6502
{
  public:
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

    uint8_t getA() const;
    void setA(uint8_t value);

    uint8_t getX() const;
    void setX(uint8_t value);

    uint8_t getY() const;
    void setY(uint8_t value);

    uint8_t getP() const;
    void setP(uint8_t value);

    uint8_t getSP() const;
    void setSP(uint8_t value);

    uint16_t getPC() const;
    void setPC(uint16_t value);

    uint32_t getCycles() const;
    void setCycles(uint32_t value);

    uint8_t getRAM(uint16_t address) const;
    void setRAM(uint16_t address, uint8_t value);

  private:
    uint8_t m_A;
    uint8_t m_X;
    uint8_t m_Y;
    uint8_t m_P;
    uint8_t m_SP;
    uint16_t m_PC;
    uint32_t m_cycles;
    uint8_t m_RAM[65536];

    PPU *ppu;
};

#endif
