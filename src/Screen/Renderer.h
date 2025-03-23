#ifndef RENDERER_H
#define RENDERER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <cstdint>
#include <vector>

class Renderer
{
  public:
    Renderer(int width, int height);
    ~Renderer();

    void initializeDisplay();
    void clearScreen();
    void flipDisplay();
    void drawPixel(int x, int y, uint8_t color);
    void drawTile(int x, int y, uint8_t tileIndex,
                  const std::vector<uint8_t> &chrData);
    uint8_t getTilePixelColor(uint8_t tileIndex, int x, int y,
                              const std::vector<uint8_t> &chrData);

  private:
    int m_width, m_height;
    ALLEGRO_DISPLAY *m_display;
    ALLEGRO_BITMAP *m_buffer;
};

#endif
