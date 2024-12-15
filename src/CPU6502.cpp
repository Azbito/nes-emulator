#include "CPU6502.h"
#include "Assembly.h"

CPU6502::CPU6502() : assembly(nullptr), PC(0), A(0), X(0), Y(0)
{
    memory.fill(0);
    status.reset();
    A = X = Y = SP = 0;
    PC = 0xFFFF;
    cycles = 0;

    status.P = 0;
}

uint8_t CPU6502::read(uint16_t address)
{
    return memory[address];
};

void CPU6502::write(uint16_t address, uint8_t value)
{
    memory[address] = value;
};

void CPU6502::execute()
{
    uint8_t opcode = read(PC);
    cycles = 0;

    cout << "Opcode at PC (0x" << hex << PC << "): "
         << setw(2) << setfill('0') << static_cast<int>(opcode) << endl;
    assembly->executeOpcode(opcode);
}

void CPU6502::reset()
{
    uint8_t lowByte = read(0xFFFC);
    uint8_t highByte = read(0xFFFD);

    PC = (highByte << 8) | lowByte;

    A = X = Y = SP = 0;

    cycles = 0;
    status.reset();
}

void CPU6502::printStatus()
{
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

    memory[0xFFFC] = 0x00;
    memory[0xFFFD] = 0x80;

    cout << "Memory mapped. PRG ROM loaded at 0x8000." << endl;
}
