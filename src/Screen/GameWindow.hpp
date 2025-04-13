#pragma once

#include <bitset>
#include <cstdio>
#include <unordered_map>

#include "Assembly/Instructions.h"
#include "Bus/Bus.h"
#include "CPU/CPU6502.h"
#include "JIT/Compiler.h"
#include "Libraries/olcPixelGameEngine.h"
#include "PPU/PPU.h"
#include "Utils/main.hpp"
#include "config.h"

class GameWindow : public olc::PixelGameEngine {
public:
    GameWindow(PPU *ppu_, CPU6502 *cpu_, JITCompiler *jit_, Bus *bus_)
        : ppu(ppu_),
          cpu(cpu_),
          jit(jit_),
          bus(bus_),
          isPaused(true),
          isStepping(false) {
        sAppName = "NES Emulator Debug View";
    }

    bool OnUserCreate() override {
        isPaused = true;
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
#if DEBUG_MODE
        if (GetKey(olc::Key::P).bPressed)
            isPaused = !isPaused;

        if (GetKey(olc::Key::S).bPressed && isPaused) {
            isStepping = true;
            printf("OPCODE: %02X\n", bus->read(cpu->getPC()));
        }

        if (isPaused && isStepping) {
            RunSingleInstruction();
            isPaused = true;
            isStepping = false;
        }

        if (!isPaused) {
            RunEmulationFrame();
        }
#else
        RunEmulationFrame();
#endif

        DrawScreen();
        return true;
    }

private:
    PPU *ppu;
    CPU6502 *cpu;
    JITCompiler *jit;
    Bus *bus;

    bool isPaused;
    bool isStepping;

    void RunSingleInstruction() {
        if (cpu->getCycles() == 0) {
            cpu->step(*jit);
        }

        do {
            ppu->clock();
            ppu->clock();
            ppu->clock();

            if (ppu->getCycles() % 3 == 0) {
                if (cpu->getCycles() == 0) {
                    cpu->step(*jit);
                }

                cpu->clock(*jit);
            }

            if (ppu->nmiTriggered()) {
                cpu->triggerNMI();
                ppu->clearNmiFlag();
            }
        } while (cpu->getCycles() > 0);
    }

    void RunEmulationFrame() {
        const int totalPPUCyclesPerFrame = 341 * 262;
        while (ppu->getCycles() < totalPPUCyclesPerFrame) {
            ppu->clock();

            if (ppu->getCycles() % 3 == 0) {
                if (cpu->getCycles() == 0) {
                    cpu->step(*jit);
                }

                cpu->clock(*jit);
            }
        }
    }

    void DrawScreen() {
        constexpr int ppuWidth = 256;

#if SHOW_INSTRUCTIONS
        Clear(olc::Pixel(20, 20, 50));

        FillRect(ppuWidth, 0, ScreenWidth() - ppuWidth, ScreenHeight(),
                 olc::DARK_BLUE);
        DrawRect(ppuWidth - 1, 0, ScreenWidth() - ppuWidth + 2, ScreenHeight(),
                 olc::WHITE);

        DrawDebugInfo(ppuWidth - 125, 10);
#else
        if (ppu->isFrameComplete()) {
            ppu->renderFrame();

            const std::array<olc::Pixel, 256 * 240> &frame =
                ppu->getFrameBuffer();
            for (int y = 0; y < 240; ++y) {
                for (int x = 0; x < 256; ++x) {
                    olc::Pixel color = frame[y * 256 + x];
                    Draw(x, y, color);
                }
            }
        }
#endif
    }

    void DrawDebugInfo(int x, int y) {
        olc::Pixel textColor = olc::WHITE;
        float scale = 0.5f;

        DrawStringDecal({(float)x, (float)(y + 0)}, "CPU REGISTERS:", textColor,
                        {scale, scale});
        DrawStringDecal({(float)x, (float)(y + 10)},
                        "PC: " + utils::hexToString(cpu->getPC(), 4), textColor,
                        {scale, scale});
        DrawStringDecal({(float)x, (float)(y + 20)},
                        "A:  " + utils::hexToString(cpu->getA(), 2), textColor,
                        {scale, scale});
        DrawStringDecal({(float)x, (float)(y + 30)},
                        "X:  " + utils::hexToString(cpu->getX(), 2), textColor,
                        {scale, scale});
        DrawStringDecal({(float)x, (float)(y + 40)},
                        "Y:  " + utils::hexToString(cpu->getY(), 2), textColor,
                        {scale, scale});
        DrawStringDecal({(float)x, (float)(y + 50)},
                        "SP: " + utils::hexToString(cpu->getSP(), 2), textColor,
                        {scale, scale});

        uint8_t p = cpu->getP();
        std::string flags = "";
        for (int i = 7; i >= 0; i--) {
            flags += (p & (1 << i)) ? '1' : '0';
        }
        DrawStringDecal({(float)x, (float)(y + 60)}, "FLAGS: " + flags,
                        textColor, {scale, scale});

        DrawStringDecal(
            {(float)x, (float)(y + 70)},
            "STATE: " + std::string(isPaused ? "PAUSED" : "RUNNING"),
            isPaused ? olc::RED : olc::GREEN, {scale, scale});

        Instructions instructions;
        std::string opcodeName =
            instructions.getOpcodeName(bus->read(cpu->getPC()));

        DrawStringDecal({(float)x, (float)(y + 80)},
                        "OPCODE: " + opcodeName + " [" +
                            utils::hexToString(bus->read(cpu->getPC()), 2) +
                            "]",
                        textColor, {scale, scale});

        DrawStringDecal({(float)x, (float)(y + 100)}, "CONTROLS:", olc::YELLOW,
                        {scale, scale});
        DrawStringDecal({(float)x, (float)(y + 110)}, "P - Pause/Continue",
                        textColor, {scale, scale});
        DrawStringDecal({(float)x, (float)(y + 120)}, "S - Step (when paused)",
                        textColor, {scale, scale});
    }
};
