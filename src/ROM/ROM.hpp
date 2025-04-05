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

    uint8_t getPRGBanks() const
    {
        return m_prgBanks;
    }

    uint8_t getCHRBanks() const
    {
        return m_chrBanks;
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
    void setPRGBanks(uint8_t value)
    {
        m_prgBanks = value;
    }
    void setCHRBanks(uint8_t value)
    {
        m_chrBanks = value;
    }

    void setROMName(const char *value)
    {
        size_t length = strlen(value);
        size_t copyLength =
            length < sizeof(m_romName) - 1 ? length : sizeof(m_romName) - 1;
        memcpy(m_romName, value, copyLength);
        m_romName[copyLength] = '\0';
    }

  private:
    std::vector<uint8_t> m_PRGData;
    std::vector<uint8_t> m_CHRData;
    uint8_t m_prgBanks = 0;
    uint8_t m_chrBanks = 0;
    char m_romName[512];
};

#endif
