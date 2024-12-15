#include "PPU.h"

PPU::PPU() : vram(0x4000, 0) {}

void PPU::reset()
{
    fill(vram.begin(), vram.end(), 0);
}

void PPU::writeMemory(uint16_t address, uint8_t value)
{
    if (address < vram.size())
    {
        vram[address] = value;
    }
}

uint8_t PPU::readMemory(uint16_t address)
{
    if (address < vram.size())
    {
        return vram[address];
    }

    return 0;
}

void PPU::renderFrame(vector<uint32_t> &frameBuffer)
{
    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            uint8_t colorIndex = vram[(y * SCREEN_WIDTH + x) % vram.size()];
            frameBuffer[y * SCREEN_WIDTH + x] = 0xFF000000 | (colorIndex * 0x010101);
        }
    }
}
