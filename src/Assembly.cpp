#include "Assembly.h"

void Assembly::executeOpcode(uint8_t opcode)
{
    auto it = Assembly::opcodeMap.find(opcode);
    if (it != Assembly::opcodeMap.end())
    {
        it->second(*this);

        if (this->cpu->status.getZeroFlag())
        {
            cout << "Zero flag is set!" << endl;
        }
        else
        {
            cout << "Zero flag is clear!" << endl;
        }
    }
    else
    {
        cerr << "Unknown opcode: 0x" << setw(2) << setfill('0') << hex << static_cast<int>(opcode) << endl;
    }
}

map<uint8_t, function<void(Assembly &)>> Assembly::opcodeMap = {
    {0x00, [](Assembly &assembly)
     { assembly.brkHandler(); }},
    {0x01, [](Assembly &assembly)
     { assembly.oraIzxHandler(); }},
    {0x02, [](Assembly &assembly)
     { assembly.kilHandler(); }},
    {0x03, [](Assembly &assembly)
     { assembly.sloIzxHandler(); }},
    {0x04, [](Assembly &assembly)
     { assembly.nopZpHandler(); }},
    {0x05, [](Assembly &assembly)
     { assembly.oraZpHandler(); }},
    {0x06, [](Assembly &assembly)
     { assembly.aslZpHandler(); }},
    {0x07, [](Assembly &assembly)
     { assembly.sloZpHandler(); }},
    {0x08, [](Assembly &assembly)
     { assembly.phpHandler(); }},
    {0x09, [](Assembly &assembly)
     { assembly.oraImmHandler(); }},
    {0x0A, [](Assembly &assembly)
     { assembly.aslAHandler(); }},
    {0x0B, [](Assembly &assembly)
     { assembly.ancImmHandler(); }},
    {0x0C, [](Assembly &assembly)
     { assembly.nopAbsHandler(); }},
    {0x0D, [](Assembly &assembly)
     { assembly.oraAbsHandler(); }},
    {0x0E, [](Assembly &assembly)
     { assembly.aslAbsHandler(); }},
    {0x0F, [](Assembly &assembly)
     { assembly.sloAbsHandler(); }},
    {0x10, [](Assembly &assembly)
     { assembly.bplHandler(); }},
    {0x11, [](Assembly &assembly)
     { assembly.oraIzyHandler(); }},
    {0x12, [](Assembly &assembly)
     { assembly.kilHandler(); }},
    {0x13, [](Assembly &assembly)
     { assembly.sloIzyHandler(); }},
    {0x14, [](Assembly &assembly)
     { assembly.nopZpxHandler(); }},
    {0x15, [](Assembly &assembly)
     { assembly.oraZpxHandler(); }},
    {0x16, [](Assembly &assembly)
     { assembly.aslZpxHandler(); }},
    {0x17, [](Assembly &assembly)
     { assembly.sloZpxHandler(); }},
    {0x18, [](Assembly &assembly)
     { assembly.secHandler(); }},
    {0x19, [](Assembly &assembly)
     { assembly.oraAbyHandler(); }},
    {0x1A, [](Assembly &assembly)
     { assembly.nopHandler(); }},
    {0x1B, [](Assembly &assembly)
     { assembly.sloAbyHandler(); }},
    {0x1C, [](Assembly &assembly)
     { assembly.nopAbxHandler(); }},
    {0x1D, [](Assembly &assembly)
     { assembly.oraAbxHandler(); }},
    {0x1E, [](Assembly &assembly)
     { assembly.aslAbxHandler(); }},
    {0x1F, [](Assembly &assembly)
     { assembly.sloAbxHandler(); }},
    {0x20, [](Assembly &assembly)
     { assembly.jsrAbsHandler(); }},
    {0x21, [](Assembly &assembly)
     { assembly.andIzxHandler(); }},
    {0x22, [](Assembly &assembly)
     { assembly.kilHandler(); }},
    {0x23, [](Assembly &assembly)
     { assembly.rlaIzxHandler(); }},
    {0x24, [](Assembly &assembly)
     { assembly.bitZpHandler(); }},
    {0x25, [](Assembly &assembly)
     { assembly.andZpHandler(); }},
    {0x26, [](Assembly &assembly)
     { assembly.rolZpHandler(); }},
    {0x27, [](Assembly &assembly)
     { assembly.rlaZpHandler(); }},
    {0x28, [](Assembly &assembly)
     { assembly.plpHandler(); }},
    {0x29, [](Assembly &assembly)
     { assembly.andImmHandler(); }},
    {0x2A, [](Assembly &assembly)
     { assembly.rolAHandler(); }},
    {0x2B, [](Assembly &assembly)
     { assembly.ancImmHandler(); }},
    {0x2C, [](Assembly &assembly)
     { assembly.bitAbsHandler(); }},
    {0x2D, [](Assembly &assembly)
     { assembly.andAbsHandler(); }},
    {0x2E, [](Assembly &assembly)
     { assembly.rolAbsHandler(); }},
    {0x2F, [](Assembly &assembly)
     { assembly.rlaAbsHandler(); }},
    {0x30, [](Assembly &assembly)
     { assembly.bmiRelHandler(); }},
    {0x31, [](Assembly &assembly)
     { assembly.andIzyHandler(); }},
    {0x32, [](Assembly &assembly)
     { assembly.kilHandler(); }},
    {0x33, [](Assembly &assembly)
     { assembly.rlaIzyHandler(); }},
    {0x34, [](Assembly &assembly)
     { assembly.nopZpxHandler(); }},
    {0x35, [](Assembly &assembly)
     { assembly.andZpxHandler(); }},
    {0x36, [](Assembly &assembly)
     { assembly.rolZpxHandler(); }},
    {0x37, [](Assembly &assembly)
     { assembly.rlaZpxHandler(); }},
    {0x38, [](Assembly &assembly)
     { assembly.secHandler(); }},
    {0x39, [](Assembly &assembly)
     { assembly.andAbyHandler(); }},
    {0x3A, [](Assembly &assembly)
     { assembly.nopHandler(); }},
    {0x3B, [](Assembly &assembly)
     { assembly.rlaAbyHandler(); }},
    {0x3C, [](Assembly &assembly)
     { assembly.nopAbxHandler(); }},
    {0x3D, [](Assembly &assembly)
     { assembly.andAbxHandler(); }},
    {0x3E, [](Assembly &assembly)
     { assembly.rolAbxHandler(); }},
    {0x3F, [](Assembly &assembly)
     { assembly.rlaAbxHandler(); }},
    {0x40, [](Assembly &assembly)
     { assembly.rtiHandler(); }},
    {0x41, [](Assembly &assembly)
     { assembly.eorIzxHandler(); }},
    {0x42, [](Assembly &assembly)
     { assembly.kilHandler(); }},
    {0x43, [](Assembly &assembly)
     { assembly.sreIzxHandler(); }},
    {0x44, [](Assembly &assembly)
     { assembly.nopZpHandler(); }},
    {0x45, [](Assembly &assembly)
     { assembly.eorZpHandler(); }},
    {0x46, [](Assembly &assembly)
     { assembly.lsrZpHandler(); }},
    {0x47, [](Assembly &assembly)
     { assembly.sreZpHandler(); }},
    {0x48, [](Assembly &assembly)
     { assembly.phaHandler(); }},
    {0x49, [](Assembly &assembly)
     { assembly.eorImmHandler(); }},
    {0x4A, [](Assembly &assembly)
     { assembly.lsrHandler(); }},
    {0x4B, [](Assembly &assembly)
     { assembly.alrHandler(); }},
    {0x4C, [](Assembly &assembly)
     { assembly.jmpAbsHandler(); }},
    {0x4D, [](Assembly &assembly)
     { assembly.eorAbsHandler(); }},
    {0x4E, [](Assembly &assembly)
     { assembly.lsrAbsHandler(); }},
    {0x4F, [](Assembly &assembly)
     { assembly.sreAbsHandler(); }},
    {0x50, [](Assembly &assembly)
     { assembly.bvcRelHandler(); }},
    {0x51, [](Assembly &assembly)
     { assembly.eorIzyHandler(); }},
    {0x52, [](Assembly &assembly)
     { assembly.kilHandler(); }},
    {0x53, [](Assembly &assembly)
     { assembly.sreIzyHandler(); }},
    {0x54, [](Assembly &assembly)
     { assembly.nopZpxHandler(); }},
    {0x55, [](Assembly &assembly)
     { assembly.eorZpxHandler(); }},
    {0x56, [](Assembly &assembly)
     { assembly.lsrZpxHandler(); }},
    {0x57, [](Assembly &assembly)
     { assembly.sreZpxHandler(); }},
    {0x58, [](Assembly &assembly)
     { assembly.cliHandler(); }},
    {0x59, [](Assembly &assembly)
     { assembly.eorAbyHandler(); }},
    {0x5A, [](Assembly &assembly)
     { assembly.nopHandler(); }},
    {0x5B, [](Assembly &assembly)
     { assembly.sreAbyHandler(); }},
    {0x5C, [](Assembly &assembly)
     { assembly.nopAbxHandler(); }},
    {0x5D, [](Assembly &assembly)
     { assembly.eorAbxHandler(); }},
    {0x5E, [](Assembly &assembly)
     { assembly.lsrAbxHandler(); }},
    {0x5F, [](Assembly &assembly)
     { assembly.sreAbxHandler(); }},
    {0x60, [](Assembly &assembly)
     { assembly.rtsHandler(); }},
    {0x61, [](Assembly &assembly)
     { assembly.adcIzxHandler(); }},
    {0x62, [](Assembly &assembly)
     { assembly.kilHandler(); }},
    {0x63, [](Assembly &assembly)
     { assembly.rraIzxHandler(); }},
    {0x64, [](Assembly &assembly)
     { assembly.nopZpHandler(); }},
    {0x65, [](Assembly &assembly)
     { assembly.adcZpHandler(); }},
    {0x66, [](Assembly &assembly)
     { assembly.rorZpHandler(); }},
    {0x67, [](Assembly &assembly)
     { assembly.rraZpHandler(); }},
    {0x68, [](Assembly &assembly)
     { assembly.plaHandler(); }},
    {0x69, [](Assembly &assembly)
     { assembly.adcImmHandler(); }},
    {0x6A, [](Assembly &assembly)
     { assembly.rorHandler(); }},
    {0x6B, [](Assembly &assembly)
     { assembly.arrHandler(); }},
    {0x6C, [](Assembly &assembly)
     { assembly.jmpIndHandler(); }},
    {0x6D, [](Assembly &assembly)
     { assembly.adcAbsHandler(); }},
    {0x6E, [](Assembly &assembly)
     { assembly.rorAbsHandler(); }},
    {0x6F, [](Assembly &assembly)
     { assembly.rraAbsHandler(); }},
    {0x80, [](Assembly &assembly)
     { assembly.nopImmHandler(); }},
    {0x81, [](Assembly &assembly)
     { assembly.staIzxHandler(); }},
    {0x82, [](Assembly &assembly)
     { assembly.nopImmHandler(); }},
    {0x83, [](Assembly &assembly)
     { assembly.saxIzxHandler(); }},
    {0x84, [](Assembly &assembly)
     { assembly.styZpHandler(); }},
    {0x85, [](Assembly &assembly)
     { assembly.staZpHandler(); }},
    {0x86, [](Assembly &assembly)
     { assembly.stxZpHandler(); }},
    {0x87, [](Assembly &assembly)
     { assembly.saxZpHandler(); }},
    {0x88, [](Assembly &assembly)
     { assembly.deyHandler(); }},
    {0x89, [](Assembly &assembly)
     { assembly.nopImmHandler(); }},
    {0x8A, [](Assembly &assembly)
     { assembly.txaHandler(); }},
    {0x8B, [](Assembly &assembly)
     { assembly.xaaImmHandler(); }},
    {0x8C, [](Assembly &assembly)
     { assembly.styAbsHandler(); }},
    {0x8D, [](Assembly &assembly)
     { assembly.staAbsHandler(); }},
    {0x8E, [](Assembly &assembly)
     { assembly.stxAbsHandler(); }},
    {0x8F, [](Assembly &assembly)
     { assembly.saxAbsHandler(); }},
    {0x70, [](Assembly &assembly)
     { assembly.bvsHandler(); }},
    {0x71, [](Assembly &assembly)
     { assembly.adcIzxHandler(); }},
    {0x72, [](Assembly &assembly)
     { assembly.crashHandler(); }},
    {0x73, [](Assembly &assembly)
     { assembly.rraIzxHandler(); }},
    {0x74, [](Assembly &assembly)
     { assembly.nopZpxHandler(); }},
    {0x75, [](Assembly &assembly)
     { assembly.adcZpxHandler(); }},
    {0x76, [](Assembly &assembly)
     { assembly.rorZpxHandler(); }},
    {0x77, [](Assembly &assembly)
     { assembly.rraZpxHandler(); }},
    {0x78, [](Assembly &assembly)
     { assembly.seiHandler(); }},
    {0x79, [](Assembly &assembly)
     { assembly.adcAbyHandler(); }},
    {0x7A, [](Assembly &assembly)
     { assembly.nopHandler(); }},
    {0x7B, [](Assembly &assembly)
     { assembly.rraAbyHandler(); }},
    {0x7C, [](Assembly &assembly)
     { assembly.nopAbxHandler(); }},
    {0x7D, [](Assembly &assembly)
     { assembly.adcAbxHandler(); }},
    {0x7E, [](Assembly &assembly)
     { assembly.rorAbxHandler(); }},
    {0x7F, [](Assembly &assembly)
     { assembly.rraAbxHandler(); }},
    {0x90, [](Assembly &assembly)
     { assembly.bccHandler(); }},
    {0x91, [](Assembly &assembly)
     { assembly.staIzyHandler(); }},
    {0x92, [](Assembly &assembly)
     { assembly.crashHandler(); }},
    {0x93, [](Assembly &assembly)
     { assembly.ahxIzyHandler(); }},
    {0x94, [](Assembly &assembly)
     { assembly.styZpxHandler(); }},
    {0x95, [](Assembly &assembly)
     { assembly.staZpxHandler(); }},
    {0x96, [](Assembly &assembly)
     { assembly.stxZpyHandler(); }},
    {0x97, [](Assembly &assembly)
     { assembly.saxZpyHandler(); }},
    {0x98, [](Assembly &assembly)
     { assembly.tyaHandler(); }},
    {0x99, [](Assembly &assembly)
     { assembly.staAbyHandler(); }},
    {0x9A, [](Assembly &assembly)
     { assembly.txsHandler(); }},
    {0x9B, [](Assembly &assembly)
     { assembly.tasAbyHandler(); }},
    {0x9C, [](Assembly &assembly)
     { assembly.shyAbxHandler(); }},
    {0x9D, [](Assembly &assembly)
     { assembly.staAbxHandler(); }},
    {0x9E, [](Assembly &assembly)
     { assembly.shxAbyHandler(); }},
    {0x9F, [](Assembly &assembly)
     { assembly.ahxAbyHandler(); }},
    {0xA0, [](Assembly &assembly)
     { assembly.ldyImmHandler(); }},
    {0xA1, [](Assembly &assembly)
     { assembly.ldaIzxHandler(); }},
    {0xA2, [](Assembly &assembly)
     { assembly.ldxImmHandler(); }},
    {0xA3, [](Assembly &assembly)
     { assembly.laxIzxHandler(); }},
    {0xA4, [](Assembly &assembly)
     { assembly.ldyZpHandler(); }},
    {0xA5, [](Assembly &assembly)
     { assembly.ldaZpHandler(); }},
    {0xA6, [](Assembly &assembly)
     { assembly.ldxZpHandler(); }},
    {0xA8, [](Assembly &assembly)
     { assembly.tayHandler(); }},
    {0xA9, [](Assembly &assembly)
     { assembly.ldaImmHandler(); }},
    {0xAA, [](Assembly &assembly)
     { assembly.taxHandler(); }},
    {0xAB, [](Assembly &assembly)
     { assembly.laxImmHandler(); }},
    {0xAC, [](Assembly &assembly)
     { assembly.ldyAbsHandler(); }},
    {0xAD, [](Assembly &assembly)
     { assembly.ldaAbsHandler(); }},
    {0xAE, [](Assembly &assembly)
     { assembly.ldxAbsHandler(); }},
    {0xAF, [](Assembly &assembly)
     { assembly.laxAbsHandler(); }},
    {0xB0, [](Assembly &assembly)
     { assembly.bcsHandler(); }},
    {0xB1, [](Assembly &assembly)
     { assembly.ldaIzyHandler(); }},
    {0xB2, [](Assembly &assembly)
     { assembly.crashHandler(); }},
    {0xB3, [](Assembly &assembly)
     { assembly.laxIzyHandler(); }},
    {0xB4, [](Assembly &assembly)
     { assembly.ldyZpxHandler(); }},
    {0xB5, [](Assembly &assembly)
     { assembly.ldaZpxHandler(); }},
    {0xB6, [](Assembly &assembly)
     { assembly.ldxZpyHandler(); }},
    {0xB7, [](Assembly &assembly)
     { assembly.laxZpyHandler(); }},
    {0xB8, [](Assembly &assembly)
     { assembly.clvHandler(); }},
    {0xB9, [](Assembly &assembly)
     { assembly.ldaAbyHandler(); }},
    {0xBA, [](Assembly &assembly)
     { assembly.tsxHandler(); }},
    {0xBB, [](Assembly &assembly)
     { assembly.lasAbyHandler(); }},
    {0xBC, [](Assembly &assembly)
     { assembly.ldyAbxHandler(); }},
    {0xBD, [](Assembly &assembly)
     { assembly.ldaAbxHandler(); }},
    {0xBE, [](Assembly &assembly)
     { assembly.ldxAbyHandler(); }},
    {0xBF, [](Assembly &assembly)
     { assembly.laxAbyHandler(); }},
    {0xC0, [](Assembly &assembly)
     { assembly.cpyImmHandler(); }},
    {0xC1, [](Assembly &assembly)
     { assembly.cmpIzxHandler(); }},
    {0xC2, [](Assembly &assembly)
     { assembly.nopImmHandler(); }},
    {0xC3, [](Assembly &assembly)
     { assembly.dcpIzxHandler(); }},
    {0xC4, [](Assembly &assembly)
     { assembly.cpyZpHandler(); }},
    {0xC5, [](Assembly &assembly)
     { assembly.cmpZpHandler(); }},
    {0xC6, [](Assembly &assembly)
     { assembly.decZpHandler(); }},
    {0xC7, [](Assembly &assembly)
     { assembly.dcpZpHandler(); }},
    {0xC8, [](Assembly &assembly)
     { assembly.inyHandler(); }},
    {0xC9, [](Assembly &assembly)
     { assembly.cmpImmHandler(); }},
    {0xCA, [](Assembly &assembly)
     { assembly.dexHandler(); }},
    {0xCB, [](Assembly &assembly)
     { assembly.axsImmHandler(); }},
    {0xCC, [](Assembly &assembly)
     { assembly.cpyAbsHandler(); }},
    {0xCD, [](Assembly &assembly)
     { assembly.cmpAbsHandler(); }},
    {0xCE, [](Assembly &assembly)
     { assembly.decAbsHandler(); }},
    {0xCF, [](Assembly &assembly)
     { assembly.dcpAbsHandler(); }},
    {0xD0, [](Assembly &assembly)
     { assembly.bneHandler(); }},
    {0xD1, [](Assembly &assembly)
     { assembly.cmpIzyHandler(); }},
    {0xD2, [](Assembly &assembly)
     { assembly.crashHandler(); }},
    {0xD3, [](Assembly &assembly)
     { assembly.dcpIzyHandler(); }},
    {0xD4, [](Assembly &assembly)
     { assembly.nopZpxHandler(); }},
    {0xD5, [](Assembly &assembly)
     { assembly.cmpZpxHandler(); }},
    {0xD6, [](Assembly &assembly)
     { assembly.decZpxHandler(); }},
    {0xD7, [](Assembly &assembly)
     { assembly.dcpZpxHandler(); }},
    {0xD8, [](Assembly &assembly)
     { assembly.cldHandler(); }},
    {0xD9, [](Assembly &assembly)
     { assembly.cmpAbyHandler(); }},
    {0xDA, [](Assembly &assembly)
     { assembly.nopHandler(); }},
    {0xDB, [](Assembly &assembly)
     { assembly.dcpAbyHandler(); }},
    {0xDC, [](Assembly &assembly)
     { assembly.nopAbxHandler(); }},
    {0xDD, [](Assembly &assembly)
     { assembly.cmpAbxHandler(); }},
    {0xDE, [](Assembly &assembly)
     { assembly.decAbxHandler(); }},
    {0xDF, [](Assembly &assembly)
     { assembly.dcpAbxHandler(); }},
    {0xE0, [](Assembly &assembly)
     { assembly.cpxImmHandler(); }},
    {0xE1, [](Assembly &assembly)
     { assembly.sbcIzxHandler(); }},
    {0xE2, [](Assembly &assembly)
     { assembly.nopImmHandler(); }},
    {0xE3, [](Assembly &assembly)
     { assembly.iscIzxHandler(); }},
    {0xE4, [](Assembly &assembly)
     { assembly.cpxZpHandler(); }},
    {0xE5, [](Assembly &assembly)
     { assembly.sbcZpHandler(); }},
    {0xE6, [](Assembly &assembly)
     { assembly.incZpHandler(); }},
    {0xE7, [](Assembly &assembly)
     { assembly.iscZpHandler(); }},
    {0xE8, [](Assembly &assembly)
     { assembly.inxHandler(); }},
    {0xE9, [](Assembly &assembly)
     { assembly.sbcImmHandler(); }},
    {0xEA, [](Assembly &assembly)
     { assembly.nopHandler(); }},
    {0xEB, [](Assembly &assembly)
     { assembly.sbcImmHandler(); }},
    {0xEC, [](Assembly &assembly)
     { assembly.cpxAbsHandler(); }},
    {0xED, [](Assembly &assembly)
     { assembly.sbcAbsHandler(); }},
    {0xEE, [](Assembly &assembly)
     { assembly.incAbsHandler(); }},
    {0xEF, [](Assembly &assembly)
     { assembly.iscAbsHandler(); }},
    {0xF0, [](Assembly &assembly)
     { assembly.beqHandler(); }},
    {0xF1, [](Assembly &assembly)
     { assembly.sbcIzyHandler(); }},
    {0xF2, [](Assembly &assembly)
     { assembly.crashHandler(); }},
    {0xF3, [](Assembly &assembly)
     { assembly.iscIzyHandler(); }},
    {0xF4, [](Assembly &assembly)
     { assembly.nopZpxHandler(); }},
    {0xF5, [](Assembly &assembly)
     { assembly.sbcZpxHandler(); }},
    {0xF6, [](Assembly &assembly)
     { assembly.incZpxHandler(); }},
    {0xF7, [](Assembly &assembly)
     { assembly.iscZpxHandler(); }},
    {0xF8, [](Assembly &assembly)
     { assembly.sedHandler(); }},
    {0xF9, [](Assembly &assembly)
     { assembly.sbcAbyHandler(); }},
    {0xFA, [](Assembly &assembly)
     { assembly.nopHandler(); }},
    {0xFB, [](Assembly &assembly)
     { assembly.iscAbyHandler(); }},
    {0xFC, [](Assembly &assembly)
     { assembly.nopAbxHandler(); }},
    {0xFD, [](Assembly &assembly)
     { assembly.sbcAbxHandler(); }},
    {0xFE, [](Assembly &assembly)
     { assembly.incAbxHandler(); }},
    {0xFF, [](Assembly &assembly)
     { assembly.iscAbxHandler(); }}};

