#include "CPU/CPU6502.h"

CPU6502::CPU6502() : A(0), X(0), Y(0), P(0x34), SP(0xFD), PC(0x8000)
{
    memset(RAM, 0, sizeof(RAM));
}

void CPU6502::updateZNFlags(uint8_t value)
{
    if (value == 0)
    {
        P |= 0x02;
    }
    else
    {
        P &= ~0x02;
    }

    if (value & 0x80)
    {
        P |= 0x80;
    }
    else
    {
        P &= ~0x80;
    }
}

void CPU6502::pushToStack(uint8_t value)
{
    RAM[0x100 + SP] = value;
    SP--;
}

void CPU6502::pushToStack16(uint16_t value)
{
    pushToStack(static_cast<uint8_t>(value >> 8));
    pushToStack(static_cast<uint8_t>(value & 0xFF));
}

uint8_t CPU6502::readMemory(uint16_t addr)
{
    if (addr < 0x10000)
    {
        return RAM[addr];
    }
    return 0;
}

void CPU6502::writeMemory(uint16_t address, uint8_t value)
{
    RAM[address] = value;
}
