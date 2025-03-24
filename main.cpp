#include "Emulator/Emulator.hpp"
#include <iostream>


int main(int argc, char *argv[])
{
    Emulator emu;

    if (emu.Construct(256, 240, 2, 2))
    {
        emu.Start();
    }

    return 0;
}
