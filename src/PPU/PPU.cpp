#include "PPU/PPU.h"
#include <unordered_map>

PPU::PPU(olc::PixelGameEngine *pgeRef) : pge(pgeRef)
{
    m_vram.resize(0x1000);
    m_oam.resize(0x100);
}

void PPU::drawTile(int x, int y, uint8_t tileIndex)
{
    int row = y / 8;
    int col = x / 8;

    uint16_t attributeTableBase = 0x23C0;
    uint16_t attributeAddress =
        attributeTableBase + ((row / 4) * 8) + (col / 4);
    uint8_t attributeByte = getRegister(attributeAddress);

    int shift = ((row % 4) / 2) * 4 + ((col % 4) / 2) * 2;
    uint8_t paletteIndex = (attributeByte >> shift) & 0x03;

    uint16_t paletteBase = 0x3F00 + (paletteIndex * 4);

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            uint8_t pixelColor = getPixelFromTile(tileIndex, row, col);

            uint8_t finalColorIndex = getRegister(paletteBase + pixelColor);

            olc::Pixel color = getNESColor(finalColorIndex);

            pge->Draw(x + col, y + row, color);
        }
    }
}

void PPU::clock()
{
    m_cycle++;
    if (m_cycle >= 341)
    {
        m_cycle = 0;
        m_scanline++;

        if (m_scanline >= 261)
        {
            m_scanline = 0;
            setVerticalBlank(true);
        }
        else if (m_scanline == 241)
        {
            setVerticalBlank(true);
        }
        else if (m_scanline == 261)
        {
            setVerticalBlank(false);
        }
    }
}

uint8_t PPU::getPixelFromTile(uint8_t tileIndex, uint8_t row, uint8_t col)
{
    uint16_t tileAddress = 0x0000 + (tileIndex * 16) + (row * 2);
    uint8_t lowByte = getRegister(tileAddress);
    uint8_t highByte = getRegister(tileAddress + 1);

    uint8_t bit = 7 - col;
    uint8_t lowBit = (lowByte >> bit) & 0x01;
    uint8_t highBit = (highByte >> bit) & 0x01;

    return (highBit << 1) | lowBit;
}

void PPU::writeRegister(uint16_t address, uint8_t value)
{
    switch (address)
    {
    case 0x2000:
        ppuctrl.reg = value;
        break;
    case 0x2001:
        registers.PPUMASK = value;
        break;
    case 0x2006:
        if (m_addressLatch == 0)
        {
            m_tempAddress = (value << 8) | (m_tempAddress & 0x00FF);
            m_addressLatch = 1;
        }
        else
        {
            m_tempAddress = (m_tempAddress & 0xFF00) | value;
            m_address = m_tempAddress;
            m_addressLatch = 0;
        }
        break;
    case 0x2007:
        m_vram[m_address] = value;
        m_address += (ppuctrl.vram_address_inc ? 32 : 1);
        break;
    case 0x4014:
        uint8_t *src = (uint8_t *)0x0000 + (value << 8);
        for (int i = 0; i < 256; i++)
        {
            m_oam[i] = src[i];
        }
        break;
    }
}

void PPU::setPGE(olc::PixelGameEngine *pgeRef)
{
    pge = pgeRef;
}

void PPU::powerUp()
{
    ppuctrl.reg = 0x00;
    registers.PPUCTRL = 0x2000;
    registers.PPUMASK = 0x2001;
    registers.PPUSTATUS = 0x2002;
    registers.OAMADDR = 0x2003;
    registers.OAMDATA = 0x2004;
    registers.PPUSCROLL = 0x2005;
    registers.PPUADDR = 0x2006;
    registers.PPUDATA = 0x2007;
    registers.OAMDMA = 0x4014;

    m_status = 0xA0;
    m_addressLatch = 0;
    m_verticalBlank = false;
    m_address = 0;
    m_tempAddress = 0;
    m_cycle = 0;
    m_scanline = 241;

    m_vram.resize(0x4000);
    for (size_t i = 0; i < m_vram.size(); i++)
    {
        m_vram[i] = (i % 2 == 0) ? 0x00 : 0xFF;
    }

    m_oam.resize(256);
    std::fill(m_oam.begin(), m_oam.end(), 0xFF);
}

