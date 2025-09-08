#include "PPU.h"
#include "Bus/Bus.h"
#include <cstring>

PPU::PPU() {
    std::memset(m_vram, 0, sizeof(m_vram));
    std::memset(m_oamData, 0, sizeof(m_oamData));
}

void PPU::connectBus(Bus *b) { m_bus = b; }
void PPU::connectCartridge(std::shared_ptr<Cartridge> cart) { m_cartridge = cart; }

uint8_t PPU::readStatus() {
    uint8_t ret = m_status;
    m_status &= 0x7F;
    m_latch = 0;
    return ret;
}

uint8_t PPU::readData() {
    uint16_t addr = mirrorAddress(m_v);
    uint8_t val = m_buffer;

    if (addr < 0x2000 && m_cartridge) {
        m_buffer = m_cartridge->getCHRROM()[addr];
    } else {
        m_buffer = m_vram[addr & 0x7FF];
    }

    m_v += (m_ctrl & 0x04) ? 32 : 1;
    return val;
}

uint8_t PPU::readOAMData() {
    return m_oamData[m_oamAddr];
}

void PPU::writeCtrl(uint8_t val) { m_ctrl = val; }
void PPU::writeMask(uint8_t val) { m_mask = val; }
void PPU::writeOAMAddr(uint8_t val) { m_oamAddr = val; }
void PPU::writeOAMData(uint8_t val) {
    m_oamData[m_oamAddr] = val;
    m_oamAddr++;
}

void PPU::writeOAMDMA(uint8_t page) {
    if (!m_bus) return;

    uint16_t baseAddr = page << 8;
    for (int i = 0; i < 256; i++) {
        m_oamData[i] = m_bus->read(baseAddr + i);
    }

    m_oamAddr = 0;
}

void PPU::writeScroll(uint8_t val) {
    if (m_latch == 0) { m_scrollX = val; m_latch = 1; }
    else { m_scrollY = val; m_latch = 0; }
}

void PPU::writeAddr(uint8_t val) {
    if (m_latch == 0) { m_v = (val & 0x3F) << 8; m_latch = 1; }
    else { m_v = (m_v & 0xFF00) | val; m_latch = 0; }
}

void PPU::writeData(uint8_t val) {
    uint16_t addr = mirrorAddress(m_v);
    printf("%04X\n", addr);
    if (addr >= 0x2000 && addr <= 0x2FFF) {
        m_vram[addr & 0x7FF] = val;
    }
    m_v += (m_ctrl & 0x04) ? 32 : 1;
}

uint16_t PPU::mirrorAddress(uint16_t addr) {
    if (addr >= 0x2000 && addr <= 0x2FFF) return addr & 0x0FFF;
    return addr;
}

void PPU::drawTile(uint8_t tileIndex, int x, int y, olc::PixelGameEngine* screen) {
    if (!m_cartridge) return;
    const auto &chr = m_cartridge->getCHRROM();
    if (chr.empty()) return;

    uint16_t offset = tileIndex * 16;
    for (int row = 0; row < 8; row++) {
        uint8_t p0 = chr[offset + row];
        uint8_t p1 = chr[offset + row + 8];

        for (int col = 0; col < 8; col++) {
            uint8_t bit0 = (p0 >> (7 - col)) & 1;
            uint8_t bit1 = (p1 >> (7 - col)) & 1;
            uint8_t colorIdx = (bit1 << 1) | bit0;

            olc::Pixel color = olc::BLACK;
            if (colorIdx == 1) color = olc::DARK_GREY;
            else if (colorIdx == 2) color = olc::GREY;
            else if (colorIdx == 3) color = olc::WHITE;

            screen->Draw(x + col, y + row, color);
        }
    }
}

void PPU::renderNametable(olc::PixelGameEngine* screen) {
    for (int row = 0; row < 30; row++) {
        for (int col = 0; col < 32; col++) {
            uint16_t addr = 0x2000 + row * 32 + col;
            uint8_t tileIndex = m_vram[addr & 0x7FF];
            if (tileIndex != 0) drawTile(tileIndex, col * 8, row * 8, screen);
        }
    }
}

void PPU::renderNametableToBuffer(uint32_t* buffer, int width, int height) {
    if (!m_cartridge) return;

    // percorre 30 linhas x 32 colunas = 960 tiles
    for (int row = 0; row < 30; row++) {
        for (int col = 0; col < 32; col++) {
            uint16_t addr = 0x2000 + row * 32 + col;
            uint8_t tileIndex = m_vram[addr & 0x7FF];

            // desenha cada tile na posição certa
            drawTileToBuffer(tileIndex, col * 8, row * 8,
                             buffer, width, height, 0);
        }
    }
}

void PPU::renderAllTilesToBuffer(uint32_t* buffer, int width, int height) {
    if (!m_cartridge) return;
    const auto &chrROM = m_cartridge->getCHRROM();
    if (chrROM.empty()) return;

    uint32_t palette[4] = {0xFF000000, 0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555};
    int tilesPerRow = width / 8;
    int totalTiles = chrROM.size() / 16;

    for (int tileIndex = 0; tileIndex < totalTiles; ++tileIndex) {
        int tileRow = tileIndex / tilesPerRow;
        int tileCol = tileIndex % tilesPerRow;
        uint16_t tileAddr = tileIndex * 16;

        for (int y = 0; y < 8; ++y) {
            uint8_t plane0 = chrROM[tileAddr + y];
            uint8_t plane1 = chrROM[tileAddr + y + 8];

            for (int x = 0; x < 8; ++x) {
                uint8_t bit0 = (plane0 >> (7 - x)) & 1;
                uint8_t bit1 = (plane1 >> (7 - x)) & 1;
                uint8_t colorIndex = (bit1 << 1) | bit0;

                int px = tileCol * 8 + x;
                int py = tileRow * 8 + y;

                if (px < width && py < height)
                    buffer[py * width + px] = palette[colorIndex];
            }
        }
    }
}

void PPU::renderSprites(uint32_t* buffer, int width, int height) {
    if (!m_cartridge) return;
    const auto &chr = m_cartridge->getCHRROM();
    if (chr.empty()) return;

    for (int i = 0; i < 64; i++) {
        uint8_t y = m_oamData[i * 4 + 0];
        uint8_t tileIndex = m_oamData[i * 4 + 1];
        uint8_t attr = m_oamData[i * 4 + 2];
        uint8_t x = m_oamData[i * 4 + 3];

        drawTileToBuffer(tileIndex, x, y, buffer, width, height, attr);
    }
}

void PPU::drawTileToBuffer(uint8_t tileIndex, int x, int y,
                           uint32_t* buffer, int width, int height,
                           uint8_t attr) {
    const auto &chr = m_cartridge->getCHRROM();
    if (chr.empty()) return;

    uint16_t offset = tileIndex * 16;
    uint32_t palette[4] = {0x00000000, 0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555};

    for (int row = 0; row < 8; row++) {
        uint8_t p0 = chr[offset + row];
        uint8_t p1 = chr[offset + row + 8];

        for (int col = 0; col < 8; col++) {
            uint8_t bit0 = (p0 >> (7 - col)) & 1;
            uint8_t bit1 = (p1 >> (7 - col)) & 1;
            uint8_t colorIdx = (bit1 << 1) | bit0;

            if (colorIdx == 0) continue;

            int px = x + col;
            int py = y + row;
            if (px < width && py < height) {
                buffer[py * width + px] = palette[colorIdx];
            }
        }
    }
}

