#pragma once
#include <vector>
#include <cstdint>

using namespace std;

class PPU
{
public:
    static constexpr int SCREEN_WIDTH = 256;
    static constexpr int SCREEN_HEIGHT = 240;

    PPU();
    void reset();
    void renderFrame(vector<uint32_t> &frameBuffer);

    void writeMemory(uint16_t address, uint8_t value);
    uint8_t readMemory(uint16_t address);

private:
    vector<uint8_t> vram;
};
