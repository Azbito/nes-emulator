/**=======================
 * *       INFO
 *  You may want to see how CPU6502 works
 *
 * https://web.archive.org/web/20200610200415/http://www.obelisk.me.uk/6502/index.html
 *========================**/
#ifndef CPU6502_H
#define CPU6502_H

#include <iostream>

using namespace std;

using BYTE = unsigned char;
using WORD = unsigned short;
using U32 = unsigned int;

class CPU6502
{
public:
    struct ProcessorState
    {
        WORD PC, SP;  // Program Counter e Stack Pointer
        BYTE A, X, Y; // Registers

        // Status Flags
        BYTE CARRY_FLAG : 1;
        BYTE ZERO_FLAG : 1;
        BYTE INTERRUPT_DISABLE : 1;
        BYTE DECIMAL_MODE : 1;
        BYTE BREAK_COMMAND : 1;
        BYTE OVERFLOW_FLAG : 1;
        BYTE NEGATIVE_FLAG : 1;

        BYTE STATUS;

        BYTE getStatusRegister() const
        {
            return (CARRY_FLAG << 0) |
                   (ZERO_FLAG << 1) |
                   (NEGATIVE_FLAG << 2) |
                   (OVERFLOW_FLAG << 3) |
                   (DECIMAL_MODE << 4) |
                   (INTERRUPT_DISABLE << 5) |
                   (BREAK_COMMAND << 6) |
                   (STATUS << 7) |
                   (PC << 8) |
                   (SP << 9) |
                   (A << 10) |
                   (X << 11) |
                   (Y << 12);
        }
    };

    struct Memory
    {
        static constexpr U32 MAX_MEM = 1024 * 64;
        BYTE data[MAX_MEM];

        void init();

        BYTE readOperator(U32 address);
        BYTE readMemory(WORD address);
        void writeOperator(U32 address, BYTE value);
        WORD fetchWord(U32 address);
    };

    struct Cycles
    {
        U32 cyclesLeft;

        Cycles() : cyclesLeft(0) {};

        void consume(U32 n)
        {
            cyclesLeft -= n;
        };

        bool hasCycles() const
        {
            return cyclesLeft > 0;
        };

        void reset()
        {
            cyclesLeft = 0;
        };
    };

    BYTE fetch(Cycles &cycles, Memory &memory); // fetchByte
    BYTE read(U32 &cycles, Memory &memory);     // readByte
    BYTE init(U32 cycles, Memory &memory);
    void execute(Cycles &cycles, Memory &memory);
    void reset(Memory &memory);
    void pushStack(BYTE value);
    void pushStatus(Memory &memory);
    void pushRegisters(Memory &memory);
    BYTE popStack();
    void PHA();

    ProcessorState processor;
    Memory memory;

    struct Instructions
    {
        static constexpr BYTE BRK = 0x00;
        static constexpr BYTE ORA_IZX = 0x01;
        static constexpr BYTE KIL_FIRST = 0x02;
        static constexpr BYTE SLO_IZX = 0x03;
        static constexpr BYTE NOP_ZP = 0x04;
        static constexpr BYTE ORA_ZP = 0x05;
        static constexpr BYTE ASL_ZP = 0x06;
        static constexpr BYTE SLO_ZP = 0x07;
        static constexpr BYTE PHP = 0x08;
        static constexpr BYTE ORA_IM = 0x09;
        static constexpr BYTE ASL = 0x0A;
        static constexpr BYTE ANC_IM = 0x0B;
        static constexpr BYTE NOP_ABS = 0x0C;
        static constexpr BYTE ORA_ABS = 0x0D;
        static constexpr BYTE ASL_ABS = 0x0E;
        static constexpr BYTE SLO_ABS = 0x0F;

