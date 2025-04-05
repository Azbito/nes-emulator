#include "CPU6502.h"

CPU6502::CPU6502(PPU &ppuRef) : ppu(&ppuRef)
{
    setA(0);
    setX(0);
    setY(0);
    setP(0);
    setSP(0xFF);
    setPC(0x0000);
    std::memset(m_RAM, 0, sizeof(m_RAM));
}

void CPU6502::reset()
{
    uint16_t low = readMemory(0xFFFC);
    uint16_t high = readMemory(0xFFFD);

    setPC((high << 8) | low);

    setA(0);
    setX(0);
    setY(0);
    setSP(0xFD);
    setP(0x24);
}

bool CPU6502::getFlag(uint8_t flag)
{
    return (m_P & flag) != 0;
}

void CPU6502::updateZNFlags(uint8_t value)
{
    setFlag(FLAG_ZERO, value == 0);
    setFlag(FLAG_NEGATIVE, value & 0x80);
}

uint8_t CPU6502::popStack()
{
    return readMemory(0x0100 + ++m_SP);
}

void CPU6502::pushToStack(uint8_t value)
{
    writeMemory(0x0100 + m_SP--, value);
}

void CPU6502::pushToStack16(uint16_t value)
{
    pushToStack((value >> 8) & 0xFF);
    pushToStack(value & 0xFF);
}

bool CPU6502::isNegativeFlagClean()
{
    return !(m_P & 0x80);
}

void CPU6502::writeMemory(uint16_t address, uint8_t value)
{
    if (address >= ppu->registers.PPUCTRL && address <= 0x3FFF)
    {
        uint16_t reg = 0x2000 + (address % 8);
        ppu->writeRegister(reg, value);
        return;
    }

    m_RAM[address] = value;
}

void CPU6502::clock()
{
    m_cycles--;
}

uint8_t CPU6502::readMemory(uint16_t address)
{
    if (address == ppu->registers.PPUSTATUS)
    {
        uint8_t value = ppu->getStatus();

        value |= (ppu->getVBlank() ? 0x80 : 0x00);

        ppu->setVerticalBlank(false);
        ppu->setAddressLatch(0);

        return value & 0xE0;
    }

    if (address >= ppu->registers.PPUCTRL && address <= 0x3FFF)
    {
        uint16_t reg = 0x2000 + (address % 8);
        return ppu->getRegister(reg);
    }

    return m_RAM[address];
}

void CPU6502::setStatus(uint8_t status)
{
    setP(status);
}

void CPU6502::setFlag(uint8_t flag, bool value)
{
    if (value)
        m_P |= flag;
    else
        m_P &= ~flag;
}

bool CPU6502::isFlagSet(uint8_t flag) const
{
    return m_P & flag;
}
