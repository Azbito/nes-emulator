#include "Assembly/Instructions.h"

#include <iostream>

#include "Bus/Bus.h"
#include "CPU/CPU6502.h"

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

std::string Instructions::getOpcodeName(uint8_t opcode) {
    auto it = opcodeMap.find(opcode);
    if (it != opcodeMap.end()) {
        return it->second;
    }

    return "Unknown";
}

void Instructions::handleBPL(CPU6502 &cpu, Bus &bus) {
    int8_t offset = static_cast<int8_t>(bus.read(cpu.getPC() + 1));

    cpu.setCycles(cpu.getCycles() + 2);

    cpu.setPC(cpu.getPC() + 2);

    if (!cpu.getFlag(cpu.FLAG_NEGATIVE)) {
        cpu.setCycles(cpu.getCycles() + 1);

        uint16_t newPC = cpu.getPC() + offset;

        if ((cpu.getPC() & 0xFF00) != (newPC & 0xFF00)) {
            cpu.setCycles(cpu.getCycles() + 1);
        }

        cpu.setPC(newPC);
    }
}
void Instructions::handleAbsXLDA(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    uint8_t low = bus.read(pc + 1);
    uint8_t high = bus.read(pc + 2);
    uint16_t baseAddress = (high << 8) | low;
    uint16_t address = baseAddress + cpu.getX();

    uint8_t value = bus.read(address);
    cpu.setA(value);
    cpu.updateZNFlags(cpu.getA());

    int cycles = 4;
    if ((address & 0xFF00) != (baseAddress & 0xFF00)) {
        cycles += 1;
    }
    cpu.setCycles(cpu.getCycles() + cycles);

    cpu.setPC(pc + 3);
}