        static constexpr BYTE BPL_REL = 0x10;
        static constexpr BYTE ORA_IZY = 0x11;
        static constexpr BYTE KIL_2 = 0x12;
        static constexpr BYTE SLO_IZY = 0x13;
        static constexpr BYTE NOP_ZPX_1 = 0x14;
        static constexpr BYTE ORA_ZPX = 0x15;
        static constexpr BYTE ASL_ZPX = 0x16;
        static constexpr BYTE SLO_ZPX = 0x17;
        static constexpr BYTE CLC = 0x18;
        static constexpr BYTE ORA_ABSY = 0x19;
        static constexpr BYTE NOP_2 = 0x1A;
        static constexpr BYTE SLO_ABSY = 0x1B;
        static constexpr BYTE NOP_ABX_1 = 0x1C;
        static constexpr BYTE ORA_ABSX = 0x1D;
        static constexpr BYTE ASL_ABSX = 0x1E;
        static constexpr BYTE SLO_ABSX = 0x1F;

        static constexpr BYTE JSR_ABS = 0x20;
        static constexpr BYTE AND_IZX = 0x21;
        static constexpr BYTE KIL_3 = 0x22;
        static constexpr BYTE RLA_IZX = 0x23;
        static constexpr BYTE BIT_ZP = 0x24;
        static constexpr BYTE AND_ZP = 0x25;
        static constexpr BYTE ROL_ZP = 0x26;
        static constexpr BYTE RLA_ZP = 0x27;
        static constexpr BYTE PLP = 0x28;
        static constexpr BYTE AND_IM = 0x29;
        static constexpr BYTE ROL = 0x2A;
        static constexpr BYTE ANC_IM_2 = 0x2B;
        static constexpr BYTE BIT_ABS = 0x2C;
        static constexpr BYTE AND_ABS = 0x2D;
        static constexpr BYTE ROL_ABS = 0x2E;
        static constexpr BYTE RLA_ABS = 0x2F;

        static constexpr BYTE BMI_REL = 0x30;
        static constexpr BYTE AND_IZY = 0x31;
        static constexpr BYTE KIL_4 = 0x32;
        static constexpr BYTE RLA_IZY = 0x33;
        static constexpr BYTE NOP_ZPX_2 = 0x34;
        static constexpr BYTE AND_ZPX = 0x35;
        static constexpr BYTE ROL_ZPX = 0x36;
        static constexpr BYTE RLA_ZPX = 0x37;
        static constexpr BYTE SEC = 0x38;
        static constexpr BYTE AND_ABSY = 0x39;
        static constexpr BYTE NOP_3 = 0x3A;
        static constexpr BYTE RLA_ABSY = 0x3B;
        static constexpr BYTE NOP_ABX_2 = 0x3C;
        static constexpr BYTE AND_ABSX = 0x3D;
        static constexpr BYTE ROL_ABSX = 0x3E;
        static constexpr BYTE RLA_ABSX = 0x3F;

        static constexpr BYTE RTI = 0x40;
        static constexpr BYTE EOR_IZX = 0x41;
        static constexpr BYTE KIL_5 = 0x42;
        static constexpr BYTE SRE_IZX = 0x43;
        static constexpr BYTE NOP_ZP_2 = 0x44;
        static constexpr BYTE EOR_ZP = 0x45;
        static constexpr BYTE LSR_ZP = 0x46;
        static constexpr BYTE SRE_ZP = 0x47;
        static constexpr BYTE PHA = 0x48;
        static constexpr BYTE EOR_IM = 0x49;
        static constexpr BYTE LSR = 0x4A;
        static constexpr BYTE ALR_IM = 0x4B;
        static constexpr BYTE JMP_ABS = 0x4C;
        static constexpr BYTE EOR_ABS = 0x4D;
        static constexpr BYTE LSR_ABS = 0x4E;
        static constexpr BYTE SRE_ABS = 0x4F;

        static constexpr BYTE BVC_REL = 0x50;
        static constexpr BYTE EOR_IZY = 0x51;
        static constexpr BYTE KIL_6 = 0x52;
        static constexpr BYTE SRE_IZY = 0x53;
        static constexpr BYTE NOP_ZPX_3 = 0x54;
        static constexpr BYTE EOR_ZPX = 0x55;
        static constexpr BYTE LSR_ZPX = 0x56;
        static constexpr BYTE SRE_ZPX = 0x57;
        static constexpr BYTE CLI = 0x58;
        static constexpr BYTE EOR_ABSY = 0x59;
        static constexpr BYTE NOP_4 = 0x5A;
        static constexpr BYTE SRE_ABSY = 0x5B;
        static constexpr BYTE NOP_ABX_3 = 0x5C;
        static constexpr BYTE EOR_ABSX = 0x5D;
        static constexpr BYTE LSR_ABSX = 0x5E;
        static constexpr BYTE SRE_ABSX = 0x5F;

