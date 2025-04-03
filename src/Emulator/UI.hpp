#define OLC_PGE_APPLICATION

#include "CPU/CPU6502.h"
#include "Libraries/olcPixelGameEngine.h"
#include "Utils/main.hpp"

class UI : public olc::PixelGameEngine
{
  public:
    void drawRam(int x, int y, CPU6502 &cpu)
    {
        int width = 16;
        int height = 16;
        for (int row = 0; row < height; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                int address = row * width + col;
                if (address < 0xFFFF)
                {
                    uint8_t value = cpu.RAM[address];

                    Draw(x + col * 30, y + row * 10, olc::Pixel(255, 255, 255));
                    DrawString(x + col * 30, y + row * 10,
                               std::to_string(value), olc::BLACK);
                }
            }
        }
    }

    void drawCpu(int x, int y, CPU6502 &cpu)
    {

        DrawString(x, y, "PC: " + std::to_string(cpu.PC), olc::WHITE);
        DrawString(x, y + 10, "SP: " + std::to_string(cpu.SP), olc::WHITE);
        DrawString(x, y + 20, "A: " + std::to_string(cpu.A), olc::WHITE);
        DrawString(x, y + 30, "X: " + std::to_string(cpu.X), olc::WHITE);
        DrawString(x, y + 40, "Y: " + std::to_string(cpu.Y), olc::WHITE);
        DrawString(x, y + 50, "Flags: " + utils::uint8ToString(cpu.status()),
                   olc::WHITE);
    }

    void drawCode(int x, int y, CPU6502 &cpu)
    {
        uint8_t opcode = cpu.RAM[cpu.PC];
        std::string opcodeStr = "Opcode: " + std::to_string(opcode);

        DrawString(x, y, opcodeStr, olc::WHITE);
    }
};
