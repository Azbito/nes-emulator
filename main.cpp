#define OLC_PGE_APPLICATION

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "Bus/Bus.h"
#include "CPU/CPU6502.h"
#include "Cartridge/Cartridge.h"
#include "JIT/Compiler.h"
#include "Libraries/olcPixelGameEngine.h"
#include "PPU/PPU.h"
#include "Screen/GameWindow.hpp"
#include "config.h"

std::vector<uint8_t> loadROM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("It couldn't open the ROM file.");

    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
}

int main() {
    auto romData = loadROM("nestest.nes");

    auto cart = std::make_shared<Cartridge>(romData);

    const auto& prgROM = cart->getPRGROM();

    Bus bus;
    CPU6502 cpu;
    PPU ppu;
    JITCompiler jit(0x10000);

    ppu.connectCartridge(cart);

    bus.connectCPU(&cpu);
    bus.connectPPU(&ppu);
    bus.connectCartridge(cart);

    cpu.connectBus(&bus);
    ppu.connectBus(&bus);
    jit.connectBus(&bus);

    cpu.reset();
    
    // GameWindow window(&ppu, &cpu, &jit, &bus);
    //
    // if (window.Create())
    //     window.Run();
    while (true) {
        cpu.step(jit);
    }

    return 0;
}