        static constexpr BYTE RTS = 0x60;
        static constexpr BYTE ADC_IZX = 0x61;
        static constexpr BYTE KIL_7 = 0x62;
        static constexpr BYTE RRA_IZX = 0x63;
        static constexpr BYTE NOP_ZP_3 = 0x64;
        static constexpr BYTE ADC_ZP = 0x65;
        static constexpr BYTE ROR_ZP = 0x66;
        static constexpr BYTE RRA_ZP = 0x67;
        static constexpr BYTE PLA = 0x68;
        static constexpr BYTE ADC_IM = 0x69;
        static constexpr BYTE ROR_2 = 0x6A;
        static constexpr BYTE ARR_IM = 0x6B;
        static constexpr BYTE JMP_IND = 0x6C;
        static constexpr BYTE ADC_ABS = 0x6D;
        static constexpr BYTE ROR_ABS = 0x6E;
        static constexpr BYTE RRA_ABS = 0x6F;

        static constexpr BYTE BVS_REL = 0x70;
        static constexpr BYTE ADC_IZY = 0x71;
        static constexpr BYTE KIL_8 = 0x72;
        static constexpr BYTE RRA_IZY = 0x73;
        static constexpr BYTE NOP_ZPX_4 = 0x74;
        static constexpr BYTE ADC_ZPX = 0x75;
        static constexpr BYTE ROR_ZPX = 0x76;
        static constexpr BYTE RRA_ZPX = 0x77;
        static constexpr BYTE SEI = 0x78;
        static constexpr BYTE ADC_ABSY = 0x79;
        static constexpr BYTE NOP_5 = 0x7A;
        static constexpr BYTE RRA_ABSY = 0x7B;
        static constexpr BYTE NOP_ABX_4 = 0x7C;
        static constexpr BYTE ADC_ABSX = 0x7D;
        static constexpr BYTE ROR_ABSX = 0x7E;
        static constexpr BYTE RRA_ABSX = 0x7F;

        static constexpr BYTE NOP_IMM_2 = 0x80;
        static constexpr BYTE STA_IZX = 0x81;
        static constexpr BYTE NOP_IMM_2_ALT = 0x82;
        static constexpr BYTE SAX_IZX = 0x83;
        static constexpr BYTE STY_ZP = 0x84;
        static constexpr BYTE STA_ZP = 0x85;
        static constexpr BYTE STX_ZP = 0x86;
        static constexpr BYTE SAX_ZP = 0x87;
        static constexpr BYTE DEY = 0x88;
        static constexpr BYTE NOP_IMM_2_ALT2 = 0x89;
        static constexpr BYTE TXA = 0x8A;
        static constexpr BYTE XAA_IMM_2 = 0x8B;
        static constexpr BYTE STY_ABS = 0x8C;
        static constexpr BYTE STA_ABS = 0x8D;
        static constexpr BYTE STX_ABS = 0x8E;
        static constexpr BYTE SAX_ABS = 0x8F;

        static constexpr BYTE BCC_REL = 0x90;
        static constexpr BYTE STA_IZY = 0x91;
        static constexpr BYTE KIL = 0x92;
        static constexpr BYTE AHX_IZY = 0x93;
        static constexpr BYTE STY_ZPX = 0x94;
        static constexpr BYTE STA_ZPX = 0x95;
        static constexpr BYTE STX_ZPY = 0x96;
        static constexpr BYTE SAX_ZPY = 0x97;
        static constexpr BYTE TYA = 0x98;
        static constexpr BYTE STA_ABY = 0x99;
        static constexpr BYTE TXS = 0x9A;
        static constexpr BYTE TAS_ABY = 0x9B;
        static constexpr BYTE SHY_ABX = 0x9C;
        static constexpr BYTE STA_ABX = 0x9D;
        static constexpr BYTE SHX_ABY = 0x9E;
        static constexpr BYTE AHX_ABY = 0x9F;

