#ifndef CPU6502_H
#define CPU6502_H

#include "Assembly.h"
#include <iostream>
#include <stdint.h>
#include <array>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <cstring>

using namespace std;

class Assembly;

class CPU6502
{
public:
    CPU6502()
        : assembly(nullptr), PC(0xFFFF), A(0), X(0), Y(0), SP(0xFF), cycles(0)
    {
        memset(memory, 0x00, sizeof(memory));
        status.reset();
    }

    CPU6502(Assembly *assembly)
        : assembly(assembly), PC(0xFFFF), A(0), X(0), Y(0), SP(0xFF), cycles(0)
    {
        memset(memory, 0x00, sizeof(memory));
        status.reset();
    }

    struct Status
    {
        uint8_t P;

        Status() : P(0b00100000) {}

        // getters
        uint8_t getP() const { return P; }

        bool getCarryFlag() const { return P & 0x01; }
        bool getZeroFlag() const { return P & 0x02; }
        bool getInterruptFlag() const { return P & 0x04; }
        bool getDecimalFlag() const { return P & 0x08; }
        bool getBreakFlag() const { return P & 0x10; }
        bool getReservedFlag() const { return P & 0x20; }
        bool getOverflowFlag() const { return P & 0x40; }
        bool getNegativeFlag() const { return P & 0x80; }

        // setters
        void setP(uint8_t value) { P = value; }
        void setZeroFlag(bool value) { P = value ? (P | 0x02) : (P & ~0x02); }
        void setInterruptFlag(bool value) { P = value ? (P | 0x04) : (P & ~0x04); }
        void setDecimalFlag(bool value) { P = value ? (P | 0x08) : (P & ~0x08); }
        void setBreakFlag(bool value) { P = value ? (P | 0x10) : (P & ~0x10); }
        void setReservedFlag(bool value) {}
        void setOverflowFlag(bool value) { P = value ? (P | 0x40) : (P & ~0x40); }
        void setOverflowFlagAOR(uint8_t accumulator, uint8_t operand, uint8_t result)
        {
            bool overflow = ((accumulator & 0x80) == (operand & 0x80)) && ((accumulator & 0x80) != (result & 0x80));

            setOverflowFlag(overflow);
        }

        void setNegativeFlag(bool value) { P = value ? (P | 0x80) : (P & ~0x80); }
        void setCarryFlag(bool value) { P = value ? (P | 0x01) : (P & ~0x01); }
        void setInterruptDisableFlag(bool value) { P = value ? (P | 0x04) : (P & ~0x04); }

        void clearDecimalFlag()
        {
            P = P & ~0x08;
        }

        void clearInterruptDisableFlag() { P &= ~0x04; }

        void fromByte(uint8_t statusByte)
        {
            P = statusByte;
        }

        void reset() { P = 0b00100000; }
    };

    void reset();

    // getters
    uint8_t getA() const { return A; }
    uint8_t getX() const { return X; }
    uint8_t getY() const { return Y; }
    uint8_t getSP() const { return SP; }
    uint16_t getPC() const { return PC; }
    int getCycles() const { return cycles; }
    Status &getStatus() { return status; }
    uint8_t getOperand() { return operand; }
    uint8_t getMemory(uint16_t address) const
    {
        return memory[address];
    }
    uint8_t getXRegister() const { return X; }
    uint8_t getYRegister() const { return Y; };
    uint8_t getAccumulator() const { return A; }

    // setters
    void setA(uint8_t value) { A = value; }
    void setX(uint8_t value) { X = value; }
    void setY(uint8_t value) { Y = value; }
    void setSP(uint8_t value) { SP = value; }
    void setPC(uint16_t value)
    {
        PC = value;
        cout << "PC set to: 0x" << hex << PC << endl;
    }
    void setCycles(int value) { cycles = value; }
    void setMemory(uint16_t address, uint8_t value)
    {
        memory[address] = value;
    }
    void setStatus(uint8_t newStatus)
    {
        status.setP(newStatus);
    }
    void setAccumulator(uint8_t value) { A = value; }

    void triggerTrap(); //! WARNING: IT WILL KILL THE ROM
    void pushStack(uint8_t value);
    uint16_t popStackWord();
    uint8_t popStack();
    uint16_t popStack16();
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    void printStatus();
    void execute();
    void mapMemory(const std::vector<uint8_t> &PRG);
    void setAssembly(Assembly *assembly);
    uint16_t readMemory16(uint16_t address);
    Status status;

private:
    Assembly *assembly;
    uint8_t memory[0x10000]; //* 64KB memory for the CPU
    uint8_t operand;
    uint16_t PC = 0x8000; // Program counter
    uint8_t A, X, Y, SP;  // Registers: Accumulator, X, Y, Stack Pointer (SP)
    int cycles;
};

#endif // CPU6502_H
