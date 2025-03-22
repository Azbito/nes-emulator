#include "CPU/CPU6502.h"
#include "JIT/Compiler.h"
#include "ROM/Loader.h"
#include <iostream>

#define JIT_BUFFER_SZ 4096
#define INIT_ADDRESS 0x8000

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    ROMLoader rom;

    if (!rom.load(argv[1]))
    {
        return 1;
    }

    CPU6502 cpu;
    JITCompiler jit(JIT_BUFFER_SZ);

    const auto &romData = rom.getData();

    for (size_t i = 0; i < romData.size(); ++i)
    {
        cpu.RAM[i] = romData[i];
    }

    cpu.PC = INIT_ADDRESS;

    while (true)
    {
        uint8_t opcode = cpu.RAM[cpu.PC];

        jit.compileOpcode(opcode, cpu);
    }

    return 0;
}
