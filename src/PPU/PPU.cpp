#include "PPU/PPU.h"
#include "Bus/Bus.h"
#include <iostream>

void PPU::connectCartridge(std::shared_ptr<Cartridge> cart)
{
    cartridge = cart;
}

void PPU::connectBus(Bus *b)
{
    bus = b;
}

void PPU::writeMask(uint8_t value)
{
    m_mask = value;
}

uint8_t PPU::getMask() const
{
    return m_mask;
}

bool PPU::renderBackground() const
{
    return m_mask & Masks::SHOW_BACKGROUND_LEFT;
}

bool PPU::renderSprites() const
{
    return m_mask & Masks::SHOW_SPRITES;
}

uint8_t PPU::readStatus()
{
    uint8_t status = 0;

    if (m_VBlank)
        status |= 0x80;

    m_VBlank = false;

    m_writeToggle = false;

    return status;
}

const std::array<olc::Pixel, 256 * 240> &PPU::getFrameBuffer() const
{
    return framebuffer;
}

olc::Pixel getColorFromPalette(uint8_t paletteIndex)
{
    static olc::Pixel palette[4] = {
        olc::Pixel(84, 84, 84), olc::Pixel(152, 150, 164),
        olc::Pixel(128, 128, 128), olc::Pixel(255, 255, 255)};
    return palette[paletteIndex % 4];
}

void drawTile(const std::vector<uint8_t> &chr, uint8_t tileIndex, int screenX,
              int screenY, std::array<olc::Pixel, 256 * 240> &framebuffer)
{
    int baseAddr = tileIndex * 16;

    for (int row = 0; row < 8; row++)
    {
        uint8_t plane0 = chr[baseAddr + row];
        uint8_t plane1 = chr[baseAddr + row + 8];

        for (int col = 0; col < 8; col++)
        {
            uint8_t bit0 = (plane0 >> (7 - col)) & 0x01;
            uint8_t bit1 = (plane1 >> (7 - col)) & 0x01;
            uint8_t paletteIndex = (bit1 << 1) | bit0;

            olc::Pixel color = getColorFromPalette(paletteIndex);
            int pixelX = screenX + col;
            int pixelY = screenY + row;

            if (pixelX < 256 && pixelY < 240)
            {
                framebuffer[pixelY * 256 + pixelX] = color;
            }
        }
    }
}

void PPU::renderFrame()
{
    if (!cartridge)
        return;

    const auto &chr = cartridge->getCHRROM();

    for (int tileY = 0; tileY < 30; tileY++)
    {
        for (int tileX = 0; tileX < 32; tileX++)
        {
            uint8_t tileID = tileY * 32 + tileX;
            drawTile(chr, tileID, tileX * 8, tileY * 8, framebuffer);
        }
    }

    m_VBlank = true;
}
