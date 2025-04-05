#include "ROM/Loader.h"
#include <fstream>
#include <iostream>

bool ROMLoader::load(const std::string &filename, ROM &rom)
{
    printf("[SYSTEM] Running emulator... \n");

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        return false;
    }

    size_t fileSize = file.tellg();
    std::vector<uint8_t> fileData(fileSize);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(fileData.data()), fileSize);
    file.close();

    if (!verify(fileData))
    {
        printf("\033[1;31m[SYSTEM] Invalid ROM.\033[0m\n");
        return false;
    }

    printf("\033[1;32m[SYSTEM] Valid ROM.\033[0m\n");

    const size_t headerSize = 16;
    uint8_t prgBanks = fileData[4];
    uint8_t chrBanks = fileData[5];
    size_t prgSize = 16384 * prgBanks;
    size_t chrSize = 8192 * chrBanks;

    if (fileSize < headerSize + prgSize + chrSize)
    {
        printf(
            "\033[1;31m[SYSTEM] ROM file is incomplete or corrupted.\033[0m\n");
        return false;
    }

    std::vector<uint8_t> prgData(fileData.begin() + headerSize,
                                 fileData.begin() + headerSize + prgSize);
    std::vector<uint8_t> chrData(fileData.begin() + headerSize + prgSize,
                                 fileData.begin() + headerSize + prgSize +
                                     chrSize);

    rom.setPRGData(prgData);
    rom.setCHRData(chrData);
    rom.setPRGBanks(prgBanks);
    rom.setCHRBanks(chrBanks);
    rom.setROMName(filename.c_str());

    printf("\033[1;32m[SYSTEM] ROM loaded successfully!\033[0m\n");
    return true;
}

bool ROMLoader::verify(const std::vector<uint8_t> &data) const
{
    printf("[SYSTEM] Validating ROM file... \n");

    if (data.size() < 16)
        return false;

    return data[0] == 'N' && data[1] == 'E' && data[2] == 'S' &&
           data[3] == 0x1A;
}
