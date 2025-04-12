#include "JIT/Compiler.h"
#include "Assembly/Instructions.h"

#include <bitset>
#include <iomanip>

JITCompiler::~JITCompiler()
{
    delete asm_instructions;
};

JITCompiler::JITCompiler(size_t bufferSize)
{
    asm_instructions = new Instructions();
    opcodeTable[0xBE] = &Instructions::handleLDXIndirectY;
    opcodeTable[0x2A] = &Instructions::handleImmediateLDX;
    opcodeTable[0xAE] = &Instructions::handleLDXAbsolute;
    opcodeTable[0x24] = &Instructions::handleZeroPageBIT;
    opcodeTable[0x09] = &Instructions::handleORA;
    opcodeTable[0x99] = &Instructions::handleAbsoluteYSTA;
    opcodeTable[0x4C] = &Instructions::handleAbsoluteJMP;
    opcodeTable[0xEE] = &Instructions::handleAbsoluteINC;
    opcodeTable[0xAC] = &Instructions::handleLDYAbsoluteX;
    opcodeTable[0x95] = &Instructions::handleZeroPageXSTA;
    opcodeTable[0x29] = &Instructions::handleAND;
    opcodeTable[0xA5] = &Instructions::handleZeroPageLDA;
    opcodeTable[0x48] = &Instructions::handlePHA;
    opcodeTable[0x98] = &Instructions::handleTYA;
    opcodeTable[0xC6] = &Instructions::handleZeroPageDEC;
    opcodeTable[0x68] = &Instructions::handlePLA;
    opcodeTable[0x05] = &Instructions::handleORAZeroPage;
    opcodeTable[0xB1] = &Instructions::handleLDAIndirectIndexedY;
    opcodeTable[0xA6] = &Instructions::handleLDXZeroPage;
    opcodeTable[0x65] = &Instructions::handleADCZeroPage;
    opcodeTable[0x18] = &Instructions::handleCLC;
    opcodeTable[0xAA] = &Instructions::handleTAX;
    opcodeTable[0x4A] = &Instructions::handleLSRA;
    opcodeTable[0x25] = &Instructions::handleZeroPageAND;
    opcodeTable[0x84] = &Instructions::handleZeroPageSTY;
    opcodeTable[0x8A] = &Instructions::handleTXA;
    opcodeTable[0xF0] = &Instructions::handleRelativeBEQ;
    opcodeTable[0xC8] = &Instructions::handleINY;
    opcodeTable[0x2C] = &Instructions::handleAbsBIT;
    opcodeTable[0x60] = &Instructions::handleRTS;
    opcodeTable[0xC0] = &Instructions::handleImmCPY;
    opcodeTable[0x90] = &Instructions::handleRelBCC;
    opcodeTable[0x91] = &Instructions::handleIndirectYSTA;
    opcodeTable[0x88] = &Instructions::handleDEY;
    opcodeTable[0xE0] = &Instructions::handleImmCPX;
    opcodeTable[0x86] = &Instructions::handleZeroPageSTX;
    opcodeTable[0x85] = &Instructions::handleZeroPageSTA;
    opcodeTable[0x20] = &Instructions::handleJSR;
    opcodeTable[0xB5] = &Instructions::handleZeroPageLDA;
    opcodeTable[0xD0] = &Instructions::handleBNE;
    opcodeTable[0xC9] = &Instructions::handleImmCMP;
    opcodeTable[0xB0] = &Instructions::handleRelBCS;
    opcodeTable[0xCA] = &Instructions::handleDEX;
    opcodeTable[0x69] = &Instructions::handleADC;
    opcodeTable[0xA9] = &Instructions::handleLDA;
    opcodeTable[0xBD] = &Instructions::handleAbsXLDA;
    opcodeTable[0xA0] = &Instructions::handleImmLDY;
    opcodeTable[0x00] = &Instructions::handleBRK;
    opcodeTable[0x19] = &Instructions::handleORAAbsoluteY;
    opcodeTable[0x1A] = &Instructions::handleNOP;
    opcodeTable[0x1C] = &Instructions::handleNOPAbsoluteX;
    opcodeTable[0x1E] = &Instructions::handleASLAbsoluteX;
    opcodeTable[0x82] = &Instructions::handleNOPIMM;
    opcodeTable[0x80] = &Instructions::handleBRK;
    opcodeTable[0x45] = &Instructions::handleEORZP;
    opcodeTable[0x53] = &Instructions::handleSREIndirectIndexed;
    opcodeTable[0x2] = &Instructions::handleKIL;
    opcodeTable[0x1] = &Instructions::handleORAIndirectIndexedX;
    opcodeTable[0x4E] = &Instructions::handleLSRAbsolute;
    opcodeTable[0x78] = &Instructions::handleSEI;
    opcodeTable[0xD6] = &Instructions::handleDECZeroPageX;
    opcodeTable[0xE5] = &Instructions::handleSBCZeroPage;
    opcodeTable[0x8E] = &Instructions::handleSTAAbsolute;
    opcodeTable[0xBA] = &Instructions::handleTSX;
    opcodeTable[0xD2] = &Instructions::handleSEP;
    opcodeTable[0xCE] = &Instructions::handleDECAbsolute;
    opcodeTable[0xCD] = &Instructions::handleAbsCMP;
    opcodeTable[0x0A] = &Instructions::handleASLAccumulator;
    opcodeTable[0xF8] = &Instructions::handleSED;
    opcodeTable[0xD8] = &Instructions::handleCLD;
    opcodeTable[0x8D] = &Instructions::handleSTA;
    opcodeTable[0xA2] = &Instructions::handleLDXImmediate;
    opcodeTable[0x9A] = &Instructions::handleTXS;
    opcodeTable[0xAD] = &Instructions::handleLDAAbsolute;
    opcodeTable[0x10] = &Instructions::handleBPL;
    opcodeTable[0xFF] = &Instructions::handleISCAbsoluteX;
}

void JITCompiler::compileOpcode(uint8_t opcode, CPU6502 &cpu)
{
    if (opcodeTable[opcode])
    {
      printf(" 0x%02X", opcode);

        (asm_instructions->*opcodeTable[opcode])(cpu, *bus);
    }
    else
    {
        printf("\033[1;31m[SYSTEM] Opcode not implemented: 0x%02X \033[0m\n",
               +opcode);
        exit(1);
    }
}
