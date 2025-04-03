
#define OLC_PGE_APPLICATION

#include "CPU/CPU6502.h"
#include "Emulator/UI.hpp"
#include "JIT/Compiler.h"
#include "Libraries/olcPixelGameEngine.h"
#include "ROM/Loader.h"
#include "ROM/PPU.h"
#include "ROM/PRG.hpp"
#include "ROM/ROM.hpp"
#include <iostream>

#define JIT_BUFFER_SZ 4096
#define INIT_ADDRESS 0x8000
#define KB_16 16384
#define CHR_8KB 8192

class Emulator : public olc::PixelGameEngine
{
  public:
    NESGame()
    {
        sAppName = "NES Emulator with olc::PixelGameEngine";
    }

  public:
    bool OnUserCreate() override
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        CPU6502 cpu;
        UI ui;
        JITCompiler jit(JIT_BUFFER_SZ);

        ROMLoader romLoader;
        ROM rom;

        if (!romLoader.load("./smb.nes", rom))
        {
            return false;
        }

        const std::vector<uint8_t> &romData = rom.getPRGData();
        const std::vector<uint8_t> &chrData = rom.getCHRData();
        const std::vector<uint8_t> &nametable = rom.getNametableData();

        PPU ppu;
        PRG prg(romData, cpu);

        uint8_t prgBanks = romData[4];

        if (!prg.load(prgBanks))
        {
            return false;
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

            for (int y = 0; y < 240; ++y)
            {
                for (int x = 0; x < 256; ++x)
                {
                    uint8_t color = 0;
                    Draw(x, y, olc::Pixel(color, color, color));
                }
            }

            ui.drawRam(10, 10, cpu);
            ui.drawCpu(200, 10, cpu);
            ui.drawCode(200, 70, cpu);

            Sleep(16);
        }

        return true;
    }
};
