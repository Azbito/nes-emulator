#include "Assembly/Instructions.h"
#include <iostream>

void Instructions::handleBPL(CPU6502 &cpu)
{
    if (cpu.isNegativeFlagClean())
    {
        int8_t offset = static_cast<int8_t>(cpu.readMemory(cpu.PC + 1));
        cpu.PC += offset;
    }
    cpu.PC += 2;
}

void Instructions::handleADC(CPU6502 &cpu)
{
    uint8_t value = fetchImmediate(cpu);
    cpu.A += value;
    cpu.PC += 2;
}

void Instructions::handleBRK(CPU6502 &cpu)
{
    cpu.pushToStack16(cpu.PC + 2);
    cpu.pushToStack(cpu.P);
    cpu.P |= 0x10;
    cpu.PC = (cpu.readMemory(0xFFFF) << 8) | cpu.readMemory(0xFFFE);
}

void Instructions::handleORAAbsoluteY(CPU6502 &cpu)
{
    uint16_t address = fetchAbsoluteAddress(cpu) + cpu.Y;
    uint8_t value = cpu.readMemory(address);
    cpu.A |= value;
    cpu.PC += 3;
}

void Instructions::handleNOP(CPU6502 &cpu)
{
    cpu.PC += 1;
}

void Instructions::handleNOPIMM(CPU6502 &cpu)
{
    fetchImmediate(cpu);
    cpu.PC += 2;
}

void Instructions::handleNOPAbsoluteX(CPU6502 &cpu)
{
    uint16_t addr = fetchAbsoluteAddress(cpu) + cpu.X;
    cpu.PC += 3;
}

void Instructions::handleASLAbsoluteX(CPU6502 &cpu)
{
    uint16_t addr = fetchAbsoluteAddress(cpu) + cpu.X;
    uint8_t value = cpu.readMemory(addr);
    uint8_t result = value << 1;

    cpu.P = (value & 0x80) ? cpu.P | 0x01 : cpu.P & ~0x01;
    cpu.P = (result == 0) ? cpu.P | 0x02 : cpu.P & ~0x02;

    cpu.RAM[addr] = result;
    cpu.PC += 3;
}

void Instructions::handleEORZP(CPU6502 &cpu)
{
    uint8_t address = fetchZeroPage(cpu);
    uint8_t operand = cpu.readMemory(address);
    cpu.A ^= operand;
    cpu.updateZNFlags(cpu.A);
    cpu.PC += 2;
}

void Instructions::handleTXS(CPU6502 &cpu)
{
    cpu.SP = cpu.X;
    cpu.PC += 1;
}

void Instructions::handleLDAAbsolute(CPU6502 &cpu)
{
    uint16_t address = fetchAbsoluteAddress(cpu);
    cpu.A = cpu.readMemory(address);
    cpu.updateZNFlags(cpu.A);
    cpu.PC += 3;
}

void Instructions::handleLDXImmediate(CPU6502 &cpu)
{
    uint8_t value = fetchImmediate(cpu);
    cpu.X = value;
    cpu.updateZNFlags(cpu.X);
    cpu.PC += 2;
}

void Instructions::handleSTA(CPU6502 &cpu)
{
    uint16_t address = fetchAbsoluteAddress(cpu);
    cpu.writeMemory(address, cpu.A);
    cpu.PC += 3;
}

void Instructions::handleKIL(CPU6502 &cpu)
{
    printf("I'm dead x.x");
}

void Instructions::handleCLD(CPU6502 &cpu)
{
    cpu.P &= ~0x08;
    cpu.PC++;
}

void Instructions::handleSEI(CPU6502 &cpu)
{
    cpu.P |= 0x04;
    cpu.PC++;
}

void Instructions::handleLSRAbsolute(CPU6502 &cpu)
{
    uint16_t addr = fetchAbsoluteAddress(cpu);
    uint8_t value = cpu.readMemory(addr);
    uint8_t carry = value & 0x01;
    value >>= 1;

    cpu.P = (carry) ? cpu.P | 0x01 : cpu.P & ~0x01;
    cpu.P = (value == 0) ? cpu.P | 0x02 : cpu.P & ~0x02;
    cpu.P &= ~0x80;

    cpu.RAM[addr] = value;
    cpu.PC += 3;
}

void Instructions::handleORAIndirectIndexedX(CPU6502 &cpu)
{
    uint16_t baseAddr = fetchZeroPage(cpu);
    uint16_t addr = (cpu.readMemory(baseAddr + cpu.X) |
                     (cpu.readMemory(baseAddr + cpu.X + 1) << 8));
    uint8_t value = cpu.readMemory(addr);
    cpu.A |= value;
    cpu.updateZNFlags(cpu.A);
    cpu.PC += 2;
}

void Instructions::handleSREIndirectIndexed(CPU6502 &cpu)
{
    uint16_t addr = fetchIndirect(cpu) + cpu.Y;
    uint8_t value = cpu.readMemory(addr);

    uint8_t carry = value & 0x01;
    value >>= 1;
    value |= (cpu.P & 0x01) << 7;

    cpu.P = (carry) ? cpu.P | 0x01 : cpu.P & ~0x01;

    cpu.A ^= value;
    cpu.updateZNFlags(cpu.A);
    cpu.RAM[addr] = value;
    cpu.PC += 3;
}

void Instructions::handleLDA(CPU6502 &cpu)
{
    cpu.A = fetchImmediate(cpu);
    cpu.updateZNFlags(cpu.A);
    cpu.PC += 2;
}