void Instructions::handleImmLDY(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchImmediate(cpu, bus);
    cpu.setY(value);
    cpu.updateZNFlags(cpu.getY());
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleDEX(CPU6502 &cpu, Bus &bus) {
    cpu.setX(cpu.getX() - 1);
    cpu.updateZNFlags(cpu.getX());
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleBNE(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    int8_t offset = static_cast<int8_t>(bus.read(pc + 1));
    uint16_t nextPC = pc + 2;
    int cycles = 2;

    if (!cpu.isFlagSet(cpu.FLAG_ZERO)) {
        cycles += 1;
        uint16_t target = nextPC + offset;

        if ((target & 0xFF00) != (nextPC & 0xFF00)) {
            cycles += 1;
        }

        nextPC = target;
    }

    cpu.setCycles(cpu.getCycles() + cycles);
    cpu.setPC(nextPC);
}

void Instructions::handleZeroPageSTA(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchZeroPage(cpu, bus);
    bus.write(address, cpu.getA());
    cpu.setCycles(cpu.getCycles() + 3);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleZeroPageSTX(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchZeroPage(cpu, bus);
    bus.write(address, cpu.getX());
    cpu.setCycles(cpu.getCycles() + 3);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleAbsoluteSTX(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus);
    bus.write(address, cpu.getX());
    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleAbsoluteSTY(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus);
    bus.write(address, cpu.getY());
    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleDEY(CPU6502 &cpu, Bus &bus) {
    cpu.setY(cpu.getY() - 1);
    cpu.updateZNFlags(cpu.getY());
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleIndirectYSTA(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchIndirectIndexedY(cpu, bus);
    bus.write(address, cpu.getA());

    cpu.setCycles(cpu.getCycles() + 6);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleRelBCC(CPU6502 &cpu, Bus &bus) {
    int8_t offset = fetchImmediate(cpu, bus);

    if (!cpu.getFlag(cpu.FLAG_CARRY)) {
        cpu.setCycles(cpu.getCycles() + 1);
        cpu.setPC(cpu.getPC() + offset);
        return;
    }

    cpu.setCycles(cpu.getCycles() + 2);
}

void Instructions::handleRTS(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.pullStack();
    pc |= (cpu.pullStack() << 8);
    cpu.setPC(pc + 1);
    cpu.setCycles(cpu.getCycles() + 6);
}

void Instructions::handleImmCPY(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchImmediate(cpu, bus);
    uint8_t result = cpu.getY() - value;

    cpu.setFlag(cpu.FLAG_CARRY, cpu.getY() >= value);
    cpu.setFlag(cpu.FLAG_ZERO, result == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleImmCPX(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchImmediate(cpu, bus);
    uint8_t result = cpu.getX() - value;

    cpu.setFlag(cpu.FLAG_CARRY, cpu.getX() >= value);
    cpu.setFlag(cpu.FLAG_ZERO, result == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleAbsBIT(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchAbsolute(cpu, bus);
    uint8_t value = bus.read(address);

    cpu.setFlag(cpu.FLAG_ZERO, (cpu.getA() & value) == 0);

    cpu.setFlag(cpu.FLAG_OVERFLOW, value & cpu.FLAG_OVERFLOW);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & cpu.FLAG_NEGATIVE);

    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleAbsoluteYSTA(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus) + cpu.getY();
    bus.write(address, cpu.getA());
    cpu.setCycles(cpu.getCycles() + 5);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleImmediateLDX(CPU6502 &cpu, Bus &bus) {
    uint8_t value = bus.read(cpu.getPC() + 1);
    cpu.setX(value);
    cpu.updateZNFlags(value);

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleAbsoluteINC(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus);
    uint8_t value = bus.read(address);
    value++;
    bus.write(address, value);
    cpu.updateZNFlags(value);
    cpu.setCycles(cpu.getCycles() + 6);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleSTAAbsolute(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    uint8_t low = bus.read(pc + 1);
    uint8_t high = bus.read(pc + 2);

    uint16_t address = (high << 8) | low;

    bus.write(address, cpu.getA());

    cpu.setPC(cpu.getPC() + 3);
    cpu.setCycles(cpu.getCycles() + 4);
}

void Instructions::handleSEP(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    uint8_t data = bus.read(pc + 1);

    cpu.setStatus(cpu.getP() | data);

    cpu.setCycles(cpu.getCycles() + 2);

    cpu.setPC(pc + 2);
}

void Instructions::handleDECAbsolute(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    uint8_t low = bus.read(pc + 1);
    uint8_t high = bus.read(pc + 2);

    uint16_t address = (high << 8) | low;

    uint8_t value = bus.read(address);

    value--;

    bus.write(address, value);

    cpu.setCycles(cpu.getCycles() + 6);

    cpu.setPC(pc + 3);
}

void Instructions::handleAbsoluteJMPIndirect(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    uint8_t low = bus.read(pc + 1);
    uint8_t high = bus.read(pc + 2);

    uint16_t pointer = (high << 8) | low;

    uint8_t lowDest = bus.read(pointer);
    uint8_t highDest = bus.read(pointer + 1);

    uint16_t address = (highDest << 8) | lowDest;

    cpu.setPC(address);
    cpu.setCycles(cpu.getCycles() + 5);
}

void Instructions::handleAbsoluteJMP(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    uint8_t low = bus.read(pc + 1);
    uint8_t high = bus.read(pc + 2);

    uint16_t address = (high << 8) | low;

    cpu.setPC(address);
    cpu.setCycles(cpu.getCycles() + 3);
}

void Instructions::handleDECZeroPageX(CPU6502 &cpu, Bus &bus) {
    uint8_t addr = (bus.read(cpu.getPC() + 1) + cpu.getX()) & 0xFF;

    uint8_t value = bus.read(addr);
    value--;

    bus.write(addr, value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setPC(cpu.getPC() + 2);
    cpu.setCycles(cpu.getCycles() + 6);
}

void Instructions::handleSBCZeroPage(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchZeroPage(cpu, bus);
    uint8_t carry = cpu.getFlag(cpu.FLAG_CARRY) ? 0 : 1;

    uint16_t result = static_cast<uint16_t>(cpu.getA()) - value - carry;

    bool overflow =
        ((cpu.getA() ^ value) & 0x80) && ((cpu.getA() ^ result) & 0x80);

    cpu.setFlag(cpu.FLAG_CARRY, result < 0x100);
    cpu.setFlag(cpu.FLAG_ZERO, (result & 0xFF) == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);
    cpu.setFlag(cpu.FLAG_OVERFLOW, overflow);

    cpu.setA(result & 0xFF);
    cpu.setPC(cpu.getPC() + 2);
    cpu.setCycles(cpu.getCycles() + 3);
}

void Instructions::handleTSX(CPU6502 &cpu, Bus &bus) {
    uint8_t value = cpu.getSP();
    cpu.setX(value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setPC(cpu.getPC() + 1);
    cpu.setCycles(cpu.getCycles() + 2);
}

void Instructions::handleASLAccumulator(CPU6502 &cpu, Bus &bus) {
    uint8_t value = cpu.getA();

    cpu.setFlag(cpu.FLAG_CARRY, value & 0x80);

    value <<= 1;
    cpu.setA(value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setPC(cpu.getPC() + 1);

    cpu.setCycles(cpu.getCycles() + 2);
}

void Instructions::handleSED(CPU6502 &cpu, Bus &bus) {
    cpu.setFlag(cpu.FLAG_DECIMAL, true);

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleAND(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchImmediate(cpu, bus);
    cpu.setA(cpu.getA() & value);
    cpu.updateZNFlags(cpu.getA());
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleZeroPageLDA(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchZeroPage(cpu, bus);

    uint8_t value = bus.read(address);
    cpu.setA(value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setCycles(cpu.getCycles() + 3);

    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleTYA(CPU6502 &cpu, Bus &bus) {
    cpu.setA(cpu.getY());

    cpu.setFlag(cpu.FLAG_ZERO, cpu.getA() == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, cpu.getA() & 0x80);

    cpu.setCycles(cpu.getCycles() + 2);

    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handlePHA(CPU6502 &cpu, Bus &bus) {
    bus.write(0x0100 + cpu.getSP(), cpu.getA());

    cpu.setSP(cpu.getSP() - 1);

    cpu.setCycles(cpu.getCycles() + 3);

    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleZeroPageDEC(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchZeroPage(cpu, bus);

    uint8_t value = bus.read(address);

    value--;

    bus.write(address, value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setCycles(cpu.getCycles() + 5);

    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handlePLA(CPU6502 &cpu, Bus &bus) {
    uint8_t value = bus.read(0x100 + cpu.getSP());

    cpu.setA(value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setSP(cpu.getSP() + 1);
    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleLDAIndirectIndexedY(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchIndirectIndexedY(cpu, bus);

    cpu.setA(value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setCycles(cpu.getCycles() + 5);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleLDXZeroPage(CPU6502 &cpu, Bus &bus) {
    uint8_t addr = bus.read(cpu.getPC() + 1);

    uint8_t value = bus.read(addr);

    cpu.setX(value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setCycles(cpu.getCycles() + 3);

    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleADCZeroPage(CPU6502 &cpu, Bus &bus) {
    uint8_t addr = bus.read(cpu.getPC() + 1);

    uint8_t operand = bus.read(addr);

    uint16_t result = cpu.getA() + operand + cpu.isFlagSet(cpu.FLAG_CARRY);

    cpu.setA(result & 0xFF);

    cpu.setFlag(cpu.FLAG_CARRY, result > 0xFF);
    cpu.setFlag(cpu.FLAG_ZERO, (result & 0xFF) == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);
    cpu.setFlag(cpu.FLAG_OVERFLOW,
                ((cpu.getA() ^ operand) & (cpu.getA() ^ result) & 0x80) != 0);
    cpu.setCycles(cpu.getCycles() + 3);

    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleCLC(CPU6502 &cpu, Bus &bus) {
    cpu.setFlag(cpu.FLAG_CARRY, false);

    cpu.setCycles(cpu.getCycles() + 2);

    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleTAX(CPU6502 &cpu, Bus &bus) {
    uint8_t value = cpu.getA();
    cpu.setX(value);

    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & 0x80);

    cpu.setCycles(cpu.getCycles() + 2);

    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleLSRA(CPU6502 &cpu, Bus &bus) {
    uint8_t value = cpu.getA();

    bool carry = value & 0x01;

    value >>= 1;

    cpu.setA(value);

    cpu.setFlag(cpu.FLAG_CARRY, carry);
    cpu.setFlag(cpu.FLAG_ZERO, value == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, false);

    cpu.setCycles(cpu.getCycles() + 2);

    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleZeroPageAND(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchZeroPage(cpu, bus);

    uint8_t value = bus.read(address);

    uint8_t result = cpu.getA() & value;

    cpu.setA(result);

    cpu.setFlag(cpu.FLAG_ZERO, result == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);

    cpu.setCycles(cpu.getCycles() + 3);

    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleZeroPageSTY(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchZeroPage(cpu, bus);

    bus.write(address, cpu.getY());

    cpu.setCycles(cpu.getCycles() + 3);

    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleRelativeBEQ(CPU6502 &cpu, Bus &bus) {
    int8_t offset = static_cast<int8_t>(bus.read(cpu.getPC() + 1));
    uint16_t newPC = cpu.getPC() + 2;

    if (cpu.isFlagSet(cpu.FLAG_ZERO)) {
        newPC += offset;
        cpu.setCycles(cpu.getCycles() +
                      ((newPC & 0xFF00) != (cpu.getPC() & 0xFF00) ? 2 : 1));
    }

    cpu.setPC(newPC);
    cpu.setCycles(cpu.getCycles() + 2);
}

void Instructions::handleORA(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchImmediate(cpu, bus);
    cpu.setA(cpu.getA() | value);
    cpu.updateZNFlags(cpu.getA());

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleINX(CPU6502 &cpu, Bus &bus) {
    cpu.setX(cpu.getX() + 1);
    cpu.updateZNFlags(cpu.getX());

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleINY(CPU6502 &cpu, Bus &bus) {
    cpu.setY(cpu.getY() + 1);
    cpu.updateZNFlags(cpu.getY());

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleZeroPageBIT(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchZeroPage(cpu, bus);
    uint8_t value = bus.read(address);

    cpu.setFlag(cpu.FLAG_ZERO, (cpu.getA() & value) == 0);

    cpu.setFlag(cpu.FLAG_OVERFLOW, value & cpu.FLAG_OVERFLOW);
    cpu.setFlag(cpu.FLAG_NEGATIVE, value & cpu.FLAG_NEGATIVE);

    cpu.setCycles(cpu.getCycles() + 3);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleLDYAbsoluteX(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus);
    uint8_t value = bus.read(address + cpu.getX());
    cpu.setY(value);
    cpu.updateZNFlags(cpu.getY());
    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleZeroPageXSTA(CPU6502 &cpu, Bus &bus) {
    uint16_t addr = fetchZeroPageX(cpu, bus);
    bus.write(addr, cpu.getA());
    cpu.setCycles(cpu.getCycles() + 3);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleJSR(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    uint16_t targetAddr = fetchAbsoluteAddress(cpu, bus);

    uint16_t returnAddr = pc + 2;

    cpu.pushToStack((returnAddr >> 8) & 0xFF);
    cpu.pushToStack(returnAddr & 0xFF);

    cpu.setPC(targetAddr);
    cpu.setCycles(cpu.getCycles() + 6);
}

void Instructions::handleAbsCMP(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsolute(cpu, bus);
    uint8_t value = bus.read(address);

    uint8_t result = cpu.getA() - value;

    cpu.setFlag(cpu.FLAG_CARRY, cpu.getA() >= value);
    cpu.setFlag(cpu.FLAG_ZERO, result == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);

    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleImmCMP(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchImmediate(cpu, bus);
    uint8_t result = cpu.getA() - value;

    cpu.setFlag(cpu.FLAG_CARRY, cpu.getA() >= value);
    cpu.setFlag(cpu.FLAG_ZERO, result == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleRelBCS(CPU6502 &cpu, Bus &bus) {
    int16_t newPC = fetchRelative(cpu, bus);

    if (cpu.getFlag(cpu.FLAG_CARRY)) {
        cpu.setCycles(cpu.getCycles() + 1);
        cpu.setPC(newPC);
        return;
    }

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleISCAbsoluteX(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus) + cpu.getX();
    uint8_t value = bus.read(address);
    value++;
    bus.write(address, value);

    uint8_t carry = cpu.getFlag(cpu.FLAG_CARRY) ? 0 : 1;
    uint16_t result = cpu.getA() - value - carry;

    cpu.setFlag(cpu.FLAG_CARRY, result < 0x100);
    cpu.setFlag(cpu.FLAG_ZERO, (result & 0xFF) == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);
    cpu.setFlag(cpu.FLAG_OVERFLOW,
                ((cpu.getA() ^ value) & (cpu.getA() ^ result) & 0x80));

    cpu.setA(result & 0xFF);
    cpu.setCycles(cpu.getCycles() + 7);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleADC(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchImmediate(cpu, bus);
    uint16_t result =
        cpu.getA() + value + (cpu.getFlag(cpu.FLAG_CARRY) ? 1 : 0);

    cpu.setFlag(cpu.FLAG_CARRY, result > 0xFF);
    cpu.setFlag(cpu.FLAG_ZERO, (result & 0xFF) == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);
    cpu.setFlag(cpu.FLAG_OVERFLOW,
                (~(cpu.getA() ^ value) & (cpu.getA() ^ result) & 0x80));

    cpu.setA(result & 0xFF);
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleBRK(CPU6502 &cpu, Bus &bus) {
    cpu.pushToStack16(cpu.getPC() + 2);
    cpu.pushToStack(cpu.getP());
    cpu.setP(cpu.getP() | 0x10);
    cpu.setPC((bus.read(0xFFFF) << 8) | bus.read(0xFFFE));
    cpu.setCycles(cpu.getCycles() + 7);
}

void Instructions::handleORAAbsoluteY(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus) + cpu.getY();
    uint8_t value = bus.read(address);
    cpu.setA(cpu.getA() | value);
    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleNOP(CPU6502 &cpu, Bus &bus) {
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleNOPIMM(CPU6502 &cpu, Bus &bus) {
    fetchImmediate(cpu, bus);
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleLDXIndirectY(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchIndirectIndexedY(cpu, bus);

    cpu.setX(value);
    cpu.updateZNFlags(cpu.getX());
    cpu.setCycles(cpu.getCycles() + 5);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleLDXAbsolute(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus);
    uint8_t value = bus.read(address);

    cpu.setX(value);
    cpu.updateZNFlags(cpu.getX());
    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleRTI(CPU6502 &cpu, Bus &bus) {
    uint8_t flags = cpu.popStack();

    cpu.setFlag(cpu.FLAG_NEGATIVE, (flags & 0x80) != 0);
    cpu.setFlag(cpu.FLAG_OVERFLOW, (flags & 0x40) != 0);
    cpu.setFlag(cpu.FLAG_DECIMAL, (flags & 0x08) != 0);
    cpu.setFlag(cpu.FLAG_INTERRUPT, (flags & 0x04) != 0);
    cpu.setFlag(cpu.FLAG_ZERO, (flags & 0x02) != 0);
    cpu.setFlag(cpu.FLAG_CARRY, (flags & 0x01) != 0);

    uint8_t lowByte = cpu.popStack();
    uint8_t highByte = cpu.popStack();

    cpu.setPC((highByte << 8) | lowByte);
    cpu.setCycles(cpu.getCycles() + 6);
}

void Instructions::handleNOPAbsoluteX(CPU6502 &cpu, Bus &bus) {
    uint16_t addr = fetchAbsoluteAddress(cpu, bus) + cpu.getX();
    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleASLAbsoluteX(CPU6502 &cpu, Bus &bus) {
    uint16_t addr = fetchAbsoluteAddress(cpu, bus) + cpu.getX();
    uint8_t value = bus.read(addr);
    uint8_t result = value << 1;

    cpu.setP((value & 0x80) ? cpu.getP() | 0x01 : cpu.getP() & ~0x01);
    cpu.setP((result == 0) ? cpu.getP() | 0x02 : cpu.getP() & ~0x02);

    bus.write(addr, result);
    cpu.setCycles(cpu.getCycles() + 7);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleEORZP(CPU6502 &cpu, Bus &bus) {
    uint8_t address = fetchZeroPage(cpu, bus);
    uint8_t operand = bus.read(address);
    cpu.setA(cpu.getA() ^ operand);
    cpu.updateZNFlags(cpu.getA());
    cpu.setCycles(cpu.getCycles() + 3);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleTXA(CPU6502 &cpu, Bus &bus) {
    cpu.setA(cpu.getX());

    cpu.updateZNFlags(cpu.getA());

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleTXS(CPU6502 &cpu, Bus &bus) {
    cpu.setSP(cpu.getX());
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleLDAAbsolute(CPU6502 &cpu, Bus &bus) {
    uint8_t low = bus.read(cpu.getPC() + 1);
    uint8_t high = bus.read(cpu.getPC() + 2);
    uint16_t address = (high << 8) | low;

    uint8_t value = bus.read(address);
    cpu.setA(value);

    cpu.updateZNFlags(value);

    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleLDXImmediate(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchImmediate(cpu, bus);
    cpu.setX(value);
    cpu.updateZNFlags(cpu.getX());
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleORAZeroPage(CPU6502 &cpu, Bus &bus) {
    uint8_t value = fetchZeroPage(cpu, bus);

    cpu.setPC(cpu.getPC() + 2);

    uint8_t result = cpu.getA() | value;
    cpu.setA(result);

    cpu.setFlag(cpu.FLAG_ZERO, result == 0);
    cpu.setFlag(cpu.FLAG_NEGATIVE, result & 0x80);

    cpu.setCycles(cpu.getCycles() + 3);
}

void Instructions::handleSTA(CPU6502 &cpu, Bus &bus) {
    uint16_t address = fetchAbsoluteAddress(cpu, bus);
    bus.write(address, cpu.getA());
    cpu.setCycles(cpu.getCycles() + 4);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleKIL(CPU6502 &cpu, Bus &bus) {
    printf("I'm dead x.x");
    cpu.setCycles(cpu.getCycles() + 1);
}

void Instructions::handleCLD(CPU6502 &cpu, Bus &bus) {
    cpu.setP(cpu.getP() & ~0x08);
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleSEI(CPU6502 &cpu, Bus &bus) {
    cpu.setFlag(cpu.FLAG_INTERRUPT, true);

    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 1);
}

void Instructions::handleLSRAbsolute(CPU6502 &cpu, Bus &bus) {
    uint16_t addr = fetchAbsoluteAddress(cpu, bus);
    uint8_t value = bus.read(addr);
    uint8_t carry = value & 0x01;
    value >>= 1;

    cpu.setP((carry) ? cpu.getP() | 0x01 : cpu.getP() & ~0x01);
    cpu.setP((value == 0) ? cpu.getP() | 0x02 : cpu.getP() & ~0x02);
    cpu.setP(cpu.getP() & ~0x80);

    bus.write(addr, value);
    cpu.setCycles(cpu.getCycles() + 6);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleORAIndirectIndexedX(CPU6502 &cpu, Bus &bus) {
    uint16_t baseAddr = fetchZeroPage(cpu, bus);
    uint16_t addr = (bus.read(baseAddr + cpu.getX())) |
                    (bus.read(baseAddr + cpu.getX() + 1) << 8);
    uint8_t value = bus.read(addr);
    cpu.setA(cpu.getA() | value);
    cpu.updateZNFlags(cpu.getA());
    cpu.setCycles(cpu.getCycles() + 6);
    cpu.setPC(cpu.getPC() + 2);
}

void Instructions::handleSREIndirectIndexed(CPU6502 &cpu, Bus &bus) {
    uint16_t addr = fetchIndirect(cpu, bus) + cpu.getY();
    uint8_t value = bus.read(addr);

    uint8_t carry = value & 0x01;
    value >>= 1;
    value |= (cpu.getP() & 0x01) << 7;

    cpu.setP((carry) ? cpu.getP() | 0x01 : cpu.getP() & ~0x01);

    cpu.setA(cpu.getA() ^ value);
    cpu.updateZNFlags(cpu.getA());
    bus.write(addr, value);
    cpu.setCycles(cpu.getCycles() + 8);
    cpu.setPC(cpu.getPC() + 3);
}

void Instructions::handleLDA(CPU6502 &cpu, Bus &bus) {
    cpu.setA(fetchImmediate(cpu, bus));
    cpu.updateZNFlags(cpu.getA());
    cpu.setCycles(cpu.getCycles() + 2);
    cpu.setPC(cpu.getPC() + 2);
}
