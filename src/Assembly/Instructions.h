#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "CPU/CPU6502.h"

class Instructions
{
  public:
    void handleADC(CPU6502 &cpu);
    void handleLDA(CPU6502 &cpu);
    void handleBRK(CPU6502 &cpu);
    void handleORAAbsoluteY(CPU6502 &cpu);
    void handleNOP(CPU6502 &cpu);
    void handleNOPAbsoluteX(CPU6502 &cpu);
    void handleASLAbsoluteX(CPU6502 &cpu);
    void handleNOPIMM(CPU6502 &cpu);
    void handleEORZP(CPU6502 &cpu);
    void handleSREIndirectIndexed(CPU6502 &cpu);
    void handleORAIndirectIndexedX(CPU6502 &cpu);
    void handleKIL(CPU6502 &cpu);
    void handleLSRAbsolute(CPU6502 &cpu);
    void handleSEI(CPU6502 &cpu);
    void handleCLD(CPU6502 &cpu);
    void handleSTA(CPU6502 &cpu);
};

#endif
