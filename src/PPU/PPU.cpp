#include "PPU/PPU.h"

PPU::PPU(olc::PixelGameEngine *pgeRef) : pge(pgeRef)
{
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

int PPU::getWidth() const
{
    return this->width;
};

int PPU::getHeight() const
{
    return this->height;
};

void PPU::clock()
{
    cycle++;
    if (cycle >= 341)
    {
        cycle = 0;
        scanline++;
        if (scanline == 241)
        {
            verticalBlank = true;
        }
        else if (scanline >= 262)
        {
            scanline = 0;
            verticalBlank = false;
        }
    }
}

uint8_t PPU::getPixelFromTile(uint8_t tileIndex, uint8_t row, uint8_t col)
{
    uint16_t tileAddress = tileIndex * 16;

    uint8_t plane0 = chrROM[tileAddress + row];
    uint8_t plane1 = chrROM[tileAddress + row + 8];

    uint8_t bit0 = (plane0 >> (7 - col)) & 1;
    uint8_t bit1 = (plane1 >> (7 - col)) & 1;

    return (bit1 << 1) | bit0;
}

void PPU::setCHRROM(const std::vector<uint8_t> &chrData)
{
    chrROM = chrData;
}

void PPU::setVerticalBlank(bool value)
{
    if (value)
    {
        status &= ~0x80;
        verticalBlank = false;
        return;
    }

    status |= 0x80;
    verticalBlank = true;
}

void PPU::setAddressLatch(uint8_t value)
{
    addressLatch = value;
}

uint8_t PPU::getAddressLatch() const
{
    return this->addressLatch;
}

uint8_t PPU::getStatus() const
{
    return this->status;
}

bool PPU::getVBlank() const
{
    return this->verticalBlank;
}

uint8_t PPU::getRegister(uint16_t address)
{
    if (address == registers.PPUSTATUS)
    {
        uint8_t value = status;
        addressLatch = 0;
        status &= ~0x80;
        return value;
    }
    else if (address == registers.PPUDATA)
    {
        uint8_t data;

        if (vramAddress < 0x3F00)
        {
            data = ppuDataBuffer;
            ppuDataBuffer = memory[vramAddress];
        }
        else
        {
            data = memory[vramAddress];
        }

        vramAddress += (ppuctrl.vram_address_inc ? 32 : 1);

        return data;
    }

    return memory[address];
}

void PPU::writeRegister(uint16_t address, uint8_t value)
{
    if (address == registers.PPUCTRL)
    {
        ppuctrl.reg = value;
    }

    if (address == registers.PPUADDR)
    {
        if (addressLatch == 0)
        {
            vramAddress = (value << 8) | (vramAddress & 0x00FF);
            addressLatch = 1;
        }
        else
        {
            vramAddress = (vramAddress & 0xFF00) | value;
            addressLatch = 0;
        }
    }

    if (address == registers.PPUDATA)
    {
        memory[vramAddress] = value;

        if (ppuctrl.vram_address_inc)
            vramAddress += 32;
        else
            vramAddress += 1;
    }
    memory[address] = value;
}

void PPU::setPGE(olc::PixelGameEngine *pgeRef)
{
    pge = pgeRef;
}

void PPU::renderFrame()
{
    uint8_t memoryValue = getRegister(0x3F00);
    olc::Pixel bgColor = getNESColor(memoryValue);
    pge->Clear(bgColor);

    uint16_t nameTableBase = registers.PPUCTRL + (ppuctrl.nametable * 0x400);

    for (int row = 0; row < 30; row++)
    {
        for (int col = 0; col < 32; col++)
        {
            uint16_t nameTableAddr = nameTableBase + (row * 32) + col;
            uint8_t tileIndex = getRegister(nameTableAddr);
            drawTile(col * 8, row * 8, tileIndex);
        }
    }
}

olc::Pixel PPU::getNESColor(uint8_t index)
{
    static const olc::Pixel NESPalette[64] = {olc::GREY,
                                              olc::BLUE,
                                              olc::DARK_BLUE,
                                              olc::MAGENTA,
                                              olc::DARK_MAGENTA,
                                              olc::RED,
                                              olc::DARK_RED,
                                              olc::VERY_DARK_RED,
                                              olc::YELLOW,
                                              olc::DARK_YELLOW,
                                              olc::VERY_DARK_YELLOW,
                                              olc::GREEN,
                                              olc::DARK_GREEN,
                                              olc::VERY_DARK_GREEN,
                                              olc::CYAN,
                                              olc::DARK_CYAN,
                                              olc::VERY_DARK_CYAN,
                                              olc::WHITE,
                                              olc::BLACK,
                                              olc::BLANK,
                                              olc::GREY,
                                              olc::BLUE,
                                              olc::DARK_BLUE,
                                              olc::MAGENTA,
                                              olc::DARK_MAGENTA,
                                              olc::RED,
                                              olc::DARK_RED,
                                              olc::VERY_DARK_RED,
                                              olc::YELLOW,
                                              olc::DARK_YELLOW,
                                              olc::VERY_DARK_YELLOW,
                                              olc::GREEN,
                                              olc::DARK_GREEN,
                                              olc::VERY_DARK_GREEN,
                                              olc::CYAN,
                                              olc::DARK_CYAN,
                                              olc::VERY_DARK_CYAN,
                                              olc::WHITE,
                                              olc::BLACK,
                                              olc::BLANK,
                                              olc::GREY,
                                              olc::BLUE,
                                              olc::DARK_BLUE,
                                              olc::MAGENTA,
                                              olc::DARK_MAGENTA,
                                              olc::RED,
                                              olc::DARK_RED,
                                              olc::VERY_DARK_RED,
                                              olc::YELLOW,
                                              olc::DARK_YELLOW,
                                              olc::VERY_DARK_YELLOW,
                                              olc::GREEN,
                                              olc::DARK_GREEN,
                                              olc::VERY_DARK_GREEN,
                                              olc::CYAN,
                                              olc::DARK_CYAN};

    if (index < 64)
    {
        return NESPalette[index];
    }

    return olc::BLACK;
}
