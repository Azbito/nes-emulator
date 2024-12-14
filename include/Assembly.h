#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "CPU6502.h"
#include <map>
#include <functional>
#include <iostream>
#include <stdint.h>

class CPU6502;

class Assembly
{
public:
    Assembly(CPU6502 *cpu);
    void execute(uint8_t opcode);

private:
    CPU6502 *cpu;

    void ldaHandler();
    void ldxHandler();
    void ldyHandler();
    void staHandler();
    void clcHandler();
    void adcHandler();
    void sbcHandler();
    void aslHandler();
    void lsrHandler();
    void nopHandler();
    void bneHandler();
    void beqHandler();
    void bitHandler();
    void decHandler();
    void dexHandler();
    void deyHandler();
    void secHandler();
    void sedHandler();
    void seiHandler();
    void bccHandler();
    void bcsHandler();
    void taxHandler();
    void tayHandler();
    void txaHandler();
    void tyaHandler();
    void tsxHandler();
    void txsHandler();
    void plaHandler();
    void phaHandler();
    void plpHandler();
    void phpHandler();
};

#endif // ASSEMBLY_H