void Assembly::brkHandler()
{

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::oraIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = this->cpu->getMemory(operand + this->cpu->getXRegister());
    this->cpu->setAccumulator(this->cpu->getAccumulator() | address);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::nopZpHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::oraZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::aslZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint8_t result = value << 1;
    this->cpu->write(operand, result);

    this->cpu->getStatus().setCarryFlag(result & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::sloZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint8_t result = value << 1;
    this->cpu->write(operand, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::phpHandler()
{
    this->cpu->getStatus().setBreakFlag(true);
    this->cpu->pushStack(this->cpu->getStatus().getP());
    this->cpu->pushStack(this->cpu->getPC() >> 8);
    this->cpu->pushStack(this->cpu->getPC() & 0xFF);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::oraImmHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::aslAHandler()
{
    uint8_t result = this->cpu->getAccumulator() << 1;
    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setCarryFlag(result & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::ancImmHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & operand);

    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::nopAbsHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::oraAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::aslAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->getStatus().setCarryFlag(result & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::sloAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::bplHandler()
{
    uint8_t offset = this->cpu->getMemory(this->cpu->getPC() + 1);
    if (!this->cpu->getStatus().getNegativeFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + 2 + (int8_t)offset);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
    }
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::oraIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint16_t address = operand + this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::sloIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint16_t address = operand + this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::jsrAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);

    uint16_t returnAddress = this->cpu->getPC() + 2;

    this->cpu->pushStack(returnAddress >> 8);   // MSB (Most Significant Bit)
    this->cpu->pushStack(returnAddress & 0xFF); // LSB (Least Significant Bit)
    this->cpu->setPC(address);

    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::andIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = this->cpu->getMemory(operand + this->cpu->getXRegister());
    this->cpu->setAccumulator(this->cpu->getAccumulator() & address);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::rlaIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t result = (address << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(operand + this->cpu->getXRegister(), result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::bitZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint8_t result = this->cpu->getAccumulator() & value;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(value & 0x80);
    this->cpu->getStatus().setOverflowFlag(value & 0x40);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::andZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::rolZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(operand, result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::rlaZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(operand, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::plpHandler()
{
    uint8_t status = this->cpu->popStack();
    this->cpu->getStatus().fromByte(status);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::andImmHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::rolAHandler()
{
    uint8_t result = (this->cpu->getAccumulator() << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() & 0x80);
    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::bitAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = this->cpu->getAccumulator() & value;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(value & 0x80);
    this->cpu->getStatus().setOverflowFlag(value & 0x40);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::andAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::rolAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(address, result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::rlaAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(address, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::bmiRelHandler()
{
    int8_t offset = static_cast<int8_t>(this->cpu->getMemory(this->cpu->getPC() + 1));
    if (this->cpu->getStatus().getNegativeFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + offset);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
    }

    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::andIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getYRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getYRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::rlaIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getYRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getYRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(address, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::nopZpxHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::andZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());
    this->cpu->setAccumulator(this->cpu->getAccumulator() & value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::rolZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(operand + this->cpu->getXRegister(), result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::rlaZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(operand + this->cpu->getXRegister(), result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::secHandler()
{
    this->cpu->getStatus().setCarryFlag(true);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::andAbyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::nopHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::rlaAbyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(address, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::nopAbxHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::andAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::rolAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(address, result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::rlaAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();
    this->cpu->write(address, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::rtiHandler()
{
    uint8_t status = this->cpu->popStack();
    uint16_t returnAddress = this->cpu->popStack16();
    this->cpu->setPC(returnAddress);
    this->cpu->getStatus().fromByte(status);

    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::eorIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::sreIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value >> 1;
    this->cpu->write(address, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::eorZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::lsrZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint8_t result = value >> 1;
    this->cpu->write(operand, result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::sreZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint8_t result = value >> 1;
    this->cpu->write(operand, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::phaHandler()
{
    this->cpu->pushStack(this->cpu->getAccumulator());
    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::eorImmHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::lsrHandler()
{
    uint8_t value = this->cpu->getAccumulator();
    uint8_t result = value >> 1;
    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::alrHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & operand);
    this->cpu->setAccumulator(this->cpu->getAccumulator() >> 1);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::jmpAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    this->cpu->setPC(address);

    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::eorAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::lsrAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value >> 1;
    this->cpu->write(address, result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::sreAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value >> 1;
    this->cpu->write(address, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::bvcRelHandler()
{
    int8_t offset = static_cast<int8_t>(this->cpu->getMemory(this->cpu->getPC() + 1));
    if (!this->cpu->getStatus().getOverflowFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + offset);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
    }

    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::eorIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getYRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getYRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::sreIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getYRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getYRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value >> 1;
    this->cpu->write(address, result);
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::adcIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);
    uint16_t result = this->cpu->getAccumulator() + value + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(result & 0xFF);
    this->cpu->getStatus().setCarryFlag(result > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::rraIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);

    uint16_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() << 7);
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() + result + this->cpu->getStatus().getCarryFlag());
    this->cpu->getStatus().setCarryFlag(result > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::adcZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint16_t result = this->cpu->getAccumulator() + value + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(result & 0xFF);
    this->cpu->getStatus().setCarryFlag(result > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::rorZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);

    uint16_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() << 7);
    this->cpu->write(operand, result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::rraZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);

    uint16_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() << 7);
    this->cpu->write(operand, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() + result + this->cpu->getStatus().getCarryFlag());
    this->cpu->getStatus().setCarryFlag(result > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::eorZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::lsrZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());

    uint8_t result = value >> 1;
    this->cpu->write(operand + this->cpu->getXRegister(), result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::sreZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = operand + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);

    uint8_t result = value >> 1;
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ result);
    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::cliHandler()
{
    this->cpu->getStatus().clearInterruptDisableFlag();
    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::eorAbyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getYRegister());
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::eorAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getXRegister());
    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::lsrAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getXRegister());

    uint8_t result = value >> 1;
    this->cpu->write(address + this->cpu->getXRegister(), result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::sreAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getXRegister());

    uint8_t result = value >> 1;
    this->cpu->write(address + this->cpu->getXRegister(), result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ result);
    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::rtsHandler()
{
    uint16_t returnAddress = this->cpu->popStackWord();
    this->cpu->setPC(returnAddress + 1);

    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::bvsHandler()
{
    int8_t offset = static_cast<int8_t>(this->cpu->getMemory(this->cpu->getPC() + 1));
    if (this->cpu->getStatus().getOverflowFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + 2 + offset);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
    }
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::adcIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getYRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getYRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);

    uint16_t result = this->cpu->getAccumulator() + value + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(result & 0xFF);

    this->cpu->getStatus().setCarryFlag(result > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ value) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::rraIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getYRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getYRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);

    uint8_t carryIn = this->cpu->getStatus().getCarryFlag() ? 0x01 : 0x00;
    uint8_t result = (value >> 1) | (carryIn << 7);
    this->cpu->write(address, result);

    uint16_t sum = this->cpu->getAccumulator() + result + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(sum & 0xFF);

    this->cpu->getStatus().setCarryFlag(sum > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ result) & (this->cpu->getAccumulator() ^ sum) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::adcZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());

    uint16_t sum = this->cpu->getAccumulator() + value + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(sum & 0xFF);

    this->cpu->getStatus().setCarryFlag(sum > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ value) & (this->cpu->getAccumulator() ^ sum) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::rorZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());

    uint8_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() ? 0x80 : 0x00);
    this->cpu->write(operand + this->cpu->getXRegister(), result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::rraZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = operand + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);

    uint8_t carryIn = this->cpu->getStatus().getCarryFlag() ? 0x01 : 0x00;
    uint8_t result = (value >> 1) | (carryIn << 7);
    this->cpu->write(address, result);

    uint16_t sum = this->cpu->getAccumulator() + result + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(sum & 0xFF);

    this->cpu->getStatus().setCarryFlag(sum > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ result) & (this->cpu->getAccumulator() ^ sum) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::seiHandler()
{
    this->cpu->getStatus().setInterruptDisableFlag(true);
    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::adcAbyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getYRegister());

    uint16_t sum = this->cpu->getAccumulator() + value + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(sum & 0xFF);

    this->cpu->getStatus().setCarryFlag(sum > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ value) & (this->cpu->getAccumulator() ^ sum) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::adcAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getXRegister());

    uint16_t sum = this->cpu->getAccumulator() + value + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(sum & 0xFF);

    this->cpu->getStatus().setCarryFlag(sum > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ value) & (this->cpu->getAccumulator() ^ sum) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::rorAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getXRegister());

    uint8_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() ? 0x80 : 0x00);
    this->cpu->write(address + this->cpu->getXRegister(), result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::rraAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getXRegister());

    uint8_t carryIn = this->cpu->getStatus().getCarryFlag() ? 0x01 : 0x00;
    uint8_t result = (value >> 1) | (carryIn << 7);
    this->cpu->write(address + this->cpu->getXRegister(), result);

    uint16_t sum = this->cpu->getAccumulator() + result + this->cpu->getStatus().getCarryFlag();
    this->cpu->setAccumulator(sum & 0xFF);

    this->cpu->getStatus().setCarryFlag(sum > 0xFF);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ result) & (this->cpu->getAccumulator() ^ sum) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::staAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    this->cpu->write(address + this->cpu->getXRegister(), this->cpu->getAccumulator());

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::nopImmHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::staIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;

    this->cpu->write(address, this->cpu->getAccumulator());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::saxIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;

    this->cpu->write(address, this->cpu->getAccumulator() & this->cpu->getXRegister());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::styZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->write(operand, this->cpu->getYRegister());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::staZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->write(operand, this->cpu->getAccumulator());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::stxZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->write(operand, this->cpu->getXRegister());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::saxZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->write(operand, this->cpu->getAccumulator() & this->cpu->getXRegister());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::ldyImmHandler()
{
    uint8_t value = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setY(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getYRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getYRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::ldaIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;

    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::ldxImmHandler()
{
    uint8_t value = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getXRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getXRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::laxIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;

    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(value == 0);
    this->cpu->getStatus().setNegativeFlag(value & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::ldyZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->setY(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getYRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getYRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::ldaZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::ldxZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getXRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getXRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::laxZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->setAccumulator(value);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(value == 0);
    this->cpu->getStatus().setNegativeFlag(value & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::tayHandler()
{
    this->cpu->setY(this->cpu->getAccumulator());

    this->cpu->getStatus().setZeroFlag(this->cpu->getYRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getYRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::ldaImmHandler()
{
    uint8_t value = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::taxHandler()
{
    this->cpu->setX(this->cpu->getAccumulator());

    this->cpu->getStatus().setZeroFlag(this->cpu->getXRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getXRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::laxImmHandler()
{
    uint8_t value = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setAccumulator(value);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::ldyAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setY(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getYRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getYRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::ldaAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::ldxAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getXRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getXRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::laxAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::bcsRelHandler()
{
    int8_t offset = this->cpu->getMemory(this->cpu->getPC() + 1);
    if (this->cpu->getStatus().getCarryFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + offset + 2);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
    }
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::ldaIzyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getYRegister());
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::laxIzyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getYRegister());
    this->cpu->setAccumulator(value);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::ldyZpxHandler()
{
    uint16_t address = this->cpu->getMemory(this->cpu->getPC() + 1) + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setY(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getYRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getYRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::ldaZpxHandler()
{
    uint16_t address = this->cpu->getMemory(this->cpu->getPC() + 1) + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::ldxZpyHandler()
{
    uint16_t address = this->cpu->getMemory(this->cpu->getPC() + 1) + this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getXRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getXRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::laxZpyHandler()
{
    uint16_t address = this->cpu->getMemory(this->cpu->getPC() + 1) + this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::clvHandler()
{
    this->cpu->getStatus().setOverflowFlag(false);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::ldaAbyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::tsxHandler()
{
    this->cpu->setX(this->cpu->getSP());

    this->cpu->getStatus().setZeroFlag(this->cpu->getXRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getXRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::lasAbyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);

    this->cpu->setAccumulator(value);
    this->cpu->setX(value);
    this->cpu->setSP(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::ldxAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getXRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getXRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::ldaAbxHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::ldxAbyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getXRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getXRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::laxAbyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(value);
    this->cpu->setX(value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::cmpAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = this->cpu->getAccumulator() - value;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= value);
    this->cpu->getStatus().setOverflowFlag((this->cpu->getAccumulator() ^ value) & 0x80 && (this->cpu->getAccumulator() ^ result) & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::cmpZpHandler()
{
    uint16_t address = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = this->cpu->getAccumulator() - value;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= value);
    this->cpu->getStatus().setOverflowFlag((this->cpu->getAccumulator() ^ value) & 0x80 && (this->cpu->getAccumulator() ^ result) & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::cldHandler()
{
    this->cpu->getStatus().clearDecimalFlag();

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::cmpIzyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getYRegister());
    uint8_t result = this->cpu->getAccumulator() - value;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= value);
    this->cpu->getStatus().setOverflowFlag((this->cpu->getAccumulator() ^ value) & 0x80 && (this->cpu->getAccumulator() ^ result) & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::dcpIzyHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address + this->cpu->getYRegister());
    uint8_t result = value - 1;

    this->cpu->write(address + this->cpu->getYRegister(), result);

    uint8_t cmpResult = this->cpu->getAccumulator() - result;

    this->cpu->getStatus().setZeroFlag(cmpResult == 0);
    this->cpu->getStatus().setNegativeFlag(cmpResult & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= result);
    this->cpu->getStatus().setOverflowFlag((this->cpu->getAccumulator() ^ result) & 0x80 && (this->cpu->getAccumulator() ^ cmpResult) & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::kilHandler()
{

    this->cpu->triggerTrap();

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::sloIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t result = address << 1;
    this->cpu->write(operand + this->cpu->getXRegister(), result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::ancImHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getAccumulator() & operand;
    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setCarryFlag(result & 0x80);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setZeroFlag(result == 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::arrImHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t result = (this->cpu->getAccumulator() & operand) >> 1;
    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() & 0x01);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setZeroFlag(result == 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::ahxAbsHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t highByte = (this->cpu->getAccumulator() & this->cpu->getXRegister()) & 0xFF;
    this->cpu->write(operand, highByte);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::oraZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::aslZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t result = value << 1;
    this->cpu->write(operand + this->cpu->getXRegister(), result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::sloZpxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t result = value << 1;
    this->cpu->write(operand + this->cpu->getXRegister(), result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::oraAbyHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = (operand2 << 8) | operand1;
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::sloAbyHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = (operand2 << 8) | operand1;
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::oraAbxHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = ((operand2 << 8) | operand1) + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::aslAbxHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = ((operand2 << 8) | operand1) + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::sloAbxHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = ((operand2 << 8) | operand1) + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);

    this->cpu->getStatus().setCarryFlag(value & 0x80);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::sreAbyHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = (operand2 << 8) | operand1;
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = value ^ 0xFF;
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() ^ result);
    this->cpu->getStatus().setCarryFlag(result & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::plaHandler()
{
    uint8_t value = this->cpu->popStack();
    this->cpu->setAccumulator(value);

    this->cpu->getStatus().setZeroFlag(value == 0);
    this->cpu->getStatus().setNegativeFlag(value & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::adcImmHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getAccumulator() + operand + this->cpu->getStatus().getCarryFlag();

    this->cpu->setAccumulator(result);
    this->cpu->getStatus().setCarryFlag(result > 0xFF);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::rorHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    uint8_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() << 7);
    this->cpu->write(operand, result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::arrHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getAccumulator() & operand;
    this->cpu->setAccumulator(value);

    uint8_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() << 7);
    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setOverflowFlag((value ^ result) & 0x40);
    this->cpu->getStatus().setZeroFlag(result == 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::jmpIndHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = (operand2 << 8) | operand1;

    uint16_t indirectAddr = (this->cpu->getMemory(address + 1) << 8) | this->cpu->getMemory(address);
    this->cpu->setPC(indirectAddr);

    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::adcAbsHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = (operand2 << 8) | operand1;
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = this->cpu->getAccumulator() + value + this->cpu->getStatus().getCarryFlag();

    this->cpu->setAccumulator(result);
    this->cpu->getStatus().setCarryFlag(result > 0xFF);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ value) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::rorAbsHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = (operand2 << 8) | operand1;
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() << 7);
    this->cpu->write(address, result);

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::rraAbsHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = (operand2 << 8) | operand1;
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() << 7);
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() + result + this->cpu->getStatus().getCarryFlag());

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::crashHandler()
{

    std::cerr << "Unexpected opcode (crashHandler)!" << std::endl;
    std::exit(1);
}

void Assembly::rraAbyHandler()
{
    uint8_t operand1 = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t operand2 = this->cpu->getMemory(this->cpu->getPC() + 2);
    uint16_t address = (operand2 << 8) | operand1;
    address += this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    uint8_t result = (value >> 1) | (this->cpu->getStatus().getCarryFlag() << 7);
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() + result + this->cpu->getStatus().getCarryFlag());

    this->cpu->getStatus().setCarryFlag(value & 0x01);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::deyHandler()
{
    uint8_t result = this->cpu->getYRegister() - 1;
    this->cpu->setY(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::txaHandler()
{
    this->cpu->setAccumulator(this->cpu->getXRegister());

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::xaaImmHandler()
{

    uint8_t operand = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getAccumulator() & this->cpu->getXRegister();

    this->cpu->setAccumulator(result);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::styAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    this->cpu->write(address, this->cpu->getYRegister());

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::staAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    this->cpu->write(address, this->cpu->getAccumulator());

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::stxAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    this->cpu->write(address, this->cpu->getXRegister());

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::saxAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getAccumulator() & this->cpu->getXRegister();
    this->cpu->write(address, result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::bccHandler()
{

    int8_t offset = this->cpu->read(this->cpu->getPC() + 1);
    if (!this->cpu->getStatus().getCarryFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + offset);
        this->cpu->setCycles(this->cpu->getCycles() + 2);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
        this->cpu->setCycles(this->cpu->getCycles() + 3);
    }
}

void Assembly::staIzyHandler()
{

    uint8_t lowByte = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t highByte = this->cpu->read(this->cpu->getPC() + 2);
    uint16_t address = (highByte << 8) | lowByte;

    address += this->cpu->getYRegister();
    this->cpu->write(address, this->cpu->getAccumulator());

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::ahxIzyHandler()
{

    uint8_t lowByte = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t highByte = this->cpu->read(this->cpu->getPC() + 2);
    uint16_t address = (highByte << 8) | lowByte;

    address += this->cpu->getYRegister();
    uint8_t result = this->cpu->getAccumulator() & this->cpu->getXRegister();
    this->cpu->write(address, result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::styZpxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1) + this->cpu->getXRegister();
    this->cpu->write(address, this->cpu->getYRegister());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::staZpxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1) + this->cpu->getXRegister();
    this->cpu->write(address, this->cpu->getAccumulator());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::stxZpyHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1) + this->cpu->getYRegister();
    this->cpu->write(address, this->cpu->getXRegister());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::saxZpyHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1) + this->cpu->getYRegister();
    uint8_t result = this->cpu->getAccumulator() & this->cpu->getXRegister();
    this->cpu->write(address, result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::tyaHandler()
{

    this->cpu->setAccumulator(this->cpu->getYRegister());

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::staAbyHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    this->cpu->write(address, this->cpu->getAccumulator());

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::txsHandler()
{

    this->cpu->setSP(this->cpu->getXRegister());

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::tasAbyHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t result = this->cpu->getAccumulator() & this->cpu->getXRegister();
    this->cpu->write(address, result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::shyAbxHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t result = this->cpu->getYRegister() & 0xFF;
    this->cpu->write(address, result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::shxAbyHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t result = this->cpu->getXRegister() & this->cpu->getAccumulator();
    this->cpu->write(address, result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::ahxAbyHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t result = this->cpu->getAccumulator() & this->cpu->getXRegister();
    this->cpu->write(address, result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::bcsHandler()
{

    int8_t offset = this->cpu->read(this->cpu->getPC() + 1);
    if (this->cpu->getStatus().getCarryFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + offset);
        this->cpu->setCycles(this->cpu->getCycles() + 2);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
        this->cpu->setCycles(this->cpu->getCycles() + 3);
    }
}

void Assembly::ldyAbxHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    this->cpu->setY(this->cpu->read(address));

    this->cpu->getStatus().setZeroFlag(this->cpu->getYRegister() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getYRegister() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::cpyImmHandler()
{

    uint8_t operand = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getYRegister() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getYRegister() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::cmpIzxHandler()
{

    uint8_t addressLow = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t addressHigh = this->cpu->read(this->cpu->getPC() + 2);
    uint16_t address = (addressHigh << 8) | addressLow;

    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);

    uint8_t result = this->cpu->getAccumulator() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::dcpIzxHandler()
{

    uint8_t addressLow = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t addressHigh = this->cpu->read(this->cpu->getPC() + 2);
    uint16_t address = (addressHigh << 8) | addressLow;

    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);

    uint8_t result = operand - 1;
    this->cpu->write(address, result);

    uint8_t comparison = this->cpu->getAccumulator() - result;

    this->cpu->getStatus().setZeroFlag(comparison == 0);
    this->cpu->getStatus().setNegativeFlag(comparison & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::cpyZpHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);

    uint8_t result = this->cpu->getYRegister() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getYRegister() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::decZpHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);
    operand--;

    this->cpu->write(address, operand);
    this->cpu->getStatus().setZeroFlag(operand == 0);
    this->cpu->getStatus().setNegativeFlag(operand & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::dcpZpHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);

    uint8_t result = operand - 1;
    this->cpu->write(address, result);

    uint8_t comparison = this->cpu->getAccumulator() - result;

    this->cpu->getStatus().setZeroFlag(comparison == 0);
    this->cpu->getStatus().setNegativeFlag(comparison & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::inyHandler()
{

    uint8_t result = this->cpu->getYRegister() + 1;
    this->cpu->setY(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::cmpImmHandler()
{

    uint8_t operand = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getAccumulator() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::dexHandler()
{

    uint8_t result = this->cpu->getXRegister() - 1;
    this->cpu->setX(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::axsImmHandler()
{

    uint8_t operand = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t result = (this->cpu->getAccumulator() & this->cpu->getXRegister()) - operand;

    this->cpu->setAccumulator(result);
    this->cpu->setX(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::cpyAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);

    uint8_t result = this->cpu->getYRegister() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getYRegister() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::decAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);
    operand--;

    this->cpu->write(address, operand);
    this->cpu->getStatus().setZeroFlag(operand == 0);
    this->cpu->getStatus().setNegativeFlag(operand & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::dcpAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);

    uint8_t result = operand - 1;
    this->cpu->write(address, result);

    uint8_t comparison = this->cpu->getAccumulator() - result;

    this->cpu->getStatus().setZeroFlag(comparison == 0);
    this->cpu->getStatus().setNegativeFlag(comparison & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::bneHandler()
{

    int8_t offset = this->cpu->read(this->cpu->getPC() + 1);
    if (!this->cpu->getStatus().getZeroFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + offset);
        this->cpu->setCycles(this->cpu->getCycles() + 2);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
        this->cpu->setCycles(this->cpu->getCycles() + 3);
    }
}

void Assembly::cmpZpxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);

    uint8_t result = this->cpu->getAccumulator() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::decZpxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);
    operand--;

    this->cpu->write(address, operand);
    this->cpu->getStatus().setZeroFlag(operand == 0);
    this->cpu->getStatus().setNegativeFlag(operand & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::dcpZpxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);

    uint8_t result = operand - 1;
    this->cpu->write(address, result);

    uint8_t comparison = this->cpu->getAccumulator() - result;

    this->cpu->getStatus().setZeroFlag(comparison == 0);
    this->cpu->getStatus().setNegativeFlag(comparison & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::cmpAbyHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t operand = this->cpu->read(address);

    uint8_t result = this->cpu->getAccumulator() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::dcpAbyHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t operand = this->cpu->read(address);

    uint8_t result = operand - 1;
    this->cpu->write(address, result);

    uint8_t comparison = this->cpu->getAccumulator() - result;

    this->cpu->getStatus().setZeroFlag(comparison == 0);
    this->cpu->getStatus().setNegativeFlag(comparison & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::cmpAbxHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);

    uint8_t result = this->cpu->getAccumulator() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::decAbxHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);
    operand--;

    this->cpu->write(address, operand);
    this->cpu->getStatus().setZeroFlag(operand == 0);
    this->cpu->getStatus().setNegativeFlag(operand & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::dcpAbxHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);

    uint8_t result = operand - 1;
    this->cpu->write(address, result);

    uint8_t comparison = this->cpu->getAccumulator() - result;

    this->cpu->getStatus().setZeroFlag(comparison == 0);
    this->cpu->getStatus().setNegativeFlag(comparison & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= result);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::cpxImmHandler()
{

    uint8_t operand = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getXRegister() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getXRegister() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::sbcIzxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint16_t operandAddress = this->cpu->readMemory16(address + this->cpu->getXRegister());
    uint8_t operand = this->cpu->read(operandAddress);
    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::iscIzxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint16_t operandAddress = this->cpu->readMemory16(address + this->cpu->getXRegister());
    uint8_t operand = this->cpu->read(operandAddress);

    operand++;
    this->cpu->write(operandAddress, operand);

    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::cpxZpHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);
    uint8_t result = this->cpu->getXRegister() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getXRegister() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::sbcZpHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);
    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::incZpHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);
    operand++;

    this->cpu->write(address, operand);
    this->cpu->getStatus().setZeroFlag(operand == 0);
    this->cpu->getStatus().setNegativeFlag(operand & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::iscZpHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);

    operand++;
    this->cpu->write(address, operand);

    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::inxHandler()
{

    uint8_t result = this->cpu->getXRegister() + 1;
    this->cpu->setX(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::sbcImmHandler()
{

    uint8_t operand = this->cpu->read(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::cpxAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);
    uint8_t result = this->cpu->getXRegister() - operand;

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getXRegister() >= operand);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::sbcAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);
    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::incAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);
    operand++;

    this->cpu->write(address, operand);
    this->cpu->getStatus().setZeroFlag(operand == 0);
    this->cpu->getStatus().setNegativeFlag(operand & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::iscAbsHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t operand = this->cpu->read(address);

    operand++;
    this->cpu->write(address, operand);

    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::beqHandler()
{

    int8_t offset = this->cpu->read(this->cpu->getPC() + 1);
    if (this->cpu->getStatus().getZeroFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + offset);
        this->cpu->setCycles(this->cpu->getCycles() + 3);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
        this->cpu->setCycles(this->cpu->getCycles() + 2);
    }
}

void Assembly::sbcIzyHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint16_t operandAddress = this->cpu->readMemory16(address + this->cpu->getYRegister());
    uint8_t operand = this->cpu->read(operandAddress);
    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::iscIzyHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    uint16_t operandAddress = this->cpu->readMemory16(address + this->cpu->getYRegister());
    uint8_t operand = this->cpu->read(operandAddress);

    operand++;
    this->cpu->write(operandAddress, operand);

    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}

void Assembly::sbcZpxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);
    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::incZpxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);
    operand++;

    this->cpu->write(address, operand);
    this->cpu->getStatus().setZeroFlag(operand == 0);
    this->cpu->getStatus().setNegativeFlag(operand & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::iscZpxHandler()
{

    uint8_t address = this->cpu->read(this->cpu->getPC() + 1);
    address += this->cpu->getXRegister();
    uint8_t operand = this->cpu->read(address);

    operand++;
    this->cpu->write(address, operand);

    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::sedHandler()
{

    this->cpu->getStatus().setDecimalFlag(true);
    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::sbcAbyHandler()
{

    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    address += this->cpu->getYRegister();
    uint8_t operand = this->cpu->read(address);
    uint8_t result = this->cpu->getAccumulator() - operand - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setCarryFlag(this->cpu->getAccumulator() >= operand);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ operand) & (this->cpu->getAccumulator() ^ result) & 0x80) != 0);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::iscAbyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = operand + this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);

    uint8_t result = value - this->cpu->getAccumulator();
    this->cpu->write(address, result);

    this->cpu->getStatus().setCarryFlag(result < value);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::sbcAbxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = operand + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);

    uint8_t result = this->cpu->getAccumulator() - value - (this->cpu->getStatus().getCarryFlag() ? 0 : 1);
    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setCarryFlag(result <= this->cpu->getAccumulator());
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);
    this->cpu->getStatus().setOverflowFlag(((this->cpu->getAccumulator() ^ value) & (this->cpu->getAccumulator() ^ result)) & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::incAbxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = operand + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);

    value++;
    this->cpu->write(address, value);

    this->cpu->getStatus().setZeroFlag(value == 0);
    this->cpu->getStatus().setNegativeFlag(value & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::iscAbxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t address = operand + this->cpu->getXRegister();
    uint8_t value = this->cpu->getMemory(address);

    uint8_t result = value - this->cpu->getAccumulator();
    this->cpu->write(address, result);

    this->cpu->getStatus().setCarryFlag(result < value);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}
