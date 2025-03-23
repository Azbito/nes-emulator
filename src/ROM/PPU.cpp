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
