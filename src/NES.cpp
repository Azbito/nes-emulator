#include "NES.h"

// Character means sprites, tiles
// Program means instructions to run

bool NES::loadRom(const string &filename)
{
    ifstream file(filename, ios::binary);

    if (!file.is_open())
    {
        cerr << "Failed to open ROM file: " << filename << endl;
        return false;
    }

    uint8_t header[16];

    file.read(reinterpret_cast<char *>(header), 10);

    NES::verifyRom(header);

    size_t PRGSize = header[4] * 16 * 1024;
    size_t CHRSize = header[5] * 8 * 1024;

    NES::PRG.resize(PRGSize);
    file.read(reinterpret_cast<char *>(NES::PRG.data()), PRGSize);

    NES::CHR.resize(CHRSize);

    if (CHRSize > 0)
    {
        file.read(reinterpret_cast<char *>(NES::CHR.data()), CHRSize);
    }

    file.close();

    // cout << "ROM loaded successfully!" << endl;
    // cout << "PRG Size: " << PRGSize / 1024 << " KB" << endl;
    // cout << "CHR Size: " << CHRSize / 1024 << " KB" << endl;

    return true;
}

bool NES::verifyRom(const uint8_t *header)
{
    // cout << "ROM Header: ";
    // for (int i = 0; i < 16; i++)
    // {
    //     printf("%02X ", header[i]);
    // }
    // cout << endl;

    if (header[0] != 'N' || header[1] != 'E' || header[2] != 'S' || header[3] != 0x1A)
    {
        cerr << "Invalid iNES file!" << endl;
        return false;
    }

    return true;
}
