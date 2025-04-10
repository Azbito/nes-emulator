#include "Cartridge/Cartridge.h"
#include <cstdio>
#include <stdexcept>

Cartridge::Cartridge(const std::vector<uint8_t> &romData)
{
    if (romData.size() < 16)
        throw std::runtime_error("ROM muito pequena: faltando cabeçalho");

    uint8_t prgRomChunks = romData[4];
    uint8_t chrRomChunks = romData[5];

    uint8_t flags6 = romData[6];
    bool verticalMirroring = false;

    mirroring =
        verticalMirroring ? MirrorType::VERTICAL : MirrorType::HORIZONTAL;

    size_t prgRomSize = prgRomChunks * 0x4000;
    size_t chrRomSize = chrRomChunks * 0x2000;

    size_t prgStart = 16;
    size_t prgEnd = prgStart + prgRomSize;

    if (romData.size() < prgEnd)
        throw std::runtime_error("ROM inválida: PRG-ROM incompleta");

    prgROM = std::vector<uint8_t>(romData.begin() + prgStart,
                                  romData.begin() + prgEnd);

    if (chrRomSize > 0 && romData.size() >= prgEnd + chrRomSize)
    {
        chrROM = std::vector<uint8_t>(romData.begin() + prgEnd,
                                      romData.begin() + prgEnd + chrRomSize);
    }
    else
    {

        chrROM = std::vector<uint8_t>(0x2000, 0);
    }
}

MirrorType Cartridge::getMirrorType() const
{
    return mirroring;
}

const std::vector<uint8_t> &Cartridge::getCHRROM() const
{
    return chrROM;
}

uint8_t Cartridge::readPRG(uint16_t address)
{
    if (address < 0x8000)
        return 0x00;

    uint32_t prgAddress = address - 0x8000;

    if (prgROM.size() == 0x4000)
        prgAddress %= 0x4000;

    if (prgAddress < prgROM.size())
        return prgROM[prgAddress];

    return 0x00;
}

void Cartridge::writePRG([[maybe_unused]] uint16_t address,
                         [[maybe_unused]] uint8_t value)
{
}
