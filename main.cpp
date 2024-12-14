#include "CPU6502.h"
#include "NES.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    NES nes;
    CPU6502 cpu;

    string rom;

    cout << "Please, insert a .nes file: ";
    cin >> rom;

    if (rom.empty() || !nes.loadRom(rom))
    {
        return 1;
    }

    cpu.mapMemory(vector<uint8_t>(nes.PRG.begin(), nes.PRG.end()));
    cpu.reset();

    while (true)
    {
        cpu.execute();
    }

    return 0;
}
