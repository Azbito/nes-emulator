#pragma once

#include "CPU/CPU6502.h"
#include "Libraries/olcPixelGameEngine.h"

class CPUView : public olc::PixelGameEngine
{
  public:
    CPUView(CPU6502 &cpuRef) : cpu(cpuRef)
    {
        sAppName = "6502 CPU";
    }

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

  private:
    CPU6502 &cpu;
};
