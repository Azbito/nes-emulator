#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstdint>
#include <string>
#include <unordered_map>

class CPU6502;
class Bus;

class Instructions {
public:
    std::string getOpcodeName(uint8_t opcode);

    void handleSEP(CPU6502 &cpu, Bus &bus);
    void handleSTAAbsolute(CPU6502 &cpu, Bus &bus);
    void handleDECAbsolute(CPU6502 &cpu, Bus &bus);
    void handleAbsoluteJMPIndirect(CPU6502 &cpu, Bus &bus);
    void handleADC(CPU6502 &cpu, Bus &bus);
    void handleZeroPageXSTA(CPU6502 &cpu, Bus &bus);
    void handleBRK(CPU6502 &cpu, Bus &bus);
    void handleORAAbsoluteY(CPU6502 &cpu, Bus &bus);
    void handleLDXAbsolute(CPU6502 &cpu, Bus &bus);
    void handleNOP(CPU6502 &cpu, Bus &bus);
    void handleNOPAbsoluteX(CPU6502 &cpu, Bus &bus);
    void handleRTI(CPU6502 &cpu, Bus &bus);
    void handleAbsoluteSTX(CPU6502 &cpu, Bus &bus);
    void handleINX(CPU6502 &cpu, Bus &bus);
    void handleLDXIndirectY(CPU6502 &cpu, Bus &bus);
    void handleLDYAbsoluteX(CPU6502 &cpu, Bus &bus);
    void handleAbsoluteSTY(CPU6502 &cpu, Bus &bus);
    void handleASLAbsoluteX(CPU6502 &cpu, Bus &bus);
    void handleSEC(CPU6502 &cpu, Bus &bus);
    void handleNOPIMM(CPU6502 &cpu, Bus &bus);
    void handleZeroPageLDA(CPU6502 &cpu, Bus &bus);
    void handleImmediateLDX(CPU6502 &cpu, Bus &bus);
    void handleEORZP(CPU6502 &cpu, Bus &bus);
    void handleSREIndirectIndexed(CPU6502 &cpu, Bus &bus);
    void handleORAIndirectIndexedX(CPU6502 &cpu, Bus &bus);
    void handleKIL(CPU6502 &cpu, Bus &bus);
    void handleLSRAbsolute(CPU6502 &cpu, Bus &bus);
    void handleSEI(CPU6502 &cpu, Bus &bus);
    void handleDEX(CPU6502 &cpu, Bus &bus);
    void handleCLD(CPU6502 &cpu, Bus &bus);
    void handleTXA(CPU6502 &cpu, Bus &bus);
    void handleAbsCMP(CPU6502 &cpu, Bus &bus);
    void handleSED(CPU6502 &cpu, Bus &bus);
    void handleASLAccumulator(CPU6502 &cpu, Bus &bus);
    void handleDECZeroPageX(CPU6502 &cpu, Bus &bus);
    void handleSBCZeroPage(CPU6502 &cpu, Bus &bus);
    void handleTSX(CPU6502 &cpu, Bus &bus);
    void handleORAZeroPage(CPU6502 &cpu, Bus &bus);
    void handleSTA(CPU6502 &cpu, Bus &bus);
    void handleZeroPageDEC(CPU6502 &cpu, Bus &bus);
    void handleLDXZeroPage(CPU6502 &cpu, Bus &bus);
    void handleTAX(CPU6502 &cpu, Bus &bus);
    void handleCLC(CPU6502 &cpu, Bus &bus);
    void handleLDAIndirectIndexedY(CPU6502 &cpu, Bus &bus);
    void handleADCZeroPage(CPU6502 &cpu, Bus &bus);
    void handleLSRA(CPU6502 &cpu, Bus &bus);
    void handleZeroPageAND(CPU6502 &cpu, Bus &bus);
    void handleTYA(CPU6502 &cpu, Bus &bus);
    void handleLDXImmediate(CPU6502 &cpu, Bus &bus);
    void handlePHA(CPU6502 &cpu, Bus &bus);
    void handleZeroPageSTY(CPU6502 &cpu, Bus &bus);
    void handleTXS(CPU6502 &cpu, Bus &bus);
    void handleAND(CPU6502 &cpu, Bus &bus);
    void handleRelativeBEQ(CPU6502 &cpu, Bus &bus);
    void handleLDAAbsolute(CPU6502 &cpu, Bus &bus);
    void handleLDA(CPU6502 &cpu, Bus &bus);
    void handleBPL(CPU6502 &cpu, Bus &bus);
    void handleISCAbsoluteX(CPU6502 &cpu, Bus &bus);
    void handleImmLDY(CPU6502 &cpu, Bus &bus);
    void handleAbsXLDA(CPU6502 &cpu, Bus &bus);
    void handleImmCMP(CPU6502 &cpu, Bus &bus);
    void handleRelBCS(CPU6502 &cpu, Bus &bus);
    void handleBNE(CPU6502 &cpu, Bus &bus);
    void handleJSR(CPU6502 &cpu, Bus &bus);
    void handleZeroPageSTA(CPU6502 &cpu, Bus &bus);
    void handleZeroPageSTX(CPU6502 &cpu, Bus &bus);
    void handleImmCPX(CPU6502 &cpu, Bus &bus);
    void handleRelBCC(CPU6502 &cpu, Bus &bus);
    void handleDEY(CPU6502 &cpu, Bus &bus);
    void handleImmCPY(CPU6502 &cpu, Bus &bus);
    void handleRTS(CPU6502 &cpu, Bus &bus);
    void handleIndirectYSTA(CPU6502 &cpu, Bus &bus);
    void handleZeroPageBIT(CPU6502 &cpu, Bus &bus);
    void handleAbsBIT(CPU6502 &cpu, Bus &bus);
    void handleAbsoluteYSTA(CPU6502 &cpu, Bus &bus);
    void handleINY(CPU6502 &cpu, Bus &bus);
    void handleORA(CPU6502 &cpu, Bus &bus);
    void handleAbsoluteJMP(CPU6502 &cpu, Bus &bus);
    void handleAbsoluteINC(CPU6502 &cpu, Bus &bus);
    void handlePLA(CPU6502 &cpu, Bus &bus);
    static std::unordered_map<uint8_t, std::string> opcodeMap;

private:
    uint8_t fetchImmediate(CPU6502 &cpu, Bus &bus);
    uint8_t fetchZeroPage(CPU6502 &cpu, Bus &bus);
    uint8_t fetchZeroPageX(CPU6502 &cpu, Bus &bus);
    uint8_t fetchZeroPageY(CPU6502 &cpu, Bus &bus);
    uint16_t fetchAbsoluteAddress(CPU6502 &cpu, Bus &bus);
    uint8_t fetchAbsolute(CPU6502 &cpu, Bus &bus);
    uint8_t fetchAbsoluteX(CPU6502 &cpu, Bus &bus);
    uint8_t fetchAbsoluteY(CPU6502 &cpu, Bus &bus);
    uint16_t fetchIndirect(CPU6502 &cpu, Bus &bus);
    uint8_t fetchIndexedIndirectX(CPU6502 &cpu, Bus &bus);
    uint8_t fetchIndirectIndexedY(CPU6502 &cpu, Bus &bus);
    int16_t fetchRelative(CPU6502 &cpu, Bus &bus);
    uint16_t fetchWord(CPU6502 &cpu, Bus &bus);
};

#endif
