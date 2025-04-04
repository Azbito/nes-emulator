#include "CPU6502.h"

#define PPU_STATUS 0x2002

CPU6502::CPU6502(PPU &ppuRef) : ppu(&ppuRef)
{
    A = X = Y = 0;
    P = 0;
    SP = 0xFF;
    PC = 0x0000;
    std::memset(RAM, 0, sizeof(RAM));
}

bool CPU6502::getFlag(uint8_t flag)
{
    return (P & flag) != 0;
}

void CPU6502::updateZNFlags(uint8_t value)
{
    setFlag(FLAG_ZERO, value == 0);
    setFlag(FLAG_NEGATIVE, value & 0x80);
}

uint8_t CPU6502::popStack()
{
    return readMemory(0x0100 + ++SP);
}

void CPU6502::pushToStack(uint8_t value)
{
    writeMemory(0x0100 + SP--, value);
}

void CPU6502::pushToStack16(uint16_t value)
{
    pushToStack((value >> 8) & 0xFF);
    pushToStack(value & 0xFF);
}

bool CPU6502::isNegativeFlagClean()
{
    return !(P & 0x80);
}

void CPU6502::writeMemory(uint16_t address, uint8_t value)
{
    RAM[address] = value;
}

uint8_t CPU6502::readMemory(uint16_t address)
{
    if (address == PPU_STATUS)
    {
        uint8_t value = this->ppu->status;

        this->ppu->setVerticalBlank(false);

        value &= 0xE0;

        return value;
    }

    return RAM[address];
}

void CPU6502::setStatus(uint8_t status)
{
    P = status;
}

void CPU6502::setFlag(uint8_t flag, bool value)
{
    if (value)
        P |= flag;
    else
        P &= ~flag;
}

bool CPU6502::isFlagSet(uint8_t flag) const
{
    return P & flag;
}
