#include "CPU6502.h"

CPU6502::CPU6502(PPU &ppuRef) : ppu(&ppuRef)
{
    setA(0);
    setX(0);
    setY(0);
    setP(0x34);
    setSP(0xFD);
    setPC(0x0000);

    for (int i = 0; i < 65536; i++)
    {
        m_RAM[i] = (i * 13) & 0xFF;
    }
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

uint8_t CPU6502::getA() const
{
    return m_A;
}

void CPU6502::setA(uint8_t value)
{
    m_A = value;
}

uint8_t CPU6502::getX() const
{
    return m_X;
}

void CPU6502::setX(uint8_t value)
{
    m_X = value;
}

uint8_t CPU6502::getY() const
{
    return m_Y;
}

void CPU6502::setY(uint8_t value)
{
    m_Y = value;
}

uint8_t CPU6502::getP() const
{
    return m_P;
}

void CPU6502::setP(uint8_t value)
{
    m_P = value;
}

uint8_t CPU6502::getSP() const
{
    return m_SP;
}

void CPU6502::setSP(uint8_t value)
{
    m_SP = value;
}

uint16_t CPU6502::getPC() const
{
    return m_PC;
}

void CPU6502::setPC(uint16_t value)
{
    m_PC = value;
}

uint32_t CPU6502::getCycles() const
{
    return m_cycles;
}

void CPU6502::setCycles(uint32_t value)
{
    m_cycles = value;
}

uint8_t CPU6502::getRAM(uint16_t address) const
{
    return m_RAM[address];
}

void CPU6502::setRAM(uint16_t address, uint8_t value)
{
    m_RAM[address] = value;
}

void CPU6502::writeMemory(uint16_t address, uint8_t value)
{
    if (address >= ppu->registers.PPUCTRL && address <= 0x3FFF)
    {
        uint16_t reg = 0x2000 + (address % 8);
        ppu->writeRegister(reg, value);
        return;
    }

    setRAM(address, value);
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

    return getRAM(address);
}

void CPU6502::setStatus(uint8_t status)
{
    m_P = status;
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
