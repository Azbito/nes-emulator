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

uint16_t PPU::mirrorAddress(uint16_t addr) const
{
    uint16_t offset = addr % 0x400;

    if (addr < 0x2000 || addr >= 0x3000)
    {
        return 0xFFFF;
    }

    MirrorType mirror = cartridge->getMirrorType();

    switch (mirror)
    {
    case MirrorType::VERTICAL:
        if (addr >= 0x2400 && addr <= 0x27FF)
            return 0x2000 + offset;
        return addr;

    case MirrorType::HORIZONTAL:
        if (addr >= 0x2800 && addr <= 0x2BFF)
            return 0x2400 + offset;
        return addr;

    case MirrorType::SINGLE_SCREEN_LO:
        return offset;

    case MirrorType::SINGLE_SCREEN_HI:
        return 0x1000 + offset;

    default:
        return 0xFFFF;
    }
}

void PPU::renderBackground()
{
    if (!cartridge)
        return;

    uint16_t v = m_VRAMAddress;

    for (int row = 0; row < 30; row++)
    {
        for (int col = 0; col < 32; col++)
        {
            uint8_t tileID = getTileIDAtVRAM(v);

            int screenX = col * 8;
            int screenY = row * 8;

            drawTileAtScreen(tileID, screenX, screenY);

            incrementCoarseX(v);
        }

        incrementY(v);
    }
}

void PPU::drawTile(const std::vector<uint8_t> &chr, uint8_t tileIndex,
                   int screenX, int screenY,
                   std::array<olc::Pixel, 256 * 240> &framebuffer)
{
    std::cout << "oi" << std::endl;
    std::cout << SHOW_ONLY_TILES_ID << std::endl;
    int baseAddr = tileIndex * 16;

#if SHOW_ONLY_TILES_ID
    int centerX = screenX + 4;
    int centerY = screenY + 4;
    printf("oiii");
    std::string text = std::to_string(tileIndex);
    pge->DrawStringDecal({(float)centerX, (float)centerY}, text, olc::WHITE);
#else
    for (int row = 0; row < 8; row++)
    {
        uint8_t plane0 = chr[baseAddr + row];
        uint8_t plane1 = chr[baseAddr + row + 8];

        for (int col = 0; col < 8; col++)
        {
            uint8_t bit0 = (plane0 >> (7 - col)) & 0x01;
            uint8_t bit1 = (plane1 >> (7 - col)) & 0x01;
            uint8_t paletteIndex = (bit1 << 1) | bit0;

            if (paletteIndex == 0)
                continue;

            olc::Pixel color = getColorFromPalette(paletteIndex);
            int pixelX = screenX + col;
            int pixelY = screenY + row;

            if (pixelX < 256 && pixelY < 240)
            {
                framebuffer[pixelY * 256 + pixelX] = color;
            }
        }
    }
#endif
}

olc::Pixel PPU::getColorFromPalette(uint8_t paletteIndex)
{
    static olc::Pixel palette[4] = {
        olc::Pixel(84, 84, 84), olc::Pixel(152, 150, 164),
        olc::Pixel(128, 128, 128), olc::Pixel(255, 255, 255)};
    return palette[paletteIndex % 4];
}

uint8_t PPU::getTileIDAtVRAM(uint16_t v) const
{
    uint16_t nametableAddress = mirrorAddress(v);

    if (nametableAddress == 0xFFFF)
    {
        return 0;
    }

    return getVRAM(nametableAddress);
}

void PPU::drawTileAtScreen(uint8_t tileID, int x, int y)
{
    const std::vector<uint8_t> &chr = cartridge->getCHRROM();
    drawTile(chr, tileID, x, y, framebuffer);
}

void PPU::incrementCoarseX(uint16_t &v)
{
    if ((v & 0x001F) == 31)
    {
        v &= ~0x001F;
        v ^= 0x0400;
    }
    else
    {
        v += 1;
    }
}

