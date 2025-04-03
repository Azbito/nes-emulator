#include "CPU/CPUView.h"

#include "CPU/CPU6502.h"

#include "JIT/Compiler.h"
#include "PPU/PPU.hpp"
#include "ROM/Loader.h"
#include "ROM/PRG.hpp"
#include "ROM/ROM.hpp"
#include <iostream>
#include <thread>

#define JIT_BUFFER_SZ 4096
#define INIT_ADDRESS 0x8000
#define KB_16 16384
#define CHR_8KB 8192

void runCPU(CPU6502 &cpu, JITCompiler &jit)
{
    while (true)
    {
        uint8_t opcode = cpu.RAM[cpu.PC];
        jit.compileOpcode(opcode, cpu);
    }
}

int main(int argc, char *argv[])
{
    ROMLoader romLoader;
    ROM rom;

    if (!romLoader.load(argv[1], rom))
    {
        return 1;
    }

    const std::vector<uint8_t> &romData = rom.getPRGData();

    PPU ppu;
    CPU6502 cpu(ppu);
    CPUView cpuView(cpu);

    JITCompiler jit(JIT_BUFFER_SZ);

    uint8_t prgBanks = romData[4];
    PRG prg(romData, cpu);

    if (!prg.load(prgBanks))
    {
        return 1;
    }

    cpu.PC = INIT_ADDRESS;

    std::thread cpuThread(runCPU, std::ref(cpu), std::ref(jit));

    if (cpuView.Construct(ppu.width, ppu.height, 4, 4))
    {
        cpuView.Start();
    }

    cpuThread.join();

    return 0;
}
