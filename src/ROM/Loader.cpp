#include "ROM/Loader.h"

bool ROMLoader::load(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        return false;
    }

    size_t fileSize = file.tellg();

    m_data.resize(fileSize);

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(m_data.data()), fileSize);
    file.close();

    if (!verify())
    {
        return false;
    }

    return true;
}

const std::vector<uint8_t> &ROMLoader::getData() const
{
    return m_data;
}

bool ROMLoader::verify() const
{
    if (m_data.size() < 16)
    {
        return false;
    }

    return m_data[0] == 'N' && m_data[1] == 'E' && m_data[2] == 'S' &&
           m_data[3] == 0x1A;
}
