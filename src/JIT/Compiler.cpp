
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
}

void JITCompiler::compileOpcode(uint8_t opcode, CPU6502 &cpu)
{
    if (opcodeTable[opcode])
    {
        (asm_instructions.*opcodeTable[opcode])(cpu);
    }
    else
    {
        std::cerr << "Opcode not implemented: " << std::hex << +opcode
                  << std::endl;
    }
}
