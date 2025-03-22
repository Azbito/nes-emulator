#ifndef RENDERER_H
#define RENDERER_H

#include <allegro5/allegro.h>
#include <cstdint>
#include <vector>

class Renderer
{
  public:
    Renderer(int width, int height);
    ~Renderer();

    void initializeDisplay();
    void renderFrame(const std::vector<uint32_t> &framebuffer);
    void clearScreen();
    void flipDisplay();

  private:
    int m_width, m_height;
    ALLEGRO_DISPLAY *m_display;
};

#endif
