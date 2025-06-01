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
    Logger logger("read_address");

    if (address < 0x2000) {
        return ram[address & 0x07FF];
    } else if (address < 0x4000) {
        uint16_t reg = address & 0x2007;
        switch (reg) {
            case 0x2002:
                return ppu->readStatus();
            case 0x2004:
                return 0x0;
            case 0x2007:
                system("pause");
                return 0x0;
            default:
                logger.log("Leitura de registrador PPU não implementado: 0x" +
                           utils::toHexString(reg));
                return 0;
        }
    } else if (address < 0x4020) {
        logger.log("Leitura de IO register não implementada: 0x" +
                   utils::toHexString(address));
        return 0;
    } else if (address >= 0x8000 && cartridge) {
        return cartridge->readPRG(address);
    }

    logger.log("Leitura de endereço não mapeado: 0x" +
               utils::toHexString(address));
    return 0;
}

void Bus::write(uint16_t address, uint8_t value) {
    if (address < 0x2000) {
        ram[address & 0x07FF] = value;
        return;
    }

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
