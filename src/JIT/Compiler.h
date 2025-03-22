#ifndef JIT_COMPILER_H
#define JIT_COMPILER_H

#define OPCODE_RANGE 256

#include "Assembly/Instructions.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <windows.h>

class JITCompiler
{
  public:
    JITCompiler(size_t bufferSize);
    ~JITCompiler();

    void compileOpcode(uint8_t opcode, CPU6502 &cpu);

  private:
    Instructions asm_instructions;
    void (Instructions::*opcodeTable[OPCODE_RANGE])(CPU6502 &cpu);
};

#endif
