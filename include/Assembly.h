#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "CPU6502.h"
#include <map>
#include <functional>
#include <iostream>
#include <stdint.h>

using namespace std;

class CPU6502;

class Assembly
{
public:
    Assembly(CPU6502 *cpu);

    static map<uint8_t, function<void(Assembly &)>> opcodeMap;
    void executeOpcode(uint8_t opcode);
    void invokeAllHandlers();

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
    void brkHandler();
    void oraHandler();
    void bplHandler();
    void jsrHandler();
    void andHandler();
    void rolHandler();
    void bmiHandler();
    void eorHandler();
    void rorHandler();
    void rtiHandler();
    void cliHandler();
    void bvcHandler();
    void rtsHandler();
    void bvsHandler();
    void styHandler();
    void stxHandler();
    void jmpHandler();

private:
    CPU6502 *cpu;
};

#endif // ASSEMBLY_H