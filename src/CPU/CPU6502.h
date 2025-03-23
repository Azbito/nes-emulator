#ifndef CPU6502_H
#define CPU6502_H

#include <cstdint>
#include <cstring>
#include <iostream>

class CPU6502
{
  public:
    uint8_t A, X, Y, P, SP;
    uint16_t PC;
    uint8_t RAM[0x10000];

    CPU6502();

    void updateZNFlags(uint8_t value);
    void pushToStack(uint8_t value);
    void pushToStack16(uint16_t value);

    bool isNegativeFlagClean();

    void writeMemory(uint16_t address, uint8_t value);
    uint8_t readMemory(uint16_t address);
};

#endif
