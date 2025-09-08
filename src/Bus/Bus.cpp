#include "Bus/Bus.h"

#include <cstdio>
#include <cstring>

#include "CPU/CPU6502.h"
#include "Cartridge/Cartridge.h"
#include "Log/Log.hpp"
#include "PPU/PPU.h"
#include "Utils/main.hpp"

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
    if (address < 0x2000) {
        return ram[address & 0x07FF];
    }

    if (address < 0x4000 && ppu) {
        uint16_t reg = 0x2000 + (address & 0x0007);
        switch (reg) {
            case 0x2002: {
                return ppu->readStatus();
            };
            case 0x2004: {
                return ppu->readOAMData();
            };
            case 0x2007: {
                return ppu->readData();
            };
            default: return 0;
        }
    }

    if (address < 0x4020) {
        return 0;
    }

    if (address >= 0x8000 && cartridge) {
        return cartridge->readPRG(address);
    }

    return 0;
}

void Bus::write(uint16_t address, uint8_t value) {
    if (address < 0x2000) {
        ram[address & 0x07FF] = value;
        return;
    }


    if (address < 0x4000 && ppu) {
        uint16_t reg = 0x2000 + (address & 0x0007);

        switch (reg) {
            case 0x2000: ppu->writeCtrl(value); break;   // PPUCTRL
            case 0x2001: ppu->writeMask(value); break;   // PPUMASK
            case 0x2003: ppu->writeOAMAddr(value); break; // OAMADDR
            case 0x2004: ppu->writeOAMData(value); break; // OAMDATA
            case 0x2005: ppu->writeScroll(value); break; // PPUSCROLL (Wx2)
            case 0x2006: ppu->writeAddr(value); break;   // PPUADDR (Wx2)
            case 0x2007: ppu->writeData(value); break;   // PPUDATA
            default: break;
        }
        return;
    }

    if (address == 0x4014 && ppu) {
        ppu->writeOAMDMA(value);
        return;
    }

    if (address >= 0x8000 && cartridge) {
        cartridge->writePRG(address, value);
    }
}