        static constexpr BYTE LDY_IMM_2 = 0xA0;
        static constexpr BYTE LDA_IZX = 0xA1;
        static constexpr BYTE LDX_IMM_2 = 0xA2;
        static constexpr BYTE LAX_IZX = 0xA3;
        static constexpr BYTE LDY_ZP = 0xA4;
        static constexpr BYTE LDA_ZP = 0xA5;
        static constexpr BYTE LDX_ZP = 0xA6;
        static constexpr BYTE LAX_ZP = 0xA7;
        static constexpr BYTE TAY = 0xA8;
        static constexpr BYTE LDA_IMM_2 = 0xA9;
        static constexpr BYTE TAX = 0xAA;
        static constexpr BYTE LAX_IMM_2 = 0xAB;
        static constexpr BYTE LDY_ABS = 0xAC;
        static constexpr BYTE LDA_ABS = 0xAD;
        static constexpr BYTE LDX_ABS = 0xAE;
        static constexpr BYTE LAX_ABS = 0xAF;

        static constexpr BYTE BCS_REL = 0xB0;
        static constexpr BYTE LDA_IZY = 0xB1;
        static constexpr BYTE KIL_B = 0xB2;
        static constexpr BYTE LAX_IZY = 0xB3;
        static constexpr BYTE LDY_ZPX = 0xB4;
        static constexpr BYTE LDA_ZPX = 0xB5;
        static constexpr BYTE LDX_ZPY = 0xB6;
        static constexpr BYTE LAX_ZPY = 0xB7;
        static constexpr BYTE CLV = 0xB8;
        static constexpr BYTE LDA_ABY = 0xB9;
        static constexpr BYTE TSX = 0xBA;
        static constexpr BYTE LAS_ABY = 0xBB;
        static constexpr BYTE LDY_ABX = 0xBC;
        static constexpr BYTE LDA_ABX = 0xBD;
        static constexpr BYTE LDX_ABY = 0xBE;
        static constexpr BYTE LAX_ABY = 0xBF;

        static constexpr BYTE CPY_IMM_2 = 0xC0;
        static constexpr BYTE CMP_IZX = 0xC1;
        static constexpr BYTE NOP_IMM_2_C2 = 0xC2;
        static constexpr BYTE DCP_IZX = 0xC3;
        static constexpr BYTE CPY_ZP = 0xC4;
        static constexpr BYTE CMP_ZP = 0xC5;
        static constexpr BYTE DEC_ZP = 0xC6;
        static constexpr BYTE DCP_ZP = 0xC7;
        static constexpr BYTE INY = 0xC8;
        static constexpr BYTE CMP_IMM_2 = 0xC9;
        static constexpr BYTE DEX = 0xCA;
        static constexpr BYTE AXS_IMM_2 = 0xCB;
        static constexpr BYTE CPY_ABS = 0xCC;
        static constexpr BYTE CMP_ABS = 0xCD;
        static constexpr BYTE DEC_ABS = 0xCE;
        static constexpr BYTE DCP_ABS = 0xCF;

        static constexpr BYTE BNE_REL = 0xD0;
        static constexpr BYTE CMP_IZY = 0xD1;
        static constexpr BYTE KIL_D = 0xD2;
        static constexpr BYTE DCP_IZY = 0xD3;
        static constexpr BYTE NOP_ZPX = 0xD4;
        static constexpr BYTE CMP_ZPX = 0xD5;
        static constexpr BYTE DEC_ZPX = 0xD6;
        static constexpr BYTE DCP_ZPX = 0xD7;
        static constexpr BYTE CLD = 0xD8;
        static constexpr BYTE CMP_ABY = 0xD9;
        static constexpr BYTE NOP_DA = 0xDA;
        static constexpr BYTE DCP_ABY = 0xDB;
        static constexpr BYTE NOP_ABX = 0xDC;
        static constexpr BYTE CMP_ABX = 0xDD;
        static constexpr BYTE DEC_ABX = 0xDE;
        static constexpr BYTE DCP_ABX = 0xDF;

