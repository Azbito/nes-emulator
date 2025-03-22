#include "PPU/Renderer.h"
#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


using PixelColor = uint32_t; // Definir um alias para uint32_t
using Color = ALLEGRO_COLOR; // Definir um alias para ALLEGRO_COLOR

Renderer::Renderer(int width, int height)
    : m_width(width), m_height(height), m_display(nullptr)
{
}

Renderer::~Renderer()
{
    if (m_display)
    {
        al_destroy_display(m_display);
    }
}

void Renderer::initializeDisplay()
{
    m_display = al_create_display(m_width, m_height);
    if (!m_display)
    {
        printf("Failed to create Allegro display!");
    }
}

void Renderer::clearScreen()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Renderer::renderFrame(const std::vector<PixelColor> &framebuffer)
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            PixelColor color = framebuffer[y * m_width + x];
            Color al_color = al_map_rgb((color >> 16) & 0xFF,
                                        (color >> 8) & 0xFF, color & 0xFF);
            al_put_pixel(x, y, al_color);
        }
    }
}

void Renderer::flipDisplay()
{
    al_flip_display();
}
