#include "CPU6502.h"
#include "Assembly.h"

CPU6502::CPU6502() : assembly(nullptr), PC(0), A(0), X(0), Y(0)
{
    memory.fill(0);
    status.reset();
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

    assembly->execute(opcode);
}

void CPU6502::reset()
{
    PC = 0;
    A = X = Y = SP = 0;
    status.reset();
}

void CPU6502::printStatus()
{
    std::cout << "PC: " << std::hex << PC
              << " A: " << (int)A
              << " X: " << (int)X
              << " Y: " << (int)Y
              << " C: " << status.C
              << " Z: " << status.Z
              << " I: " << status.I
              << " D: " << status.D
              << " B: " << status.B
              << " R: " << status.R
              << " V: " << status.V
              << " N: " << status.N
              << std::dec << std::endl;
}

void CPU6502::mapMemory(const std::vector<uint8_t> &PRG)
{
    size_t PRGSize = PRG.size();
    for (size_t i = 0; i < PRGSize; ++i)
    {
        memory[i] = PRG[i];
    }
}