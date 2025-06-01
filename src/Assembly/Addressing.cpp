#include "Assembly/Instructions.h"
#include "Bus/Bus.h"
#include "CPU/CPU6502.h"

uint8_t Instructions::fetchImmediate(CPU6502 &cpu, Bus &bus) {
    return bus.read(cpu.getPC() + 1);
}

uint16_t Instructions::fetchWord(CPU6502 &cpu, Bus &bus) {
    uint16_t pc = cpu.getPC();
    uint8_t lo = bus.read(pc);
    uint8_t hi = bus.read(pc + 1);

    cpu.setPC(pc + 2);

    uint16_t address = (hi << 8) | lo;

    return address;
}

uint8_t Instructions::fetchZeroPage(CPU6502 &cpu, Bus &bus) {
    return bus.read(cpu.getPC() + 1);
}

uint8_t Instructions::fetchZeroPageX(CPU6502 &cpu, Bus &bus) {
    return bus.read((bus.read(cpu.getPC() + 1) + cpu.getX()) & 0xFF);
}

uint8_t Instructions::fetchZeroPageY(CPU6502 &cpu, Bus &bus) {
    return bus.read((bus.read(cpu.getPC() + 1) + cpu.getY()) & 0xFF);
}

uint8_t Instructions::fetchAbsolute(CPU6502 &cpu, Bus &bus) {
    return bus.read(fetchAbsoluteAddress(cpu, bus));
}

uint8_t Instructions::fetchAbsoluteX(CPU6502 &cpu, Bus &bus) {
    return bus.read(fetchAbsoluteAddress(cpu, bus) + cpu.getX());
}

uint8_t Instructions::fetchAbsoluteY(CPU6502 &cpu, Bus &bus) {
    return bus.read(fetchAbsoluteAddress(cpu, bus) + cpu.getY());
}

uint16_t Instructions::fetchIndirect(CPU6502 &cpu, Bus &bus) {
    uint16_t addr = fetchAbsoluteAddress(cpu, bus);
    return bus.read(addr) | (bus.read(addr + 1) << 8);
}

int16_t Instructions::fetchRelative(CPU6502 &cpu, Bus &bus) {
    int8_t offset = static_cast<int8_t>(bus.read(cpu.getPC() + 1));
    return cpu.getPC() + 2 + offset;
}

uint8_t Instructions::fetchIndexedIndirectX(CPU6502 &cpu, Bus &bus) {
    uint16_t baseAddr = bus.read(cpu.getPC() + 1);
    uint16_t addr = (bus.read(baseAddr + cpu.getX()) |
                     (bus.read(baseAddr + cpu.getX() + 1) << 8));
    return bus.read(addr);
}

uint8_t Instructions::fetchIndirectIndexedY(CPU6502 &cpu, Bus &bus) {
    uint16_t zpAddr = bus.read(cpu.getPC() + 1);
    uint16_t low = bus.read(zpAddr);
    uint16_t high = bus.read((zpAddr + 1) & 0xFF);
    uint16_t addr = (high << 8) | low;
    addr += cpu.getY();

    return bus.read(addr);
}

uint16_t Instructions::fetchAbsoluteAddress(CPU6502 &cpu, Bus &bus) {
    return static_cast<uint16_t>(bus.read(cpu.getPC() + 1)) |
           (static_cast<uint16_t>(bus.read(cpu.getPC() + 2)) << 8);
}
