#include "Bus/Bus.h"
#include "CPU/CPU6502.h"
#include "Cartridge/Cartridge.h"
#include "JIT/Compiler.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

std::vector<uint8_t> loadROM(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Não foi possível abrir a ROM!");

    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
}

int main()
{
    auto romData = loadROM("smb.nes");

    auto cart = std::make_shared<Cartridge>(romData);

    Bus bus;
    CPU6502 cpu;
    JITCompiler jit(0x10000);

    bus.connectCPU(&cpu);
    bus.connectCartridge(cart);
    cpu.connectBus(&bus);
    jit.connectBus(&bus);

    cpu.reset();

    while (true)
    {
        cpu.step(jit);
    }

    return 0;
}
