#include "ROM/PPU.h"
#include <allegro5/allegro.h>
#include <cstdio>

PPU::PPU() : m_width(256), m_height(240)
{
    initializeFramebuffer(m_width, m_height);
}

PPU::~PPU()
{
}

void PPU::loadCHR(const std::vector<uint8_t> &romData, size_t offset)
{
    memcpy(CHRMemory, &romData[offset], 8192);
}

void PPU::initializeFramebuffer(int width, int height)
{
    this->m_width = width;
    this->m_height = height;
    m_framebuffer.resize(width * height);
}

ALLEGRO_COLOR PPU::getNESColor(uint8_t index)
{
    static const uint32_t nesPalette[64] = {
        0x7C7C7C, 0x0000FC, 0x0000BC, 0x4428BC, 0x940084, 0xA80020, 0xA81000,
        0x881400, 0x503000, 0x007800, 0x006800, 0x005800, 0x004058, 0x000000,
        0x000000, 0x000000, 0xBCBCBC, 0x0078F8, 0x0058F8, 0x6844FC, 0xD800CC,
        0xE40058, 0xF83800, 0xE45C10, 0xAC7C00, 0x00B800, 0x00A800, 0x00A844,
        0x008888, 0x000000, 0x000000, 0x000000, 0xF8F8F8, 0x3CBCFC, 0x6888FC,
        0x9878F8, 0xF878F8, 0xF85898, 0xF87858, 0xFCA044, 0xF8B800, 0xB8F818,
        0x58D854, 0x58F898, 0x00E8D8, 0x787878, 0x000000, 0x000000, 0xFCFCFC,
        0xA4E4FC, 0xB8B8F8, 0xD8B8F8, 0xF8B8F8, 0xF8A4C0, 0xF0D0B0, 0xFCE0A8,
        0xF8D878, 0xD8F878, 0xB8F8B8, 0xB8F8D8, 0x00FCFC, 0xF8D8F8, 0x000000,
        0x000000};

    uint32_t rgb = nesPalette[index % 64];
    return al_map_rgb((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

void PPU::updateFramebuffer(std::vector<uint32_t> &framebuffer)
{
    framebuffer.resize(m_width * m_height);

    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            size_t targetMemory = y * m_width + x;

            uint8_t pixelValue = getMemory(targetMemory);
            ALLEGRO_COLOR color = getNESColor(pixelValue);
            unsigned char r, g, b;
            al_unmap_rgb(color, &r, &g, &b);
            printf("color: #%02X%02X%02X\n", r, g, b);
            framebuffer[y * m_width + x] = (static_cast<uint32_t>(r) << 16) |
                                           (static_cast<uint32_t>(g) << 8) |
                                           static_cast<uint32_t>(b);
        }
    }
}

uint32_t *PPU::getFramebuffer()
{
    return reinterpret_cast<uint32_t *>(m_framebuffer.data());
}
