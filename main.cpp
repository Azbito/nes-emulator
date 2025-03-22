#include "CPU/CPU6502.h"
#include "JIT/Compiler.h"
#include "PPU/PPU.h"
#include "PPU/Renderer.h"
#include "PRG/PRG.hpp"
#include "ROM/Loader.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>

#define JIT_BUFFER_SZ 4096
#define INIT_ADDRESS 0x8000
#define MB_16 16384

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

    ROMLoader rom;
    if (!rom.load(argv[1]))
    {
        return 1;
    }

    const std::vector<uint8_t> &romData = rom.getData();

    PPU ppu;
    CPU6502 cpu;
    JITCompiler jit(JIT_BUFFER_SZ);

    uint8_t prgBanks = romData[4];
    PRGLoader prgLoader(romData, cpu);

    if (!prgLoader.loadPRG(prgBanks))
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

        std::vector<uint32_t> framebuffer;
        ppu.updateFramebuffer(framebuffer);

        renderer.clearScreen();
        renderer.renderFrame(framebuffer);

        renderer.flipDisplay();

        al_rest(0.016);
    }

    return 0;
}
