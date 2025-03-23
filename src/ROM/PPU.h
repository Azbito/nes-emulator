#ifndef PPU_H
#define PPU_H

#include <allegro5/allegro.h>
#include <cstdint>
#include <vector>

#define KB_8 8192

class PPU
{
  public:
    PPU();
    ~PPU();
    uint8_t CHRMemory[KB_8];

    void loadCHR(const std::vector<uint8_t> &romData, size_t offset);
    void initializeFramebuffer(int width, int height);
    void updateFramebuffer(std::vector<uint32_t> &framebuffer);
    ALLEGRO_COLOR getNESColor(uint8_t index);
    uint32_t *getFramebuffer();

    void setMemory(size_t i, uint8_t value)
    {
        m_memory[i] = value;
    }

    uint8_t getMemory(size_t i)
    {
        return m_memory[i];
    }

  private:
    int m_width, m_height;
    std::vector<uint32_t> m_framebuffer;
    uint8_t m_memory[0x2000];
};

#endif
