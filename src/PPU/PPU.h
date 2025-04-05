
#ifndef PPU_HPP
#define PPU_HPP

#include "Libraries/olcPixelGameEngine.h"
#include <cstdint>
#include <vector>

class PPU
{
  public:
    PPU(olc::PixelGameEngine *pgeRef);
    olc::PixelGameEngine *pge;

    struct Registers
    {
        uint16_t PPUCTRL = 0x2000;
        uint16_t PPUMASK = 0x2001;
        uint16_t PPUSTATUS = 0x2002;
        uint16_t OAMADDR = 0x2003;
        uint16_t OAMDATA = 0x2004;
        uint16_t PPUSCROLL = 0x2005;
        uint16_t PPUADDR = 0x2006;
        uint16_t PPUDATA = 0x2007;
        uint16_t OAMDMA = 0x4014;
    };

    union PPUCTRL
    {
        uint8_t reg;

        struct
        {
            uint8_t nametable : 2;
            uint8_t vram_address_inc : 1;
            uint8_t sprite_pattern_table : 1;
            uint8_t bg_pattern_table : 1;
            uint8_t sprite_size : 1;
            uint8_t ppu_master_slave : 1;
            uint8_t generate_nmi : 1;
        };
    };

    PPUCTRL ppuctrl;
    Registers registers;

    void setCHRROM(const std::vector<uint8_t> &chrData);
    void setVerticalBlank(bool value);

    void writeRegister(uint16_t address, uint8_t value);
    void setPGE(olc::PixelGameEngine *pgeRef);
    void setAddressLatch(uint8_t value);

    void renderFrame();
    void drawTile(int x, int y, uint8_t tileIndex);

    uint8_t getRegister(uint16_t address);
    uint8_t getPixelFromTile(uint8_t tileIndex, uint8_t row, uint8_t col);
    olc::Pixel getNESColor(uint8_t index);

    void clock();

    int getWidth() const;
    int getHeight() const;
    bool getVBlank() const;
    uint8_t getStatus() const;
    uint8_t getAddressLatch() const;

  private:
    int width = 256;
    int height = 240;

    std::vector<uint8_t> chrROM;

    uint8_t status = 0x80;
    bool verticalBlank = false;
    uint8_t memory[0x3FFF];
    uint16_t vramAddress = 0;
    uint8_t addressLatch = 0;
    uint8_t ppuDataBuffer = 0;

    int cycle = 0;
    int scanline = 0;
};

#endif
