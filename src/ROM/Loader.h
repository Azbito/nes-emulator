#ifndef ROM_LOADER_H
#define ROM_LOADER_H

#include <cstdint>
#include <fstream>
#include <vector>

class ROMLoader
{
  public:
    ROMLoader() = default;

    bool load(const std::string &filename);
    bool verify() const;
    const std::vector<uint8_t> &getData() const;

  private:
    std::vector<uint8_t> m_data;
};

#endif
