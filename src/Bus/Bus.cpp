#include "Bus/Bus.h"
#include "Cartridge/Cartridge.h"
#include "PPU/PPU.h"
#include <cstdio>
#include <cstring>

Bus::Bus()
{
    std::memset(ram, 0, sizeof(ram));
    cpu = nullptr;
}

void Bus::connectCPU(CPU6502 *cpuPtr)
{
    cpu = cpuPtr;
}

void Bus::connectPPU(PPU *ppuPtr)
{
    ppu = ppuPtr;
}

void Bus::connectCartridge(std::shared_ptr<Cartridge> cart)
{
    cartridge = cart;
}

uint8_t Bus::read(uint16_t address)
{
    if (address < 0x2000)
        return ram[address % 0x0800];

    if (address >= 0x8000 && cartridge)
        return cartridge->readPRG(address);

    if (address == 0x2002)
        return ppu->readStatus();

    return 0x00;
}

void Bus::write(uint16_t address, uint8_t value)
{
    if (address >= 0x8000 && cartridge)
    {
        return;
    }

    if (address == 0x2001)
    {
        ppu->writeMask(value);
        return;
    }

    if (address < 0x2000)
    {
        ram[address % 0x0800] = value;
        return;
    }

    if (address >= 0x8000 && cartridge)
    {
        cartridge->writePRG(address, value);
        return;
    }

    printf("ADDR WR: $%04X\n", address);
    system("pause");
}
