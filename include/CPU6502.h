// CPU6502.h
#ifndef CPU6502_H
#define CPU6502_H
#include <iostream>
#include <stdint.h>
#include <array>
#include <vector>
#include <cstdint>
#include "Assembly.h"

using namespace std;

class Assembly;

class CPU6502
{
public:
    struct Status
    {
        bool C; // Carry flag
        bool Z; // Zero flag
        bool I; // Interrupt Disable flag
        bool D; // Decimal flag
        bool B; // Break flag
        bool R; // Reserved flag (always 1)
        bool V; // Overflow flag
        bool N; // Negative flag

        void reset()
        {
            C = Z = I = D = B = R = V = N = false;
            R = true;
        }
    };

    uint8_t operand;
    uint16_t PC;            // Program counter
    uint8_t A, X, Y, SP, P; // Registers: Accumulator, X, Y, Stack Pointer (SP), Processor Status (P)

    CPU6502(); // Constructor declaration

    void reset();
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    void printStatus();
    void execute();
    void mapMemory(const std::vector<uint8_t> &PRG);

    Status status;

    bool getZeroFlag() const { return status.Z; }
    bool getCarryFlag() const { return status.C; }
    bool getInterruptFlag() const { return status.I; }
    bool getNegativeFlag() const { return status.N; }

private:
    std::array<uint8_t, 0x10000> memory; // 64KB memory for the CPU
    Assembly *assembly;
};

#endif // CPU6502_H
