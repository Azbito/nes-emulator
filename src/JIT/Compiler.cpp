
#include "JIT/Compiler.h"

JITCompiler::~JITCompiler() = default;

JITCompiler::JITCompiler(size_t bufferSize)
{
    opcodeTable[0x69] = &Instructions::handleADC;
    opcodeTable[0xA9] = &Instructions::handleLDA;
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
    printf("\n 0x%02X", opcode);

    if (opcodeTable[opcode])
    {
        (asm_instructions.*opcodeTable[opcode])(cpu);
    }
    else
    {
        printf("\033[1;31m[SYSTEM] Opcode not implemented: 0x%02X \033[0m\n",
               +opcode);
        exit(1);
    }
}
