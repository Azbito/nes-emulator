#include "Bus/Bus.h"

#include <cstdio>
#include <cstring>

#include "Cartridge/Cartridge.h"
#include "PPU/PPU.h"

Bus::Bus() {
    std::memset(ram, 0, sizeof(ram));
    cpu = nullptr;
}

void Bus::connectCPU(CPU6502 *cpuPtr) {
    cpu = cpuPtr;
}

void Bus::connectPPU(PPU *ppuPtr) {
    ppu = ppuPtr;
}

void Bus::connectCartridge(std::shared_ptr<Cartridge> cart) {
    cartridge = cart;
}

uint8_t Bus::read(uint16_t address) {
    if (address < 0x2000)
        return ram[address % 0x0800];

    if (address >= 0x8000 && cartridge)
        return cartridge->readPRG(address);

    if (address >= ppu->registers.STATUS) {
        return ppu->readStatus();
    }

    return 0x00;
}

void Bus::write(uint16_t address, uint8_t value) {
    if (address >= 0x8000 && cartridge) {
        cartridge->writePRG(address, value);
        return;
    }

    if (address == ppu->registers.CTRL) {
        ppu->writeCTRL(value);
        return;
    }

    if (address == ppu->registers.MASK) {
        return;
    }

    if (address == ppu->registers.SCROLL) {
        ppu->writeScroll(value);
        return;
    }

    if (address == ppu->registers.ADDR) {
        ppu->writeAddr(value);
        return;
    }
}
