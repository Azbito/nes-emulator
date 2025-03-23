#include "CPU/CPU6502.h"
#include "JIT/Compiler.h"
#include "ROM/Loader.h"
#include "ROM/PPU.h"
#include "ROM/PRG.hpp"
#include "ROM/ROM.hpp"
#include "Screen/Renderer.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>

#define JIT_BUFFER_SZ 4096
#define INIT_ADDRESS 0x8000
#define KB_16 16384
#define CHR_8KB 8192

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    if (!al_init())
    {
        return 1;
    }

    if (!al_init_font_addon() || !al_init_ttf_addon())
    {
        return 1;
    }

    Renderer renderer(256, 240);
    try
    {
        renderer.initializeDisplay();
    }
    catch (const std::exception &e)
    {
        return 1;
    }

    ROMLoader romLoader;
    ROM rom;

    if (!romLoader.load(argv[1], rom))
    {
        return 1;
    }

    const std::vector<uint8_t> &romData = rom.getPRGData();
    const std::vector<uint8_t> &chrData = rom.getCHRData();
    const std::vector<uint8_t> &nametable = rom.getNametableData();

    PPU ppu;
    CPU6502 cpu;
    JITCompiler jit(JIT_BUFFER_SZ);

    uint8_t prgBanks = romData[4];
    PRG prg(romData, cpu);

    if (!prg.load(prgBanks))
    {
        return 1;
    }

    uint16_t resetVector =
        cpu.readMemory(0xFFFC) | (cpu.readMemory(0xFFFD) << 8);
    cpu.PC = resetVector;

    for (size_t i = 0; i < romData.size(); ++i)
    {
        cpu.RAM[i] = romData[i];
    }

    cpu.PC = INIT_ADDRESS;

    while (true)
    {
        uint8_t opcode = cpu.RAM[cpu.PC];
        jit.compileOpcode(opcode, cpu);
        renderer.clearScreen();
        ppu.renderBackground(renderer, nametable, chrData);
        renderer.flipDisplay();

        al_rest(0.016);
    }

    return 0;
}
