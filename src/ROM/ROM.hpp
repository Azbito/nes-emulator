#ifndef ROM_HPP
#define ROM_HPP

#include <cstdint>
#include <cstring>
#include <vector>


class ROM
{
  public:
    const std::vector<uint8_t> &getPRGData() const
    {
        return m_PRGData;
    }

    const std::vector<uint8_t> &getCHRData() const
    {
        return m_CHRData;
    }

    const char *getROMName() const
    {
        return m_romName;
    }

    void setPRGData(const std::vector<uint8_t> &value)
    {
        m_PRGData = value;
    }

    void setCHRData(const std::vector<uint8_t> &value)
    {
        m_CHRData = value;
    }

    void setROMName(const char *value)
    {
        size_t length = strlen(value);
        size_t copyLength =
            length < sizeof(m_romName) - 1 ? length : sizeof(m_romName) - 1;

        memcpy(m_romName, value, copyLength);
        m_romName[copyLength] = '\0';
    }

    std::vector<uint8_t> getNametableData() const
    {
        std::vector<uint8_t> nametableData;

        for (size_t i = 0x2000; i < 0x2400; ++i)
        {
            nametableData.push_back(m_PRGData[i]);
        }

        for (size_t i = 0x2400; i < 0x2800; ++i)
        {
            nametableData.push_back(m_PRGData[i]);
        }

        return nametableData;
    }

  private:
    std::vector<uint8_t> m_PRGData;
    std::vector<uint8_t> m_CHRData;
    char m_romName[512];
};

#endif
