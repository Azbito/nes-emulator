#pragma once
#include <cstdint>
#include <memory>
#include "Cartridge/Cartridge.h"
#include "Libraries/olcPixelGameEngine.h"

class Bus;
class Cartridge;

class PPU {
public:
    PPU();

    void connectBus(Bus *b);
    void connectCartridge(std::shared_ptr<Cartridge> cart);

    // Leitura/Escrita PPU
    uint8_t readStatus();
    uint8_t readData();
    void writeCtrl(uint8_t val);
    void writeMask(uint8_t value);
    void writeOAMAddr(uint8_t value);
    void writeOAMData(uint8_t value);
    void writeOAMDMA(uint8_t page);
    void writeScroll(uint8_t val);
    void writeAddr(uint8_t val);
    void writeData(uint8_t val);
    uint8_t readOAMData();

    // Renderização
    void renderNametable(olc::PixelGameEngine* screen);
    void renderAllTilesToBuffer(uint32_t* buffer, int width, int height);
    void drawTileToBuffer(uint8_t tileIndex, int x, int y,
                               uint32_t* buffer, int width, int height,
                               uint8_t attr);
    void renderSprites(uint32_t* buffer, int width, int height);
    void renderNametableToBuffer(uint32_t* buffer, int width, int height);
private:
    Bus *m_bus = nullptr;
    std::shared_ptr<Cartridge> m_cartridge;

    // Registradores e buffers
    uint16_t m_v = 0;      // endereço VRAM corrente
    uint8_t m_buffer = 0;  // buffer de leitura da VRAM
    uint8_t m_latch = 0;   // latch para $2005/$2006

    uint8_t m_ctrl = 0;
    uint8_t m_mask = 0;
    uint8_t m_status = 0;
    uint8_t m_oamAddr = 0;
    uint8_t m_scrollX = 0;
    uint8_t m_scrollY = 0;
    uint8_t m_oamData[256]{};
    uint8_t m_vram[0x800]{}; // 2KB VRAM interna

    void drawTile(uint8_t tileIndex, int x, int y, olc::PixelGameEngine* screen);
    uint16_t mirrorAddress(uint16_t addr);
};
