#include "CPU/CPUView.h"

#include "CPU/CPU6502.h"

#include "JIT/Compiler.h"
#include "PPU/PPU.h"
#include "ROM/Loader.h"
#include "ROM/PRG.hpp"
#include "ROM/ROM.hpp"
#include <iostream>
#include <thread>

#define JIT_BUFFER_SZ 4096
#define INIT_ADDRESS 0x8000
#define KB_16 16384
#define CHR_8KB 8192

void runCPU(CPU6502 &cpu, JITCompiler &jit, PPU &ppu)
{
    while (true)
    {
        if (cpu.cycles == 0)
        {
            uint8_t opcode = cpu.readMemory(cpu.PC);
            cpu.PC++;
            jit.compileOpcode(opcode, cpu);
        }

        cpu.clock();
        ppu.clock();
        ppu.clock();
        ppu.clock();
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

    PPU ppu(nullptr);
    CPU6502 cpu(ppu);
    CPUView cpuView(cpu, ppu);

    ppu.setPGE(&cpuView);
    ppu.setCHRROM(rom.getCHRData());

    JITCompiler jit(JIT_BUFFER_SZ);

    uint8_t prgBanks = romData[4];
    PRG prg(romData, cpu);

    if (!prg.load(prgBanks))
    {
        return 1;
    }

    cpu.PC = INIT_ADDRESS;

    std::thread cpuThread(runCPU, std::ref(cpu), std::ref(jit), std::ref(ppu));

    if (cpuView.Construct(ppu.getWidth(), ppu.getHeight(), 4, 4))
    {
        cpuView.Start();
    }

    cpuThread.join();

    return 0;
}
