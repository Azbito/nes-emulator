#ifndef PPU_H
#define PPU_H

#include "Screen/Renderer.h"
#include <cstdint>
#include <vector>

class PPU
{
  public:
    PPU();
    ~PPU();

    struct Dimensions
    {
        int width;
        int height;
    };

    void initializeFramebuffer(int width, int height);
    Dimensions getDimensions();
    uint32_t *getFramebuffer();
    void renderBackground(Renderer &renderer,
                          const std::vector<uint8_t> &nametable,
                          const std::vector<uint8_t> &chrData);
    ALLEGRO_COLOR getNESColor(uint8_t index);

  private:
    int m_width;
    int m_height;
    std::vector<uint8_t> m_memory;
    std::vector<uint32_t> m_framebuffer;
};

#endif // PPU_H
