#include <windows.h>
#include "Emulator.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    Emulator emu;

    emu.start();

    return 0;
}
