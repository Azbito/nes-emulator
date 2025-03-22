#ifndef MEMORY_MANIPULATOR_HPP
#define MEMORY_MANIPULATOR_HPP

#include "CPU/CPU6502.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <windows.h>

namespace memory
{
uint8_t read(uint16_t &address, CPU6502 &cpu)
{
    return cpu.RAM[address];
};

void write(uint16_t &address, uint8_t &value, CPU6502 &cpu)
{
    cpu.RAM[address] = value;
};

void *allocExecutableMemory(size_t &size)
{
    void *mem = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE,
                             PAGE_EXECUTE_READWRITE);

    if (mem == NULL)
    {
        exit(1);
    }

    return mem;
};
}; // namespace memory
#endif
