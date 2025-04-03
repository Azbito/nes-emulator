#include "Assembly/Instructions.h"
#include <iostream>

std::unordered_map<uint8_t, std::string> Instructions::opcodeMap = {
    {0xA9, "LDA"}, {0xA5, "LDA"}, {0xB5, "LDA"}, {0xAD, "LDA"}, {0xBD, "LDA"},
    {0xB9, "LDA"}, {0xA1, "LDA"}, {0xB1, "LDA"}, {0xA2, "LDX"}, {0xA6, "LDX"},
    {0xB6, "LDX"}, {0xAE, "LDX"}, {0xBE, "LDX"}, {0xA0, "LDY"}, {0xA4, "LDY"},
    {0xB4, "LDY"}, {0xAC, "LDY"}, {0xBC, "LDY"}, {0x85, "STA"}, {0x95, "STA"},
    {0x8D, "STA"}, {0x9D, "STA"}, {0x99, "STA"}, {0x81, "STA"}, {0x91, "STA"},
    {0x86, "STX"}, {0x96, "STX"}, {0x8E, "STX"}, {0x84, "STY"}, {0x94, "STY"},
    {0x8C, "STY"},

    {0x69, "ADC"}, {0x65, "ADC"}, {0x75, "ADC"}, {0x6D, "ADC"}, {0x7D, "ADC"},
    {0x79, "ADC"}, {0x61, "ADC"}, {0x71, "ADC"}, {0xE9, "SBC"}, {0xE5, "SBC"},
    {0xF5, "SBC"}, {0xED, "SBC"}, {0xFD, "SBC"}, {0xF9, "SBC"}, {0xE1, "SBC"},
    {0xF1, "SBC"},

    {0x29, "AND"}, {0x25, "AND"}, {0x35, "AND"}, {0x2D, "AND"}, {0x3D, "AND"},
    {0x39, "AND"}, {0x21, "AND"}, {0x31, "AND"}, {0x09, "ORA"}, {0x05, "ORA"},
    {0x15, "ORA"}, {0x0D, "ORA"}, {0x1D, "ORA"}, {0x19, "ORA"}, {0x01, "ORA"},
    {0x11, "ORA"}, {0x49, "EOR"}, {0x45, "EOR"}, {0x55, "EOR"}, {0x4D, "EOR"},
    {0x5D, "EOR"}, {0x59, "EOR"}, {0x41, "EOR"}, {0x51, "EOR"},

    {0x0A, "ASL"}, {0x06, "ASL"}, {0x16, "ASL"}, {0x0E, "ASL"}, {0x1E, "ASL"},
    {0x4A, "LSR"}, {0x46, "LSR"}, {0x56, "LSR"}, {0x4E, "LSR"}, {0x5E, "LSR"},
    {0x2A, "ROL"}, {0x26, "ROL"}, {0x36, "ROL"}, {0x2E, "ROL"}, {0x3E, "ROL"},
    {0x6A, "ROR"}, {0x66, "ROR"}, {0x76, "ROR"}, {0x6E, "ROR"}, {0x7E, "ROR"},

    {0xE6, "INC"}, {0xF6, "INC"}, {0xEE, "INC"}, {0xFE, "INC"}, {0xE8, "INX"},
    {0xC8, "INY"}, {0xC6, "DEC"}, {0xD6, "DEC"}, {0xCE, "DEC"}, {0xDE, "DEC"},
    {0xCA, "DEX"}, {0x88, "DEY"},

    {0xC9, "CMP"}, {0xC5, "CMP"}, {0xD5, "CMP"}, {0xCD, "CMP"}, {0xDD, "CMP"},
    {0xD9, "CMP"}, {0xC1, "CMP"}, {0xD1, "CMP"}, {0xE0, "CPX"}, {0xE4, "CPX"},
    {0xEC, "CPX"}, {0xC0, "CPY"}, {0xC4, "CPY"}, {0xCC, "CPY"},

    {0x90, "BCC"}, {0xB0, "BCS"}, {0xF0, "BEQ"}, {0x30, "BMI"}, {0xD0, "BNE"},
    {0x10, "BPL"}, {0x50, "BVC"}, {0x70, "BVS"},

    {0x4C, "JMP"}, {0x6C, "JMP"}, {0x20, "JSR"}, {0x60, "RTS"}, {0x40, "RTI"},

    {0x18, "CLC"}, {0xD8, "CLD"}, {0x58, "CLI"}, {0xB8, "CLV"}, {0x38, "SEC"},
    {0xF8, "SED"}, {0x78, "SEI"},

    {0x48, "PHA"}, {0x08, "PHP"}, {0x68, "PLA"}, {0x28, "PLP"},

    {0xAA, "TAX"}, {0xA8, "TAY"}, {0xBA, "TSX"}, {0x8A, "TXA"}, {0x9A, "TXS"},
    {0x98, "TYA"},

    {0x00, "BRK"}, {0xEA, "NOP"}, {0x24, "BIT"}, {0x2C, "BIT"},

};

