#pragma once

#include <array>
#include <cstdint>
#include <memory>

#include "Cartridge/Cartridge.h"
#include "Libraries/olcPixelGameEngine.h"
#include "config.h"

class Bus;
class Cartridge;

class PPU {
public:
    struct Registers {
        // 0x2000
        uint16_t CTRL = 0x2000;
        // 0x2001
        uint16_t MASK = 0x2001;
        // 0x2002
        uint16_t STATUS = 0x2002;
        // 0x2003
        uint16_t OAMADDR = 0x2003;
        // 0x2004
        uint16_t OAMDATA = 0x2004;
        // 0x2005
        uint16_t SCROLL = 0x2005;
        // 0x2006
        uint16_t ADDR = 0x2006;
        // 0x2007
        uint16_t DATA = 0x2007;
    };

    enum Status : uint8_t {
        PPU_OPEN_BUS = (1 << 5) - 1,  // 2C05
        SPRITE_OVERFLOW = 1 << 5,
        SPRITE_ZERO_HIT = 1 << 6,
        VBLANK_STARTED = 1 << 7  //! unreliable, use NMI instead
    };

    struct OAMEntry {
        uint8_t y;
        uint8_t x;
        uint8_t tile;
        uint8_t attr;
    };

    Registers registers;

    void connectCartridge(std::shared_ptr<Cartridge> cart);
    void connectBus(Bus *b);
    void clock();

    void checkSpriteOverflow();
    void checkSpriteZeroHit();

    void writeCTRL(uint8_t value);
    void writeScroll(uint8_t value);
    void writeAddr(uint8_t value);
    void setVerticalBlank();

    bool isNMIEnabled();
    bool isSpriteOnCurrentLine(int index);
    bool isSpriteZeroVisible();
    bool isSpriteZeroCollidingWithBackground();
    bool isSpriteOverlappingBackground(uint8_t spriteX, uint8_t spriteY);
    bool isRenderingLine();

    uint8_t readStatus();

private:
    std::shared_ptr<Cartridge> cartridge;
    Bus *bus = nullptr;

    static const int OAM_SIZE = 64;
    OAMEntry m_oam[OAM_SIZE];

    uint8_t m_bgXStart, m_bgYStart, m_bgXEnd, m_bgYEnd;

    //* $2000 - CTRL
    Registers m_registers;
    uint8_t m_ctrl;
    uint16_t m_nametableBase;
    uint8_t m_vramIncrementValue;
    uint16_t m_spriteTableAddr;
    uint16_t m_bgTableAddr;
    uint8_t m_spriteSize;
    bool m_ppuMasterSlave;
    bool m_nmiEnabled;

    bool m_nmiOutput = false;  //* 7th bit

    //* $2002 - STATUS
    uint8_t m_status = 0x00;
    int m_scanline = 0;

    //* $2005 - SCROLL & $2006 - ADDR
    uint8_t m_scrollX = 0;
    uint8_t m_scrollY = 0;
    uint16_t m_t = 0;
    uint16_t m_v = 0;
    uint8_t m_w = 0;

    bool m_nmiOccurred = false;
    uint8_t m_openBus = 0;
};
