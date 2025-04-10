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

        const int totalPPUCyclesPerFrame = 341 * 262;
        static int accumulatedCPUCycles = 0;

        ppu->resetFrameFlag();

        int ppuCyclesThisFrame = 0;
        while (ppuCyclesThisFrame < totalPPUCyclesPerFrame)
        {

            if (ppuCyclesThisFrame % 3 == 0)
            {
                if (cpu->getCycles() == 0)
                {
                    cpu->step(*jit);
                }
                cpu->clock(*jit);
                accumulatedCPUCycles++;
            }

            ppu->clock();
            ppuCyclesThisFrame++;

            if (ppu->nmiTriggered())
            {
                cpu->triggerNMI();
                ppu->clearNmiFlag();
            }
        }

        if (ppu->isFrameComplete())
        {
            ppu->renderFrame();

            const std::array<olc::Pixel, 256 * 240> &frame =
                ppu->getFrameBuffer();
            for (int y = 0; y < 240; ++y)
            {
                for (int x = 0; x < 256; ++x)
                {
                    olc::Pixel color = frame[y * 256 + x];
                    Draw(x, y, color);
                }
            }
        }

        return true;
    }

  private:
    PPU *ppu;
    CPU6502 *cpu;
    JITCompiler *jit;
};
