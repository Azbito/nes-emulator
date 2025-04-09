#pragma once

#include "Cartridge/Cartridge.h"
#include "Libraries/olcPixelGameEngine.h"
#include <array>
#include <cstdint>
#include <memory>

class Bus;

class PPU
{
  public:
    enum Masks
    {
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
    void writeMask(uint8_t value);

    uint8_t getMask() const;

    bool renderBackground() const;
    bool renderSprites() const;

    const std::array<olc::Pixel, 256 * 240> &getFrameBuffer() const;

  private:
    std::shared_ptr<Cartridge> cartridge;
    Bus *bus = nullptr;

    std::array<olc::Pixel, 256 * 240> framebuffer;

    bool m_VBlank = false;

    //* this is used for $2005 and $2006
    bool m_writeToggle = false; //* Address latch

    uint8_t m_mask = 0x00;
};
