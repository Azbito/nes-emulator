#pragma once

#include "CPU/CPU6502.h"
#include "Libraries/olcPixelGameEngine.h"
#include "PPU/PPU.h"

class CPUView : public olc::PixelGameEngine
{
  public:
    CPUView(CPU6502 &cpuRef, PPU &ppuRef) : cpu(cpuRef), ppu(ppuRef)
    {
        sAppName = "6502 CPU";
    }

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

  private:
    bool debugger();

    CPU6502 &cpu;
    PPU &ppu;
};
