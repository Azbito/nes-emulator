#ifndef CPU6502_H
#define CPU6502_H
#include <iostream>
#include <stdint.h>
#include <array>
#include <vector>
#include <cstdint>
#include <iomanip>
#include "Assembly.h"

using namespace std;

class Assembly;

class CPU6502
{
public:
    struct Status
    {
        uint8_t P;

        Status() : P(0b00100000) {}

        bool getCarryFlag() const { return P & 0x01; }
        void setCarryFlag(bool value) { P = value ? (P | 0x01) : (P & ~0x01); }

        bool getZeroFlag() const { return P & 0x02; }
        void setZeroFlag(bool value) { P = value ? (P | 0x02) : (P & ~0x02); }

        bool getInterruptFlag() const { return P & 0x04; }
        void setInterruptFlag(bool value) { P = value ? (P | 0x04) : (P & ~0x04); }

        bool getDecimalFlag() const { return P & 0x08; }
        void setDecimalFlag(bool value) { P = value ? (P | 0x08) : (P & ~0x08); }

        bool getBreakFlag() const { return P & 0x10; }
        void setBreakFlag(bool value) { P = value ? (P | 0x10) : (P & ~0x10); }

        bool getReservedFlag() const { return P & 0x20; }
        void setReservedFlag(bool value) {}

        bool getOverflowFlag() const { return P & 0x40; }
        void setOverflowFlag(bool value) { P = value ? (P | 0x40) : (P & ~0x40); }

        bool getNegativeFlag() const { return P & 0x80; }
        void setNegativeFlag(bool value) { P = value ? (P | 0x80) : (P & ~0x80); }

        void reset()
        {
            P = 0b00100000;
        }
    };

    uint8_t operand;
    uint16_t PC;         // Program counter
    uint8_t A, X, Y, SP; // Registers: Accumulator, X, Y, Stack Pointer (SP)
    int cycles;

    CPU6502();

    void reset();
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    void printStatus();
    void execute();
    void mapMemory(const std::vector<uint8_t> &PRG);

    Status status;

private:
    std::array<uint8_t, 0x10000> memory; // 64KB memory for the CPU
    Assembly *assembly;
};

#endif // CPU6502_H
