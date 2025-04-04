#define OLC_PGE_APPLICATION

#include "CPUView.h"
#include "Assembly/Instructions.h"
#include "Utils/main.hpp"
#include <iostream>
#include <unordered_map>

bool CPUView::OnUserCreate()
{
    std::cout << "[EMULATOR] Running view..." << std::endl;
    return true;
}

bool CPUView::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLACK);
    olc::vf2d scale = {0.5f, 0.5f};
    float baseX = 140.0f;
    float startY = 10.0f;
    float lineSpacing = 15.0f;

    uint8_t opcode = this->cpu.RAM[this->cpu.PC];

    DrawStringDecal({baseX, startY}, "CPU 6502 Registers", olc::WHITE, scale);
    DrawStringDecal({baseX, startY + lineSpacing},
                    "A:  " + std::to_string(this->cpu.A), olc::GREEN, scale);
    DrawStringDecal({baseX, startY + 2.0f * lineSpacing},
                    "X:  " + std::to_string(this->cpu.X), olc::GREEN, scale);
    DrawStringDecal({baseX, startY + 3.0f * lineSpacing},
                    "Y:  " + std::to_string(this->cpu.Y), olc::GREEN, scale);
    DrawStringDecal({baseX, startY + 4.0f * lineSpacing},
                    "PC: " + std::to_string(this->cpu.PC), olc::CYAN, scale);
    DrawStringDecal({baseX, startY + 5.0f * lineSpacing},
                    "SP: " + std::to_string(this->cpu.SP), olc::MAGENTA, scale);
    DrawStringDecal({baseX, startY + 6.0f * lineSpacing},
                    "P:  " + std::to_string(this->cpu.P), olc::YELLOW, scale);

    Instructions instructions;

    std::string instruction = (instructions.opcodeMap.count(opcode) > 0)
                                  ? instructions.opcodeMap[opcode]
                                  : "???";

    DrawStringDecal(olc::vf2d(baseX, startY + 7.0f * lineSpacing),
                    utils::hexToString(this->cpu.PC) + ": " +
                        utils::hexToString(opcode) + " " + instruction,
                    olc::WHITE, scale);

    return true;
}
