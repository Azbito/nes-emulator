#ifndef RENDER_H
#define RENDER_H

#include <allegro5/allegro.h>
#include <cstdint>
#include <vector>

class PPU
{
  public:
    PPU();
    ~PPU();

    void initializeFramebuffer(int width, int height);
    void updateFramebuffer(std::vector<uint32_t> &framebuffer);

    uint32_t *getFramebuffer();

  private:
    int m_width, m_height;
    std::vector<uint32_t> m_framebuffer;
};

#endif
