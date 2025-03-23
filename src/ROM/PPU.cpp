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

PPU::Dimensions PPU::getDimensions()
{
    return {m_width, m_height};
}

void PPU::initializeFramebuffer(int width, int height)
{
    this->m_width = width;
    this->m_height = height;
    m_framebuffer.resize(width * height);
}

uint32_t *PPU::getFramebuffer()
{
    return reinterpret_cast<uint32_t *>(m_framebuffer.data());
}

void PPU::renderBackground(Renderer &renderer,
                           const std::vector<uint8_t> &nametable,
                           const std::vector<uint8_t> &chrData)
{
    for (int row = 0; row < 30; ++row)
    {
        for (int col = 0; col < 32; ++col)
        {
            uint8_t tileIndex = nametable[row * 32 + col];

            renderer.drawTile(col * 8, row * 8, tileIndex, chrData);
        }
    }
}
