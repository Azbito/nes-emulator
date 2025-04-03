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

    std::vector<uint8_t> fileData;
    fileData.resize(fileSize);

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(fileData.data()), fileSize);
    file.close();

    if (!verify(fileData))
    {
        printf("\033[1;31m[SYSTEM] Invalid ROM.\033[0m\n");
        return false;
    }
    printf("\033[1;32m[SYSTEM] Valid ROM.\033[0m\n");

    size_t prgSize = 16384 * fileData[4];
    size_t chrSize = (fileSize > prgSize) ? (fileSize - prgSize) : 0;

    std::vector<uint8_t> prgData(fileData.begin(), fileData.begin() + prgSize);
    std::vector<uint8_t> chrData(fileData.begin() + prgSize, fileData.end());

    rom.setPRGData(prgData);
    rom.setCHRData(chrData);
    rom.setROMName(filename.c_str());

    printf("\033[1;32m[SYSTEM] ROM loaded successfully!\033[0m\n");

    return true;
}

bool ROMLoader::verify(const std::vector<uint8_t> &data) const
{
    printf("[SYSTEM] Validating ROM file... \n");

    if (data.size() < 16)
    {
        return false;
    }
    return data[0] == 'N' && data[1] == 'E' && data[2] == 'S' &&
           data[3] == 0x1A;
}
