#pragma once

#include <array>
#include <cstdint>
#include <memory>

#include "Cartridge/Cartridge.h"
#include "Libraries/olcPixelGameEngine.h"
#include "PPU/MirrorType.h"
#include "config.h"

class Bus;
class Cartridge;

class PPU {
public:
    enum Masks {
        GREY_SCALE = (1 << 0),
        SHOW_BACKGROUND_LEFT = (1 << 1),
        SHOW_SPRITES_LEFT = (1 << 2),
        SHOW_BACKGROUND = (1 << 3),
        SHOW_SPRITES = (1 << 4),
        EMPHASIZE_RED = (1 << 5),
        EMPHASIZE_GREEN = (1 << 6),
        EMPHASIZE_BLUE = (1 << 7)
    };

    void connectCartridge(std::shared_ptr<Cartridge> cart);
    void connectBus(Bus *b);

    void renderFrame();
    uint8_t readStatus();
    uint8_t readData();
    uint8_t getVRAM(uint16_t address) const;
    uint8_t readMirrorVRAM(uint16_t addr);

    void writeMask(uint8_t value);
    void writeControl(uint8_t value);
    void writeAddress(uint8_t value);
    void writeData(uint8_t value);

    void renderBackground();

    uint8_t getMask() const;
    int getCycles();

    bool showBackground() const;
    bool renderSprites() const;

    const std::array<olc::Pixel, 256 * 240> &getFrameBuffer() const;

    void clock();
    void resetFrameFlag();
    bool isFrameComplete();

    bool nmiTriggered() const;
    void clearNmiFlag();
    uint16_t mirrorAddress(uint16_t addr) const;
    uint8_t getTileIDAtVRAM(uint16_t v) const;
    olc::Pixel getColorFromPalette(uint8_t paletteIndex);

private:
    std::shared_ptr<Cartridge> cartridge;
    Bus *bus = nullptr;
    olc::PixelGameEngine *pge;

    std::array<olc::Pixel, 256 * 240> framebuffer;

    bool m_VBlank = false;

    uint8_t m_mask = 0x00;

    uint8_t m_control = 0x00;

    //* $2000 - PPU CTRL
    uint8_t m_baseNametable = 0;
    uint8_t m_vramIncrement = 1;
    uint16_t m_spritePatternAddr = 0x0000;
    uint16_t m_backgroundPatternAddr = 0x0000;
    uint8_t m_spriteSize = 8;
    bool m_generateNMI = false;

    //* $2006 & $2007
    uint16_t m_VRAMAddress = 0x0000;
    uint16_t m_tempAddress = 0x0000;
    bool m_writeToggle = false;  //* Address latch

    std::array<uint8_t, 0x4000> m_VRAM{};
    uint8_t m_VRAMReadBuffer = 0x00;

    //*
    int m_cycles, m_scanline = 0;
    bool m_frameComplete = false;
    //*

    bool m_nmiOccurred = false;

    void drawTile(const std::vector<uint8_t> &chr, uint8_t tileIndex,
                  int screenX, int screenY,
                  std::array<olc::Pixel, 256 * 240> &framebuffer);
    void incrementY(uint16_t &v);
    void drawTileAtScreen(uint8_t tileID, int x, int y);
    void incrementCoarseX(uint16_t &v);
};