        static constexpr BYTE CPX_IMM_2 = 0xE0;
        static constexpr BYTE SBC_IZX = 0xE1;
        static constexpr BYTE NOP_IMM_2_E2 = 0xE2;
        static constexpr BYTE ISC_IZX = 0xE3;
        static constexpr BYTE CPX_ZP = 0xE4;
        static constexpr BYTE SBC_ZP = 0xE5;
        static constexpr BYTE INC_ZP = 0xE6;
        static constexpr BYTE ISC_ZP = 0xE7;
        static constexpr BYTE INX = 0xE8;
        static constexpr BYTE SBC_IMM_2 = 0xE9;
        static constexpr BYTE NOP_EA = 0xEA;
        static constexpr BYTE SBC_IMM_2_ALT = 0xEB;
        static constexpr BYTE CPX_ABS = 0xEC;
        static constexpr BYTE SBC_ABS = 0xED;
        static constexpr BYTE INC_ABS = 0xEE;
        static constexpr BYTE ISC_ABS = 0xEF;

        static constexpr BYTE BEQ_REL = 0xF0;
        static constexpr BYTE SBC_IZY = 0xF1;
        static constexpr BYTE KIL_F = 0xF2;
        static constexpr BYTE ISC_IZY = 0xF3;
        static constexpr BYTE NOP_ZPX_F4 = 0xF4;
        static constexpr BYTE SBC_ZPX = 0xF5;
        static constexpr BYTE INC_ZPX = 0xF6;
        static constexpr BYTE ISC_ZPX = 0xF7;
        static constexpr BYTE SED = 0xF8;
        static constexpr BYTE SBC_ABY = 0xF9;
        static constexpr BYTE NOP_FA = 0xFA;
        static constexpr BYTE SBC_ABY_ALT = 0xFB;
        static constexpr BYTE NOP_ABX_FC = 0xFC;
        static constexpr BYTE SBC_ABX = 0xFD;
        static constexpr BYTE INC_ABX = 0xFE;
        static constexpr BYTE ISC_ABX = 0xFF;
    };

    Instructions instructions;

    struct Handlers
    {
        void NOP_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_IMPLIED_HANDLER(Cycles &cycles, Memory &memory);
        void BRK_HANDLER(Cycles &cycles, Memory &memory);
        void ORA_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_FIRST_HANDLER(Cycles &cycles, Memory &memory);
        void SLO_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void ORA_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void ASL_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void SLO_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void PHP_HANDLER(Cycles &cycles, Memory &memory);
        void ORA_IM_HANDLER(Cycles &cycles, Memory &memory);
        void ASL_HANDLER(Cycles &cycles, Memory &memory);
        void ANC_IM_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void ORA_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void ASL_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void SLO_ABS_HANDLER(Cycles &cycles, Memory &memory);

        void BPL_REL_HANDLER(Cycles &cycles, Memory &memory);
        void ORA_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_2_HANDLER(Cycles &cycles, Memory &memory);
        void SLO_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZPX_1_HANDLER(Cycles &cycles, Memory &memory);
        void ORA_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void ASL_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void SLO_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void CLC_HANDLER(Cycles &cycles, Memory &memory);
        void ORA_ABSY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_2_HANDLER(Cycles &cycles, Memory &memory);
        void SLO_ABSY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ABX_1_HANDLER(Cycles &cycles, Memory &memory);
        void ORA_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void ASL_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void SLO_ABSX_HANDLER(Cycles &cycles, Memory &memory);

        void JSR_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void AND_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_3_HANDLER(Cycles &cycles, Memory &memory);
        void RLA_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void BIT_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void AND_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void ROL_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void RLA_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void PLP_HANDLER(Cycles &cycles, Memory &memory);
        void AND_IM_HANDLER(Cycles &cycles, Memory &memory);
        void ROL_HANDLER(Cycles &cycles, Memory &memory);
        void BIT_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void AND_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void ROL_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void RLA_ABS_HANDLER(Cycles &cycles, Memory &memory);

