#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <vector>

class Cartridge {
public:
    Cartridge(const std::vector<uint8_t> &romData);
    [[nodiscard]]
    const std::vector<uint8_t> &getCHRROM() const;
    [[nodiscard]]
    const std::vector<uint8_t> &getPRGROM() const;
    [[nodiscard]]
    uint8_t readPRG(uint16_t address);
    void writePRG(uint16_t address, uint8_t value);
    [[nodiscard]]
    bool isHorizontalMirror() const { return m_horizontalMirror; }

private:
    std::vector<uint8_t> prgROM;
    std::vector<uint8_t> chrROM;
    bool m_horizontalMirror = false;
};

#endif