void PPU::renderFrame()
{
    for (int y = 0; y < getHeight(); y++)
    {
        for (int x = 0; x < getWidth(); x++)
        {
            drawTile(x, y, 0);
        }
    }
}

olc::Pixel PPU::getNESColor(uint8_t index)
{
    static const olc::Pixel palette[] = {
        olc::Pixel(84, 84, 84),    olc::Pixel(0, 30, 116),
        olc::Pixel(8, 16, 144),    olc::Pixel(48, 0, 136),
        olc::Pixel(68, 0, 100),    olc::Pixel(92, 0, 48),
        olc::Pixel(84, 4, 0),      olc::Pixel(60, 24, 0),
        olc::Pixel(32, 42, 0),     olc::Pixel(8, 58, 0),
        olc::Pixel(0, 64, 0),      olc::Pixel(0, 60, 0),
        olc::Pixel(0, 50, 60),     olc::Pixel(0, 0, 0),
        olc::Pixel(0, 0, 0),       olc::Pixel(0, 0, 0),
        olc::Pixel(152, 150, 152), olc::Pixel(8, 76, 196),
        olc::Pixel(48, 50, 236),   olc::Pixel(92, 30, 228),
        olc::Pixel(136, 20, 176),  olc::Pixel(160, 20, 100),
        olc::Pixel(152, 34, 32),   olc::Pixel(120, 60, 0),
        olc::Pixel(84, 90, 0),     olc::Pixel(40, 114, 0),
        olc::Pixel(8, 124, 0),     olc::Pixel(0, 118, 40),
        olc::Pixel(0, 102, 120),   olc::Pixel(0, 0, 0),
        olc::Pixel(0, 0, 0),       olc::Pixel(0, 0, 0),
        olc::Pixel(236, 238, 236), olc::Pixel(76, 154, 236),
        olc::Pixel(120, 124, 236), olc::Pixel(176, 98, 236),
        olc::Pixel(228, 84, 236),  olc::Pixel(236, 88, 180),
        olc::Pixel(236, 106, 100), olc::Pixel(212, 136, 32),
        olc::Pixel(160, 170, 0),   olc::Pixel(116, 196, 0),
        olc::Pixel(76, 208, 32),   olc::Pixel(56, 204, 108),
        olc::Pixel(56, 180, 204),  olc::Pixel(60, 60, 60),
        olc::Pixel(0, 0, 0),       olc::Pixel(0, 0, 0),
        olc::Pixel(236, 238, 236), olc::Pixel(168, 204, 236),
        olc::Pixel(188, 188, 236), olc::Pixel(212, 178, 236),
        olc::Pixel(236, 174, 236), olc::Pixel(236, 174, 212),
        olc::Pixel(236, 198, 176), olc::Pixel(228, 204, 144),
        olc::Pixel(204, 214, 120), olc::Pixel(180, 222, 120),
        olc::Pixel(168, 226, 144), olc::Pixel(152, 226, 180),
        olc::Pixel(160, 214, 228), olc::Pixel(160, 162, 160),
        olc::Pixel(0, 0, 0),       olc::Pixel(0, 0, 0)};
    return palette[index];
}

uint8_t PPU::getRegister(uint16_t address)
{
    if (address < 0x2000)
    {
        return m_chrROM[address];
    }

    if (address < 0x3F00)
    {
        uint16_t nametableAddress = address & 0x0FFF;
        return m_vram[nametableAddress];
    }

    if (address < 0x4000)
    {
        static const std::unordered_map<uint16_t, uint16_t> paletteMirror = {
            {0x0010, 0x0000},
            {0x0014, 0x0004},
            {0x0018, 0x0008},
            {0x001C, 0x000C}};

        uint16_t paletteAddress = address & 0x001F;
        auto it = paletteMirror.find(paletteAddress);
        if (it != paletteMirror.end())
        {
            paletteAddress = it->second;
        }

        return m_vram[paletteAddress];
    }

    return 0;
}
