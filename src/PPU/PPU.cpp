#include "PPU/PPU.h"

#include <iostream>

#include "Bus/Bus.h"

void PPU::connectCartridge(std::shared_ptr<Cartridge> cart) {
    cartridge = cart;
}

void PPU::connectBus(Bus *b) {
    bus = b;
}

void PPU::writeCTRL(uint8_t value) {
    m_registers.CTRL = value;
    m_ctrl = value;
    m_openBus = value;

    uint8_t nametable = m_ctrl & 0x03;

    switch (nametable) {
        case 0x00:
            m_nametableBase = 0x2000;
            break;
        case 0x01:
            m_nametableBase = 0x2400;
            break;
        case 0x02:
            m_nametableBase = 0x2800;
            break;
        case 0x03:
            m_nametableBase = 0x2C00;
            break;
    }

    m_vramIncrementValue = (m_ctrl & 0x04) != 0 ? 32 : 1;
    m_spriteTableAddr = (m_ctrl & 0x08) != 0 ? 0x1000 : 0x0000;
    m_bgTableAddr = (m_ctrl & 0x10) != 0 ? 0x1000 : 0x0000;
    m_spriteSize = (m_ctrl & 0x20) != 0 ? 16 : 8;
    m_ppuMasterSlave = (m_ctrl & 0x40) != 0;
    m_nmiEnabled = (m_ctrl & 0x80) != 0;

    if (m_nmiEnabled) {
        m_nmiOutput = true;
    }
}

uint8_t PPU::readStatus() {
    uint8_t status = 0;

    if (m_status & Status::VBLANK_STARTED) {
        status |= Status::VBLANK_STARTED;
    }

    if (m_status & Status::SPRITE_OVERFLOW) {
        status |= Status::SPRITE_OVERFLOW;
    }

    if (m_status & Status::SPRITE_ZERO_HIT) {
        status |= Status::SPRITE_ZERO_HIT;
    }

    status |= (m_openBus & ((1 << 5) - 1));

    m_status &= ~Status::VBLANK_STARTED;

    m_openBus = status;

    return status;
}

void PPU::clock() {
    if (m_scanline < 240) {
        if (m_scanline >= 0 && m_scanline <= 239) {
            checkSpriteOverflow();
            checkSpriteZeroHit();
        }
    } else if (m_scanline == 241) {
        setVerticalBlank();
    }

    if (m_scanline == 261) {
        m_scanline = 0;
    } else {
        m_scanline++;
    }
}

bool PPU::isRenderingLine() {
    return (m_scanline >= 0 && m_scanline < 240);
};

void PPU::checkSpriteOverflow() {
    int spriteCount = 0;

    for (int i = 0; i < OAM_SIZE; i++) {
        if (isSpriteOnCurrentLine(i)) {
            spriteCount++;
        }

        if (spriteCount > 8) {
            m_status |= Status::SPRITE_OVERFLOW;
            break;
        }
    }
}

void PPU::checkSpriteZeroHit() {
    if (isSpriteZeroVisible() && isSpriteZeroCollidingWithBackground()) {
        m_status |= Status::SPRITE_ZERO_HIT;
    }
}

bool PPU::isSpriteOnCurrentLine(int index) {
    uint8_t spriteY = m_oam[index].y;
    return (spriteY >= m_scanline && spriteY < (m_scanline + 8));
}

bool PPU::isSpriteZeroVisible() {
    return isSpriteOnCurrentLine(0);
}

bool PPU::isSpriteZeroCollidingWithBackground() {
    uint8_t spriteZeroX = m_oam[0].x;
    uint8_t spriteZeroY = m_oam[0].y;

    return isSpriteOverlappingBackground(spriteZeroX, spriteZeroY);
};

bool PPU::isSpriteOverlappingBackground(uint8_t spriteX, uint8_t spriteY) {
    return (spriteX >= m_bgXStart && spriteX <= m_bgXEnd &&
            spriteY >= m_bgYStart && spriteY <= m_bgYEnd);
};

void PPU::setVerticalBlank() {
    m_status |= Status::VBLANK_STARTED;

    if (m_nmiEnabled) {
        m_nmiOccurred = true;
    }
}

bool PPU::isNMIEnabled() {
    return m_nmiEnabled;
}

void PPU::writeScroll(uint8_t value) {
    if (m_w == 0) {
        m_scrollX = value;
        m_w = 1;
    } else {
        m_scrollY = value;
        m_w = 0;
    }
}

void PPU::writeAddr(uint8_t value) {
    if (m_w == 0) {
        m_t = (m_t & 0x00FF) | ((uint16_t)value << 8);
        m_w = 1;
    } else {
        m_t = (m_t & 0xFF00) | value;
        m_v = m_t;
        m_w = 0;
    }
}
