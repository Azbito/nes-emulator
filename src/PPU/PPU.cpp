#include "PPU/PPU.h"
#include <allegro5/allegro.h>

PPU::PPU() : m_width(256), m_height(240)
{
    initializeFramebuffer(m_width, m_height);
}

PPU::~PPU()
{
}

void PPU::initializeFramebuffer(int width, int height)
{
    this->m_width = width;
    this->m_height = height;
    m_framebuffer.resize(width * height);
}

void PPU::updateFramebuffer(std::vector<uint32_t> &framebuffer)
{
    framebuffer.resize(m_width * m_height);
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            ALLEGRO_COLOR color = al_map_rgb(255, 0, 0); // red color
            unsigned char r, g, b;
            al_unmap_rgb(color, &r, &g, &b); // Unpacks the RGB values

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
