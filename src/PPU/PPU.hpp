#ifndef PPU_HPP
#define PPU_HPP
#include <cstdint>

class PPU
{
  public:
    int width = 256;
    int height = 240;

    uint8_t status = 0x80;
    bool verticalBlank = false;

    void setVerticalBlank(bool value)
    {
        if (value)
        {
            status &= ~0x80;
            verticalBlank = false;
            return;
        }

        status |= 0x80;
        verticalBlank = true;
    }
};
#endif