void Instructions::handleBPL(CPU6502 &cpu)
{
    int8_t offset = cpu.readMemory(cpu.PC + 1);

    if (offset < -10 || offset > 10)
    {
        std::cout << "Limiting offset to avoid infinite loop" << std::endl;
        offset = 0;
    }

    if (cpu.isNegativeFlagClean())
    {
        cpu.PC += 2 + offset;
        return;
    }

    cpu.PC += 2;
}

void Instructions::handleAbsXLDA(CPU6502 &cpu)
{
    uint16_t address = fetchAbsoluteX(cpu);
    uint8_t value = cpu.readMemory(address);
    cpu.A = value;
    cpu.updateZNFlags(cpu.A);
    cpu.PC += 3;
}

void Instructions::handleImmLDY(CPU6502 &cpu)
{
    uint8_t value = fetchImmediate(cpu);
    cpu.Y = value;
    cpu.updateZNFlags(cpu.Y);
    cpu.PC += 2;
}

void Instructions::handleDEX(CPU6502 &cpu)
{
    cpu.X--;
    cpu.updateZNFlags(cpu.X);
    cpu.PC++;
}

void Instructions::handleImmCMP(CPU6502 &cpu)
{
    uint8_t value = cpu.readMemory(cpu.PC + 1);
    uint8_t result = cpu.A - value;

    cpu.setFlag(cpu.C, cpu.A >= value);
    cpu.setFlag(cpu.Z, result == 0);
    cpu.setFlag(cpu.N, result & 0x80);

    cpu.PC += 2;
}

void Instructions::handleRelBCS(CPU6502 &cpu)
{
    int16_t newPC = fetchRelative(cpu);

    if (cpu.isFlagSet(cpu.C))
    {
        cpu.PC = newPC;
    }
    else
    {
        cpu.PC += 2;
    }
}

void Instructions::handleISCAbsoluteX(CPU6502 &cpu)
{

    uint16_t address = fetchAbsoluteAddress(cpu) + cpu.X;

    uint8_t value = cpu.readMemory(address);
    value--;
    cpu.writeMemory(address, value);

    uint8_t result = cpu.A + value + (cpu.P & 0x01);

    cpu.P &= ~0x01;
    if (result & 0x80)
    {
        cpu.P |= 0x80;
    }
    else
    {
        cpu.P &= ~0x80;
    }

    if (result == 0)
    {
        cpu.P |= 0x02;
    }
    else
    {
        cpu.P &= ~0x02;
    }

    if (((cpu.A ^ value) & (cpu.A ^ result) & 0x80))
    {
        cpu.P |= 0x40;
    }
    else
    {
        cpu.P &= ~0x40;
    }

    if (result < cpu.A)
    {
        cpu.P |= 0x01;
    }
    else
    {
        cpu.P &= ~0x01;
    }

    cpu.A = result;
    cpu.PC += 3;
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
    uint8_t value = cpu.readMemory(address);
    cpu.A = value;
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