        void BMI_REL_HANDLER(Cycles &cycles, Memory &memory);
        void AND_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_4_HANDLER(Cycles &cycles, Memory &memory);
        void RLA_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZPX_2_HANDLER(Cycles &cycles, Memory &memory);
        void AND_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void ROL_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void RLA_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void SEC_HANDLER(Cycles &cycles, Memory &memory);
        void AND_ABSY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_3_HANDLER(Cycles &cycles, Memory &memory);
        void RLA_ABSY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ABX_2_HANDLER(Cycles &cycles, Memory &memory);
        void AND_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void ROL_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void RLA_ABSX_HANDLER(Cycles &cycles, Memory &memory);

        void RTI_HANDLER(Cycles &cycles, Memory &memory);
        void EOR_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_5_HANDLER(Cycles &cycles, Memory &memory);
        void SRE_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZP_2_HANDLER(Cycles &cycles, Memory &memory);
        void EOR_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void LSR_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void SRE_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void PHA_HANDLER(Cycles &cycles, Memory &memory);
        void EOR_IM_HANDLER(Cycles &cycles, Memory &memory);
        void LSR_HANDLER(Cycles &cycles, Memory &memory);
        void ALR_IM_HANDLER(Cycles &cycles, Memory &memory);
        void JMP_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void EOR_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void LSR_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void SRE_ABS_HANDLER(Cycles &cycles, Memory &memory);

        void BVC_REL_HANDLER(Cycles &cycles, Memory &memory);
        void EOR_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_6_HANDLER(Cycles &cycles, Memory &memory);
        void SRE_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZPX_3_HANDLER(Cycles &cycles, Memory &memory);
        void EOR_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void LSR_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void SRE_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void CLI_HANDLER(Cycles &cycles, Memory &memory);
        void EOR_ABSY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_4_HANDLER(Cycles &cycles, Memory &memory);
        void SRE_ABSY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ABX_3_HANDLER(Cycles &cycles, Memory &memory);
        void EOR_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void LSR_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void SRE_ABSX_HANDLER(Cycles &cycles, Memory &memory);

        void RTS_HANDLER(Cycles &cycles, Memory &memory);
        void ADC_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_7_HANDLER(Cycles &cycles, Memory &memory);
        void RRA_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZP_3_HANDLER(Cycles &cycles, Memory &memory);
        void ADC_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void ROR_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void RRA_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void PLA_HANDLER(Cycles &cycles, Memory &memory);
        void ADC_IM_HANDLER(Cycles &cycles, Memory &memory);
        void ROR_2_HANDLER(Cycles &cycles, Memory &memory);
        void ARR_IM_HANDLER(Cycles &cycles, Memory &memory);
        void JMP_IND_HANDLER(Cycles &cycles, Memory &memory);
        void ADC_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void ROR_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void RRA_ABS_HANDLER(Cycles &cycles, Memory &memory);

        void BVS_REL_HANDLER(Cycles &cycles, Memory &memory);
        void ADC_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_8_HANDLER(Cycles &cycles, Memory &memory);
        void RRA_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZPX_4_HANDLER(Cycles &cycles, Memory &memory);
        void ADC_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void ROR_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void RRA_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void SEI_HANDLER(Cycles &cycles, Memory &memory);
        void ADC_ABSY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_5_HANDLER(Cycles &cycles, Memory &memory);
        void RRA_ABSY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ABX_4_HANDLER(Cycles &cycles, Memory &memory);
        void ADC_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void ROR_ABSX_HANDLER(Cycles &cycles, Memory &memory);
        void RRA_ABSX_HANDLER(Cycles &cycles, Memory &memory);

        void NOP_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void STA_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_IMM_2_ALT_HANDLER(Cycles &cycles, Memory &memory);
        void SAX_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void STY_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void STA_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void STX_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void SAX_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void DEY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_IMM_2_ALT2_HANDLER(Cycles &cycles, Memory &memory);
        void TXA_HANDLER(Cycles &cycles, Memory &memory);
        void XAA_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void STY_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void STA_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void STX_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void SAX_ABS_HANDLER(Cycles &cycles, Memory &memory);

