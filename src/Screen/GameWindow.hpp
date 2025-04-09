#pragma once

#include "CPU/CPU6502.h"
#include "JIT/Compiler.h"
#include "Libraries/olcPixelGameEngine.h"
#include "PPU/PPU.h"

class GameWindow : public olc::PixelGameEngine
{
  public:
    GameWindow(PPU *ppu_, CPU6502 *cpu_, JITCompiler *jit_)
        : ppu(ppu_), cpu(cpu_), jit(jit_)
    {
        sAppName = "PPU Background View";
    }

    bool OnUserCreate() override
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        const int targetCyclesPerFrame = 29830;
        int startCycle = cpu->getCycles();

        while ((cpu->getCycles() - startCycle) < targetCyclesPerFrame)
        {
            cpu->step(*jit);
        }

        if (!ppu->renderBackground())
            return;

        Clear(olc::BLACK);
        ppu->renderFrame();
        const auto &fb = ppu->getFrameBuffer();

        for (int y = 0; y < 240; y++)
            for (int x = 0; x < 256; x++)
                Draw(x, y, fb[y * 256 + x]);

        return true;
    }

  private:
    PPU *ppu;
    CPU6502 *cpu;
    JITCompiler *jit;
};
