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

void runCPU(CPU6502 &cpu, JITCompiler &jit, PPU &ppu)
{
    while (true)
    {
        if (cpu.getCycles() == 0)
        {
            uint8_t opcode = cpu.readMemory(cpu.getPC());
            cpu.setPC(cpu.getPC() + 1);
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
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <rom_file.nes>" << std::endl;
        return 1;
    }

    ROM rom;
    ROMLoader romLoader;

    std::cout << "[SYSTEM] Running emulator..." << std::endl;

    if (!romLoader.load(argv[1], rom))
    {
        return 1;
    }

    std::cout << "[SYSTEM] Valid ROM." << std::endl;
    std::cout << "[SYSTEM] ROM loaded successfully!" << std::endl;

    const auto &prgData = rom.getPRGData();
    size_t sz = prgData.size();

    PPU ppu(nullptr);
    CPU6502 cpu(ppu);
    CPUView cpuView(cpu, ppu);

    ppu.powerUp();
    ppu.setPGE(&cpuView);
    ppu.setCHRROM(rom.getCHRData());

    JITCompiler jit(JIT_BUFFER_SZ);

    uint8_t prgBanks = rom.getPRGBanks();

    PRG prg(prgData, cpu);

    if (!prg.load(prgBanks))
    {
        return 1;
    }

    uint16_t resetVector = prgData[sz - 4] | (prgData[sz - 3] << 8);
    cpu.setPC(resetVector);

    cpu.setCycles(7);

    std::thread cpuThread(runCPU, std::ref(cpu), std::ref(jit), std::ref(ppu));

    if (cpuView.Construct(ppu.getWidth(), ppu.getHeight(), 4, 4))
    {
        cpuView.Start();
    }

    cpuThread.join();
    return 0;
}
