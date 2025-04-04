#include "Assembly/Instructions.h"

uint8_t Instructions::fetchImmediate(CPU6502 &cpu)
{
    return cpu.readMemory(cpu.PC + 1);
}

uint16_t Instructions::fetchWord(CPU6502 &cpu)
{
    uint8_t lo = cpu.readMemory(cpu.PC + 1);
    uint8_t hi = cpu.readMemory(cpu.PC + 2);
    return (hi << 8) | lo;
}

uint8_t Instructions::fetchZeroPage(CPU6502 &cpu)
{
    return cpu.readMemory(cpu.readMemory(cpu.PC + 1));
}

uint8_t Instructions::fetchZeroPageX(CPU6502 &cpu)
{
    return cpu.readMemory((cpu.readMemory(cpu.PC + 1) + cpu.X) & 0xFF);
}

uint8_t Instructions::fetchZeroPageY(CPU6502 &cpu)
{
    return cpu.readMemory((cpu.readMemory(cpu.PC + 1) + cpu.Y) & 0xFF);
}

uint8_t Instructions::fetchAbsolute(CPU6502 &cpu)
{
    return cpu.readMemory(fetchAbsoluteAddress(cpu));
}

uint8_t Instructions::fetchAbsoluteX(CPU6502 &cpu)
{
    return cpu.readMemory(fetchAbsoluteAddress(cpu) + cpu.X);
}

uint8_t Instructions::fetchAbsoluteY(CPU6502 &cpu)
{
    return cpu.readMemory(fetchAbsoluteAddress(cpu) + cpu.Y);
}

uint16_t Instructions::fetchIndirect(CPU6502 &cpu)
{
    uint16_t addr = fetchAbsoluteAddress(cpu);
    return cpu.readMemory(addr) | (cpu.readMemory(addr + 1) << 8);
}

int16_t Instructions::fetchRelative(CPU6502 &cpu)
{
    int8_t offset = static_cast<int8_t>(cpu.readMemory(cpu.PC + 1));
    return cpu.PC + 2 + offset;
}

uint8_t Instructions::fetchIndexedIndirectX(CPU6502 &cpu)
{
    uint16_t baseAddr = cpu.readMemory(cpu.PC + 1);
    uint16_t addr = (cpu.readMemory(baseAddr + cpu.X) |
                     (cpu.readMemory(baseAddr + cpu.X + 1) << 8));
    return cpu.readMemory(addr);
}

uint8_t Instructions::fetchIndirectIndexedY(CPU6502 &cpu)
{
    uint16_t zpAddr = cpu.readMemory(cpu.PC + 1);
    uint16_t low = cpu.readMemory(zpAddr);
    uint16_t high = cpu.readMemory((zpAddr + 1) & 0xFF);
    uint16_t addr = (high << 8) | low;
    addr += cpu.Y;

    return cpu.readMemory(addr);
}

uint16_t Instructions::fetchAbsoluteAddress(CPU6502 &cpu)
{
    return cpu.readMemory(cpu.PC + 1) | (cpu.readMemory(cpu.PC + 2) << 8);
}