void PPU::incrementY(uint16_t &v)
{

    if ((v & 0x7000) != 0x7000)
    {
        v += 0x1000;
    }
    else
    {
        v &= ~0x7000;
        int coarseY = (v & 0x03E0) >> 5;
        if (coarseY == 29)
        {
            coarseY = 0;
            v ^= 0x0800;
        }
        else if (coarseY == 30)
        {
            coarseY = 0;
        }
        else
        {
            coarseY++;
        }
        v = (v & ~0x03E0) | (coarseY << 5);
    }
}

void PPU::writeData(uint8_t value)
{
    if (m_VRAMAddress < 0x4000)
    {
        uint16_t mirrorAddr = mirrorAddress(m_VRAMAddress);
        if (mirrorAddr != 0xFFFF)
        {
            m_VRAM[mirrorAddr] = value;
        }
    }

    m_VRAMAddress += (m_control & 0x04) ? 32 : 1;
}

uint8_t PPU::getVRAM(uint16_t address) const
{
    uint16_t mirrorVal = mirrorAddress(address);
    if (mirrorVal == 0xFFFF)
    {
        return 0;
    }

    return m_VRAM[mirrorVal];
}

uint8_t PPU::readData()
{
    uint8_t data = m_VRAMReadBuffer;
    m_VRAMReadBuffer = m_VRAM[m_VRAMAddress];

    if (m_VRAMAddress >= 0x3F00)
        data = m_VRAM[m_VRAMAddress];

    m_VRAMAddress += (m_control & 0x04) ? 32 : 1;

    return data;
}

void PPU::writeAddress(uint8_t value)
{
    if (!m_writeToggle)
    {
        m_tempAddress = (m_tempAddress & 0x00FF) | ((value & 0x3F) << 8);
        m_writeToggle = true;
    }
    else
    {
        m_tempAddress = (m_tempAddress & 0xFF00) | value;
        m_VRAMAddress = m_tempAddress;
        m_writeToggle = false;
    }
}

void PPU::writeControl(uint8_t value)
{
    m_control = value;

    m_baseNametable = value & 0x03;
    m_vramIncrement = (value & 0x04) ? 32 : 1;
    m_spritePatternAddr = (value & 0x08) ? 0x1000 : 0x0000;
    m_backgroundPatternAddr = (value & 0x10) ? 0x1000 : 0x0000;
    m_spriteSize = (value & 0x20) ? 16 : 8;
    m_generateNMI = value & 0x80;
}

void PPU::writeMask(uint8_t value)
{
    m_mask = value;
}

uint8_t PPU::getMask() const
{
    return m_mask;
}

bool PPU::showBackground() const
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
    {
        status |= 0x80;
    }

    m_VBlank = false;
    m_writeToggle = false;
    m_nmiOccurred = false;

    return status;
}

bool PPU::nmiTriggered() const
{
    return m_nmiOccurred;
}

void PPU::clearNmiFlag()
{
    m_nmiOccurred = false;
}

bool PPU::isFrameComplete()
{
    return m_frameComplete;
}

void PPU::resetFrameFlag()
{
    m_frameComplete = false;
}

int PPU::getCycles()
{
    return m_cycles;
}

void PPU::clock()
{
    m_cycles++;

    if (m_cycles >= 341)
    {
        m_cycles = 0;
        m_scanline++;

        if (m_scanline >= 262)
        {
            m_scanline = 0;
            m_frameComplete = true;
        }
    }

    if (m_scanline == 241 && m_cycles == 1)
    {
        m_VBlank = true;

        if (m_control & 0x80)
        {
            m_nmiOccurred = true;
        }
    }

    if (m_scanline == 261 && m_cycles == 1)
    {
        m_VBlank = false;
        m_nmiOccurred = false;
    }
}

uint8_t PPU::readMirrorVRAM(uint16_t addr)
{
    return m_VRAM[addr & 0x0FFF];
}

const std::array<olc::Pixel, 256 * 240> &PPU::getFrameBuffer() const
{
    return framebuffer;
}

void PPU::renderFrame()
{
    if (!cartridge)
        return;

    renderBackground();
}