        void BCC_REL_HANDLER(Cycles &cycles, Memory &memory);
        void STA_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_HANDLER(Cycles &cycles, Memory &memory);
        void AHX_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void STY_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void STA_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void STX_ZPY_HANDLER(Cycles &cycles, Memory &memory);
        void SAX_ZPY_HANDLER(Cycles &cycles, Memory &memory);
        void TYA_HANDLER(Cycles &cycles, Memory &memory);
        void STA_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void TXS_HANDLER(Cycles &cycles, Memory &memory);
        void TAS_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void SHY_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void STA_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void SHX_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void AHX_ABY_HANDLER(Cycles &cycles, Memory &memory);

        void LDY_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void LDA_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void LDX_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void LAX_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void LDY_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void LDA_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void LDX_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void LAX_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void TAY_HANDLER(Cycles &cycles, Memory &memory);
        void LDA_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void TAX_HANDLER(Cycles &cycles, Memory &memory);
        void LAX_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void LDY_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void LDA_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void LDX_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void LAX_ABS_HANDLER(Cycles &cycles, Memory &memory);

        void BCS_REL_HANDLER(Cycles &cycles, Memory &memory);
        void LDA_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_B_HANDLER(Cycles &cycles, Memory &memory);
        void LAX_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void LDY_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void LDA_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void LDX_ZPY_HANDLER(Cycles &cycles, Memory &memory);
        void LAX_ZPY_HANDLER(Cycles &cycles, Memory &memory);
        void CLV_HANDLER(Cycles &cycles, Memory &memory);
        void LDA_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void TSX_HANDLER(Cycles &cycles, Memory &memory);
        void LAS_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void LDY_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void LDA_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void LDX_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void LAX_ABY_HANDLER(Cycles &cycles, Memory &memory);

        void CPY_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void CMP_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_IMM_2_C2_HANDLER(Cycles &cycles, Memory &memory);
        void DCP_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void CPY_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void CMP_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void DEC_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void DCP_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void INY_HANDLER(Cycles &cycles, Memory &memory);
        void CMP_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void DEX_HANDLER(Cycles &cycles, Memory &memory);
        void AXS_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void CPY_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void CMP_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void DEC_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void DCP_ABS_HANDLER(Cycles &cycles, Memory &memory);

        void BNE_REL_HANDLER(Cycles &cycles, Memory &memory);
        void CMP_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_D_HANDLER(Cycles &cycles, Memory &memory);
        void DCP_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void CMP_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void DEC_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void DCP_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void CLD_HANDLER(Cycles &cycles, Memory &memory);
        void CMP_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_DA_HANDLER(Cycles &cycles, Memory &memory);
        void DCP_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void CMP_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void DEC_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void DCP_ABX_HANDLER(Cycles &cycles, Memory &memory);

        void CPX_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_IMM_2_E2_HANDLER(Cycles &cycles, Memory &memory);
        void ISC_IZX_HANDLER(Cycles &cycles, Memory &memory);
        void CPX_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void INC_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void ISC_ZP_HANDLER(Cycles &cycles, Memory &memory);
        void INX_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_IMM_2_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_EA_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_IMM_2_ALT_HANDLER(Cycles &cycles, Memory &memory);
        void CPX_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void INC_ABS_HANDLER(Cycles &cycles, Memory &memory);
        void ISC_ABS_HANDLER(Cycles &cycles, Memory &memory);

        void BEQ_REL_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void KIL_F_HANDLER(Cycles &cycles, Memory &memory);
        void ISC_IZY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ZPX_F4_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void INC_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void ISC_ZPX_HANDLER(Cycles &cycles, Memory &memory);
        void SED_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_ABY_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_FA_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_ABY_ALT_HANDLER(Cycles &cycles, Memory &memory);
        void NOP_ABX_FC_HANDLER(Cycles &cycles, Memory &memory);
        void SBC_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void INC_ABX_HANDLER(Cycles &cycles, Memory &memory);
        void ISC_ABX_HANDLER(Cycles &cycles, Memory &memory);
    };
};

#endif // CPU6502_H
