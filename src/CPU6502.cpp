#include "CPU6502.hpp"
#include "Assembly.h"

uint8_t CPU6502::read(uint16_t address)
{
    return memory[address];
};

void CPU6502::write(uint16_t address, uint8_t value)
{
    memory[address] = value;
};

uint16_t CPU6502::popStackWord()
{
    uint8_t lowByte = memory[0x0100 + SP];
    SP++;
    uint8_t highByte = memory[0x0100 + SP];
    SP++;

    return (highByte << 8) | lowByte;
}

uint16_t CPU6502::popStack16()
{
    uint8_t lowByte = this->memory[0x0100 + this->SP];
    this->SP--;

    uint8_t highByte = this->memory[0x0100 + this->SP];
    this->SP--;
    uint16_t result = (highByte << 8) | lowByte;

    return result;
}

uint8_t CPU6502::popStack()
{
    uint8_t value = this->memory[0x0100 + this->SP];
    this->SP++;
    return value;
}

void CPU6502::pushStack(uint8_t value)
{
    this->memory[0x0100 + getSP()] = value;
    setSP(getSP() - 1);
}

void CPU6502::triggerTrap()
{
    uint16_t returnAddress = getPC() + 1;
    pushStack(returnAddress >> 8);
    pushStack(returnAddress & 0xFF);
    uint8_t status = getStatus().getP();
    status |= 0x10;
    status &= ~0x04;
    pushStack(status);

    getStatus().setInterruptFlag(true);

    setPC(0xFFFA);
    setCycles(getCycles() + 7);
}

void CPU6502::execute()
{
    cout << "PC before fetch: 0x" << hex << PC << endl;

    uint8_t opcode = memory[PC];
    cycles = 0;
    cout << "Opcode at PC (0x" << hex << PC << "): "
         << setw(2) << setfill('0') << static_cast<int>(opcode) << endl;

    cout << "PC after fetch: 0x" << hex << PC << endl;

    uint16_t pc = getPC();
    cout << "getPC returned: 0x" << hex << pc << endl;

    setPC(pc + 1);

    cout << "PC after increment: 0x" << hex << getPC() << endl;

    assembly->executeOpcode(opcode);
}

void CPU6502::setAssembly(Assembly *assembly)
{
    this->assembly = assembly;
}

void CPU6502::reset()
{
    A = X = Y = 0;
    SP = 0xFD;

    cycles = 0;
    uint16_t resetVector = read(0xFFFC) | (read(0xFFFC + 1) << 8);
    PC = 0x8000;

    status.reset();
}

uint16_t CPU6502::readMemory16(uint16_t address)
{
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}

void CPU6502::printStatus()
{
    if (this == nullptr)
    {
        std::cerr << "Error: CPU is null!" << std::endl;
        return;
    }

    cout << "PC: " << hex << PC
         << " A: " << (int)A
         << " X: " << (int)X
         << " Y: " << (int)Y
         << " C: " << (status.getCarryFlag() ? 1 : 0)
         << " Z: " << (status.getZeroFlag() ? 1 : 0)
         << " I: " << (status.getInterruptFlag() ? 1 : 0)
         << " D: " << (status.getDecimalFlag() ? 1 : 0)
         << " B: " << (status.getBreakFlag() ? 1 : 0)
         << " R: " << (status.getReservedFlag() ? 1 : 0)
         << " V: " << (status.getOverflowFlag() ? 1 : 0)
         << " N: " << (status.getNegativeFlag() ? 1 : 0)
         << dec << endl;
}

void CPU6502::mapMemory(const vector<uint8_t> &PRG)
{
    size_t PRGSize = PRG.size();
    size_t startAddress = 0x8000;

    for (size_t i = 0; i < PRGSize; ++i)
    {
        memory[startAddress + i] = PRG[i];
    }

    uint8_t lowByte = memory[0xFFFC];
    uint8_t highByte = memory[0xFFFD];

    uint16_t resetVector = (highByte << 8) | lowByte;

    this->PC = 0x8000;

    cout << "Memory mapped. PRG ROM loaded at 0x8000." << endl;
    cout << "Reset vector at 0xFFFC-0xFFFD points to: 0x" << hex << resetVector << dec << endl;
}
