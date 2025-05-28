#include "CPU/CPU6502.h"

#include <fstream>
#include <iomanip>

#include "Bus/Bus.h"

CPU6502::CPU6502() {
    setA(0);
    setX(0);
    setY(0);
    setP(0);
    setSP(0xFF);
    setPC(0x0000);
    std::memset(m_RAM, 0, sizeof(m_RAM));
}

void CPU6502::reset() {
    uint16_t low = bus->read(0xFFFC);
    uint16_t high = bus->read(0xFFFD);
    uint16_t startPC = ((high << 8) | low) - 0x4;

    setPC(startPC);
    setA(0);
    setX(0);
    setY(0);
    setSP(0xFD);
    setP(0x24);

    printf("[SYSTEM] CPU reset successfully!\nPC: $%04X | A: 0x%02X | X: 0x%02X | Y: 0x%02X | SP: 0x%02X | P: 0x%02X\n\n", startPC, getA(), getX(), getY(), getSP(), getP());
}

bool CPU6502::getFlag(uint8_t flag) {
    return (m_P & flag) != 0;
}

void CPU6502::triggerNMI() {
    bus->write(0x0100 + m_SP--, (m_PC >> 8) & 0xFF);
    bus->write(0x0100 + m_SP--, m_PC & 0xFF);

    setFlag(FLAG_BREAK, false);
    setFlag(FLAG_UNKNOW, true);
    bus->write(0x0100 + m_SP--, m_P);

    setFlag(FLAG_INTERRUPT, true);

    uint16_t lo = bus->read(0xFFFA);
    uint16_t hi = bus->read(0xFFFB);
    m_PC = (hi << 8) | lo;

    m_cycles = 7;
}

void CPU6502::updateZNFlags(uint8_t value) {
    setFlag(FLAG_ZERO, value == 0);
    setFlag(FLAG_NEGATIVE, value & 0x80);
}

uint8_t CPU6502::popStack() {
    m_SP++;
    uint8_t val = bus->read(0x100 + m_SP);
    return val;
}

uint8_t CPU6502::pullStack() {
    return bus->read(0x100 | ++m_SP);
}

void CPU6502::pushToStack(uint8_t value) {
    bus->write(0x0100 + m_SP, value);
    m_SP--;
}

void CPU6502::pushToStack16(uint16_t value) {
    pushToStack((value >> 8) & 0xFF);
    pushToStack(value & 0xFF);
}

bool CPU6502::isNegativeFlagClean() {
    return !(m_P & 0x80);
}

void CPU6502::writeMemory(uint16_t address, uint8_t value) {
    bus->write(address, value);
}

void CPU6502::clock(JITCompiler &jit) {
    m_cycles--;
}

uint8_t CPU6502::readMemory(uint16_t address) {
    return bus->read(address);
}

void CPU6502::setStatus(uint8_t status) {
    setP(status);
}

void CPU6502::setFlag(uint8_t flag, bool value) {
    if (value)
        m_P |= flag;
    else
        m_P &= ~flag;
}

bool CPU6502::isFlagSet(uint8_t flag) const {
    return m_P & flag;
}

void CPU6502::setStatusRegister(uint8_t status) {
    m_P = status;

    setFlag(FLAG_CARRY, (status & FLAG_CARRY) != 0);
    setFlag(FLAG_ZERO, (status & FLAG_ZERO) != 0);
    setFlag(FLAG_INTERRUPT, (status & FLAG_INTERRUPT) != 0);
    setFlag(FLAG_DECIMAL, (status & FLAG_DECIMAL) != 0);
    setFlag(FLAG_BREAK, (status & FLAG_BREAK) != 0);
    setFlag(FLAG_OVERFLOW, (status & FLAG_OVERFLOW) != 0);
    setFlag(FLAG_NEGATIVE, (status & FLAG_NEGATIVE) != 0);
}

void CPU6502::step(JITCompiler &jit) {
    uint8_t opcode = bus->read(m_PC);
    jit.compileOpcode(opcode, *this);
}
