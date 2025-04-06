#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <memory>

class CPU6502;
class Cartridge;

class Bus
{
  public:
    Bus();

    void connectCPU(CPU6502 *cpu);
    void connectCartridge(std::shared_ptr<Cartridge> cart);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

  private:
    CPU6502 *cpu;
    std::shared_ptr<Cartridge> cartridge;

    uint8_t ram[0x0800];
};

#endif
