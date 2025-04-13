#ifndef CPU6502_H
#define CPU6502_H

#include <cstdint>
#include <cstring>
#include <iostream>

#include "JIT/Compiler.h"

class Bus;

class CPU6502 {
private:
    uint8_t m_A, m_X, m_Y, m_P, m_SP;
    uint16_t m_PC;
    uint32_t m_cycles;
    uint8_t m_RAM[65536];

    Bus *bus;

public:
    enum Flags {
        FLAG_CARRY = 1 << 0,
        FLAG_ZERO = 1 << 1,
        FLAG_INTERRUPT = 1 << 2,
        FLAG_DECIMAL = 1 << 3,
        FLAG_BREAK = 1 << 4,
        FLAG_UNKNOW = 1 << 5,
        FLAG_OVERFLOW = 1 << 6,
        FLAG_NEGATIVE = 1 << 7
    };

    CPU6502();

    inline void connectBus(Bus *busPtr) {
        bus = busPtr;
    }

    inline uint8_t getA() const {
        return m_A;
    }
    inline uint8_t getX() const {
        return m_X;
    }
    inline uint8_t getY() const {
        return m_Y;
    }
    inline uint8_t getP() const {
        return m_P;
    }
    inline uint8_t getSP() const {
        return m_SP;
    }
    inline uint16_t getPC() const {
        return m_PC;
    }
    inline uint32_t getCycles() const {
        return m_cycles;
    }
    inline uint8_t *getRAM() {
        return m_RAM;
    }

    inline void setA(uint8_t value) {
        m_A = value;
    }
    inline void setX(uint8_t value) {
        m_X = value;
    }
    inline void setY(uint8_t value) {
        m_Y = value;
    }
    inline void setP(uint8_t value) {
        m_P = value;
    }
    inline void setSP(uint8_t value) {
        m_SP = value;
    }
    inline void setPC(uint16_t value) {
        m_PC = value;
    }
    inline void setCycles(uint32_t value) {
        m_cycles = value;
    }

    void triggerNMI();

    void updateZNFlags(uint8_t value);
    void pushToStack(uint8_t value);
    void pushToStack16(uint16_t value);
    uint8_t popStack();

    bool isNegativeFlagClean();

    void writeMemory(uint16_t address, uint8_t value);
    uint8_t readMemory(uint16_t address);

    void setStatusRegister(uint8_t status);

    void setStatus(uint8_t status);
    void setFlag(uint8_t flag, bool value);
    bool getFlag(uint8_t flag);
    bool isFlagSet(uint8_t flag) const;

    void step(JITCompiler &jit);
    void clock(JITCompiler &jit);

    void reset();
};

#endif
