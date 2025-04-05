#include "CPU/CPU6502.h"
#include "CPU/CPUView.h"
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
    printf("\n\n OPCODES:\n");

    while (true)
    {
        if (cpu.getCycles() == 0)
        {
            uint8_t opcode = cpu.readMemory(cpu.getPC());
            printf(" %02X", opcode);
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

    PRG prg(romData, cpu);

    if (!prg.load())
    {
        std::cerr << "[SYSTEM] Failed to load PRG into CPU memory."
                  << std::endl;
        return 1;
    }

    cpu.reset();

    std::thread cpuThread(runCPU, std::ref(cpu), std::ref(jit), std::ref(ppu));

    if (cpuView.Construct(ppu.getWidth(), ppu.getHeight(), 4, 4))
    {
        cpuView.Start();
    }

    cpuThread.join();

    return 0;
}
