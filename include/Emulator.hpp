#include "CPU6502.h"
#include "NES.h"
#include "Window.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Emulator
{
public:
    int start()
    {
        NES nes;
        CPU6502 cpu;
        Window win;

        string rom;

        cout << "Please, insert a .nes file: ";
        cin >> rom;

        if (!win.init())
        {
            return 1;
        }

        if (rom.empty() || !nes.loadRom(rom))
        {
            win.close();
            return 1;
        }

        cpu.mapMemory(vector<uint8_t>(nes.PRG.begin(), nes.PRG.end()));
        cpu.reset();

        uint32_t frameBuffer[win.width * win.height];

        while (true)
        {
            cpu.execute();

            for (int i = 0; i < win.width * win.height; ++i)
            {
                frameBuffer[i] = 0xFF0000;
            }

            win.renderFrame(frameBuffer);

            SDL_Delay(16);
        }

        return 0;
    };
};