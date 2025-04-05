#ifndef PPU_H
#define PPU_H

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

    inline void setCHRROM(const std::vector<uint8_t> &chrData)
    {
        m_chrROM = chrData;
    }
    inline void setVerticalBlank(bool value)
    {
        m_verticalBlank = value;
    }

    void writeRegister(uint16_t address, uint8_t value);
    void setPGE(olc::PixelGameEngine *pgeRef);
    inline void setAddressLatch(uint8_t value)
    {
        m_addressLatch = value;
    }

    void renderFrame();
    void drawTile(int x, int y, uint8_t tileIndex);
    void powerUp();

    uint8_t getRegister(uint16_t address);
    uint8_t getPixelFromTile(uint8_t tileIndex, uint8_t row, uint8_t col);
    olc::Pixel getNESColor(uint8_t index);

    void clock();

    inline int getWidth() const
    {
        return 256;
    }
    inline int getHeight() const
    {
        return 240;
    }
    inline bool getVBlank() const
    {
        return m_verticalBlank;
    }
    inline uint8_t getStatus() const
    {
        return m_status;
    }
    inline uint8_t getAddressLatch() const
    {
        return m_addressLatch;
    }

  private:
    std::vector<uint8_t> m_chrROM;
    std::vector<uint8_t> m_vram;
    std::vector<uint8_t> m_oam;
    uint8_t m_status = 0;
    uint8_t m_addressLatch = 0;
    bool m_verticalBlank = false;
    uint16_t m_address = 0;
    uint16_t m_tempAddress = 0;
    uint16_t m_cycle = 0;
    uint16_t m_scanline = 0;
};

#endif
