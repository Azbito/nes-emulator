#include "CPU6502.hpp"
#include "NES.h"
#include "Window.h"
#include "PPU.h"
#include "Assembly.h"

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;

class Emulator
{
public:
    int start()
    {
        CPU6502 *cpu = new CPU6502();

        Assembly assembly(cpu);

        cpu->setAssembly(&assembly);

        NES nes;
        PPU ppu;
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

        cpu->mapMemory(vector<uint8_t>(nes.PRG.begin(), nes.PRG.end()));
        cpu->reset();
        vector<uint32_t> frameBuffer(win.width * win.height);

        auto lastTime = chrono::steady_clock::now();
        while (true)
        {
            auto currentTime = chrono::steady_clock::now();
            auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count();
            int cyclesToExecute = elapsedTime * 1.79;

            while (cyclesToExecute > 0)
            {
                cpu->execute();
                cout << "Executing opcode at PC: " << hex << cpu->getPC() << dec << endl;
                cyclesToExecute -= cpu->getCycles();
            }

            ppu.renderFrame(frameBuffer);
            win.renderFrame(frameBuffer.data());

            lastTime = currentTime;
            SDL_Delay(16);
        }

        delete cpu;
        return 0;
    }
};
