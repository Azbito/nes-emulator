#include "JIT/Compiler.h"

#include <bitset>
#include <iomanip>
#include <set>

#include "Assembly/Instructions.h"
#include "CPU/CPU6502.h"
#include "Log/Log.hpp"
#include "Utils/main.hpp"

JITCompiler::~JITCompiler() {
    delete asm_instructions;

    asm_instructions = nullptr;
};

JITCompiler::JITCompiler(size_t bufferSize) {
    asm_instructions = new Instructions();

#pragma region Instructions
    opcodeTable[0x00] = &Instructions::handleBRK;
    opcodeTable[0x01] = &Instructions::handleORAIndirectIndexedX;
    opcodeTable[0x02] = &Instructions::handleKIL;
    opcodeTable[0x05] = &Instructions::handleORAZeroPage;
    opcodeTable[0x06] = &Instructions::handleASLZP;
    opcodeTable[0x08] = &Instructions::handlePHP;
    opcodeTable[0x09] = &Instructions::handleORA;
    opcodeTable[0x0A] = &Instructions::handleASLAccumulator;
    opcodeTable[0x0C] = &Instructions::handleNOPAbsoluteX;
    opcodeTable[0x0D] = &Instructions::handleORAAbsolute;
    opcodeTable[0x0E] = &Instructions::handleASLAbsolute;
    opcodeTable[0x10] = &Instructions::handleBPL;
    opcodeTable[0x11] = &Instructions::handleORAIndirectY;
    opcodeTable[0x15] = &Instructions::handleORAZeroPageX;
    opcodeTable[0x18] = &Instructions::handleCLC;
    opcodeTable[0x19] = &Instructions::handleORAAbsoluteY;
    opcodeTable[0x1A] = &Instructions::handleNOP;
    opcodeTable[0x1C] = &Instructions::handleNOPAbsoluteX;
    opcodeTable[0x1E] = &Instructions::handleASLAbsoluteX;
    opcodeTable[0x20] = &Instructions::handleJSR;
    opcodeTable[0x24] = &Instructions::handleZeroPageBIT;
    opcodeTable[0x25] = &Instructions::handleZeroPageAND;
    opcodeTable[0x29] = &Instructions::handleAND;
    opcodeTable[0x2C] = &Instructions::handleAbsBIT;
    opcodeTable[0x38] = &Instructions::handleSEC;
    opcodeTable[0x40] = &Instructions::handleRTI;
    opcodeTable[0x4A] = &Instructions::handleLSRA;
    opcodeTable[0x4C] = &Instructions::handleAbsoluteJMP;
    opcodeTable[0x4E] = &Instructions::handleLSRAbsolute;
    opcodeTable[0x45] = &Instructions::handleEORZP;
    opcodeTable[0x50] = &Instructions::handleRelBVC;
    opcodeTable[0x53] = &Instructions::handleSREIndirectIndexed;
    opcodeTable[0x60] = &Instructions::handleRTS;
    opcodeTable[0x65] = &Instructions::handleADCZeroPage;
    opcodeTable[0x68] = &Instructions::handlePLA;
    opcodeTable[0x69] = &Instructions::handleADC;
    opcodeTable[0x70] = &Instructions::handleRelBVS;
    opcodeTable[0x78] = &Instructions::handleSEI;
    opcodeTable[0x84] = &Instructions::handleZeroPageSTY;
    opcodeTable[0x85] = &Instructions::handleZeroPageSTA;
    opcodeTable[0x86] = &Instructions::handleZeroPageSTX;
    opcodeTable[0x88] = &Instructions::handleDEY;
    opcodeTable[0x8A] = &Instructions::handleTXA;
    opcodeTable[0x8C] = &Instructions::handleAbsoluteSTY;
    opcodeTable[0x8D] = &Instructions::handleSTAAbsolute;
    opcodeTable[0x8E] = &Instructions::handleAbsoluteSTX;
    opcodeTable[0x90] = &Instructions::handleRelBCC;
    opcodeTable[0x98] = &Instructions::handleTYA;
    opcodeTable[0x9A] = &Instructions::handleTXS;
    opcodeTable[0x99] = &Instructions::handleAbsoluteYSTA;
    opcodeTable[0xA0] = &Instructions::handleImmLDY;
    opcodeTable[0xA2] = &Instructions::handleLDXImmediate;
    opcodeTable[0xA5] = &Instructions::handleZeroPageLDA;
    opcodeTable[0xA6] = &Instructions::handleLDXZeroPage;
    opcodeTable[0xA9] = &Instructions::handleLDA;
    opcodeTable[0xAD] = &Instructions::handleLDAAbsolute;
    opcodeTable[0xAE] = &Instructions::handleLDXAbsolute;
    opcodeTable[0xB0] = &Instructions::handleRelBCS;
    opcodeTable[0xB1] = &Instructions::handleLDAIndirectIndexedY;
    opcodeTable[0xB5] = &Instructions::handleZeroPageLDA;
    opcodeTable[0xBD] = &Instructions::handleAbsXLDA;
    opcodeTable[0xC0] = &Instructions::handleImmCPY;
    opcodeTable[0xC6] = &Instructions::handleZeroPageDEC;
    opcodeTable[0xC8] = &Instructions::handleINY;
    opcodeTable[0xC9] = &Instructions::handleImmCMP;
    opcodeTable[0xCA] = &Instructions::handleDEX;
    opcodeTable[0xCD] = &Instructions::handleAbsCMP;
    opcodeTable[0xCE] = &Instructions::handleDECAbsolute;
    opcodeTable[0xD0] = &Instructions::handleBNE;
    opcodeTable[0xD2] = &Instructions::handleSEP;
    opcodeTable[0xD6] = &Instructions::handleDECZeroPageX;
    opcodeTable[0xE0] = &Instructions::handleImmCPX;
    opcodeTable[0xE5] = &Instructions::handleSBCZeroPage;
    opcodeTable[0xE8] = &Instructions::handleINX;
    opcodeTable[0xEA] = &Instructions::handleNOP;
    opcodeTable[0xF0] = &Instructions::handleRelativeBEQ;
    opcodeTable[0xF8] = &Instructions::handleSED;
    opcodeTable[0xFF] = &Instructions::handleISCAbsoluteX;
#pragma endregion
}

void JITCompiler::compileOpcode(uint8_t opcode, CPU6502 &cpu) {
    static std::set<uint8_t> recordedOpcodes;
    Logger log("jit");
    log.turnOffRegisterDate();

    std::string message =
        "\nOPCODE: 0x" +
        utils::toHexString(opcode, 2) +
        ", PC: $" + utils::toHexString(cpu.getPC(), 4) +
        " | A: 0x" + utils::toHexString(cpu.getA(), 2) +
        " | X: 0x" + utils::toHexString(cpu.getX(), 2) +
        " | Y: 0x" + utils::toHexString(cpu.getY(), 2) +
        " | SP: 0x" + utils::toHexString(cpu.getSP(), 2) +
        " | P: 0x" + utils::toHexString(cpu.getP(), 2);

    log.log(message);

    if (opcodeTable[opcode]) {
        (asm_instructions->*opcodeTable[opcode])(cpu, *bus);
        return;
    }

    printf("\033[1;31m[SYSTEM] Opcode not implemented: 0x%02X \033[0m\n",
           opcode);
    exit(1);
}
