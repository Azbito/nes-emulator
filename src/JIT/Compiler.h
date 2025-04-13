#ifndef JIT_COMPILER_H
#define JIT_COMPILER_H

#define OPCODE_RANGE 256

#include <windows.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>

class CPU6502;
class Instructions;
class Bus;

class JITCompiler {
public:
    JITCompiler(size_t bufferSize);
    ~JITCompiler();

    void compileOpcode(uint8_t opcode, CPU6502 &cpu);

    inline void connectBus(Bus *busPtr) {
        bus = busPtr;
    }

private:
    Instructions *asm_instructions;
    Bus *bus;

    void (Instructions::*opcodeTable[OPCODE_RANGE])(CPU6502 &cpu,
                                                    Bus &bus) = {nullptr};
};

#endif
