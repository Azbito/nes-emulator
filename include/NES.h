#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

class NES
{
public:
    vector<uint8_t> PRG;
    vector<uint8_t> CHR;

    bool loadRom(const string &filename);
    bool verifyRom(const uint8_t *header);
};