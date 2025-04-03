#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "CPU/CPU6502.h"
#include <unordered_map>

class Instructions
{
  public:
    void handleADC(CPU6502 &cpu);
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
    void handleDEX(CPU6502 &cpu);
    void handleCLD(CPU6502 &cpu);
    void handleSTA(CPU6502 &cpu);
    void handleLDXImmediate(CPU6502 &cpu);
    void handleTXS(CPU6502 &cpu);
    void handleLDAAbsolute(CPU6502 &cpu);
    void handleLDA(CPU6502 &cpu);
    void handleBPL(CPU6502 &cpu);
    void handleISCAbsoluteX(CPU6502 &cpu);
    void handleImmLDY(CPU6502 &cpu);
    void handleAbsXLDA(CPU6502 &cpu);
    void handleImmCMP(CPU6502 &cpu);
    void handleRelBCS(CPU6502 &cpu);
    void handleBNE(CPU6502 &cpu);
    static std::unordered_map<uint8_t, std::string> opcodeMap;

  private:
    uint8_t fetchImmediate(CPU6502 &cpu);
    uint8_t fetchZeroPage(CPU6502 &cpu);
    uint8_t fetchZeroPageX(CPU6502 &cpu);
    uint8_t fetchZeroPageY(CPU6502 &cpu);
    uint16_t fetchAbsoluteAddress(CPU6502 &cpu);
    uint8_t fetchAbsolute(CPU6502 &cpu);
    uint8_t fetchAbsoluteX(CPU6502 &cpu);
    uint8_t fetchAbsoluteY(CPU6502 &cpu);
    uint16_t fetchIndirect(CPU6502 &cpu);
    uint8_t fetchIndexedIndirectX(CPU6502 &cpu);
    uint8_t fetchIndirectIndexedY(CPU6502 &cpu);
    int16_t fetchRelative(CPU6502 &cpu);
};

#endif
