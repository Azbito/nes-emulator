#include "Screen/Renderer.h"
#include "ROM/PPU.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

Renderer::Renderer(int width, int height)
    : m_width(width), m_height(height), m_display(nullptr), m_buffer(nullptr)
{
}

Renderer::~Renderer()
{
    if (m_buffer)
        al_destroy_bitmap(m_buffer);
    if (m_display)
        al_destroy_display(m_display);
}

void Renderer::initializeDisplay()
{
    if (!al_init())
    {
        throw std::runtime_error("Failed to initialize Allegro");
    }

    m_display = al_create_display(m_width, m_height);
    if (!m_display)
    {
        throw std::runtime_error("Failed to create display");
    }

    m_buffer = al_create_bitmap(m_width, m_height);
    if (!m_buffer)
    {
        throw std::runtime_error("Failed to create buffer");
    }
}

void Renderer::clearScreen()
{
    al_set_target_bitmap(m_buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Renderer::flipDisplay()
{
    al_set_target_bitmap(al_get_backbuffer(m_display));
    al_draw_bitmap(m_buffer, 0, 0, 0);
    al_flip_display();
}

void Renderer::drawTile(int x, int y, uint8_t tileIndex,
                        const std::vector<uint8_t> &chrData)
{
    PPU ppu;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            uint8_t colorIndex = getTilePixelColor(tileIndex, i, j, chrData);

            ALLEGRO_COLOR color = ppu.getNESColor(colorIndex);
            al_put_pixel(x + i, y + j, color);
        }
    }
}
uint8_t Renderer::getTilePixelColor(uint8_t tileIndex, int row, int col,
                                    const std::vector<uint8_t> &chrData)
{
    uint8_t byte1 = chrData[tileIndex * 16 + row * 2];
    uint8_t byte2 = chrData[tileIndex * 16 + row * 2 + 1];

    uint8_t pixelBit = (col < 4) ? (byte1 >> (7 - col)) & 0x01
                                 : (byte2 >> (7 - (col - 4))) & 0x01;

    return pixelBit;
}
