#include "Assembly.h"

void Assembly::executeOpcode(uint8_t opcode)
{
    handleOpcode(opcode);
}

void Assembly::handleOpcode(uint8_t opcode)
{
    switch (opcode)
    {
    case 0x00:
        brkHandler();
        break;
    case 0x01:
        oraIzxHandler();
        break;
    case 0x02:
        kilHandler();
        break;
    case 0x03:
        sloIzxHandler();
        break;
    case 0x04:
        nopZpHandler();
        break;
    case 0x05:
        oraZpHandler();
        break;
    case 0x06:
        aslZpHandler();
        break;
    case 0x07:
        sloZpHandler();
        break;
    case 0x08:
        phpHandler();
        break;
    case 0x09:
        oraImmHandler();
        break;
    case 0x0A:
        aslAHandler();
        break;
    case 0x0B:
        ancImmHandler();
        break;
    case 0x0C:
        nopAbsHandler();
        break;
    case 0x0D:
        oraAbsHandler();
        break;
    case 0x0E:
        aslAbsHandler();
        break;
    case 0x0F:
        sloAbsHandler();
        break;
    case 0x10:
        bplHandler();
        break;
    case 0x11:
        oraIzyHandler();
        break;
    case 0x12:
        kilHandler();
        break;
    case 0x13:
        sloIzyHandler();
        break;
    case 0x14:
        nopZpxHandler();
        break;
    case 0x15:
        oraZpxHandler();
        break;
    case 0x16:
        aslZpxHandler();
        break;
    case 0x17:
        sloZpxHandler();
        break;
    case 0x18:
        secHandler();
        break;
    case 0x19:
        oraAbyHandler();
        break;
    case 0x1A:
        nopHandler();
        break;
    case 0x1B:
        sloAbyHandler();
        break;
    case 0x1C:
        nopAbxHandler();
        break;
    case 0x1D:
        oraAbxHandler();
        break;
    case 0x1E:
        aslAbxHandler();
        break;
    case 0x1F:
        sloAbxHandler();
        break;
    case 0x20:
        jsrAbsHandler();
        break;
    case 0x21:
        andIzxHandler();
        break;
    case 0x22:
        kilHandler();
        break;
    case 0x23:
        rlaIzxHandler();
        break;
    case 0x24:
        bitZpHandler();
        break;
    case 0x25:
        andZpHandler();
        break;
    case 0x26:
        rolZpHandler();
        break;
    case 0x27:
        rlaZpHandler();
        break;
    case 0x28:
        plpHandler();
        break;
    case 0x29:
        andImmHandler();
        break;
    case 0x2A:
        rolAHandler();
        break;
    case 0x2B:
        rlaImmHandler();
        break;
    case 0x2C:
        bitAbsHandler();
        break;
    case 0x2D:
        andAbsHandler();
        break;
    case 0x2E:
        rolAbsHandler();
        break;
    case 0x2F:
        rlaAbsHandler();
        break;
    case 0x30:
        bmiHandler();
        break;
    case 0x31:
        andIzyHandler();
        break;
    case 0x32:
        kilHandler();
        break;
    case 0x33:
        rlaIzyHandler();
        break;
    case 0x34:
        nopZpxHandler();
        break;
    case 0x35:
        andZpxHandler();
        break;
    case 0x36:
        rolZpxHandler();
        break;
    case 0x37:
        rlaZpxHandler();
        break;
    case 0x38:
        secHandler();
        break;
    case 0x39:
        andAbyHandler();
        break;
    case 0x3A:
        nopHandler();
        break;
    case 0x3B:
        rlaAbyHandler();
        break;
    case 0x3C:
        nopAbxHandler();
        break;
    case 0x3D:
        andAbxHandler();
        break;
    case 0x3E:
        rolAbxHandler();
        break;
    case 0x3F:
        rlaAbxHandler();
        break;
    case 0x40:
        rtiHandler();
        break;
    case 0x41:
        eorIzxHandler();
        break;
    case 0x42:
        kilHandler();
        break;
    case 0x43:
        sreIzxHandler();
        break;
    case 0x44:
        nopZpHandler();
        break;
    case 0x45:
        eorZpHandler();
        break;
    case 0x46:
        lsrZpHandler();
        break;
    case 0x47:
        sreZpHandler();
        break;
    case 0x48:
        phaHandler();
        break;
    case 0x49:
        eorImmHandler();
        break;
    case 0x4A:
        lsrAHandler();
        break;
    case 0x4B:
        sreImmHandler();
        break;
    case 0x4C:
        jmpAbsHandler();
        break;
    case 0x4D:
        eorAbsHandler();
        break;
    case 0x4E:
        lsrAbsHandler();
        break;
    case 0x4F:
        sreAbsHandler();
        break;
    case 0x50:
        bvcHandler();
        break;
    case 0x51:
        eorIzyHandler();
        break;
    case 0x52:
        kilHandler();
        break;
    case 0x53:
        sreIzyHandler();
        break;
    case 0x54:
        nopZpxHandler();
        break;
    case 0x55:
        eorZpxHandler();
        break;
    case 0x56:
        lsrZpxHandler();
        break;
    case 0x57:
        sreZpxHandler();
        break;
    case 0x58:
        cliHandler();
        break;
    case 0x59:
        eorAbyHandler();
        break;
    case 0x5A:
        nopHandler();
        break;
    case 0x5B:
        sreAbyHandler();
        break;
    case 0x5C:
        nopAbxHandler();
        break;
    case 0x5D:
        eorAbxHandler();
        break;
    case 0x5E:
        lsrAbxHandler();
        break;
    case 0x5F:
        sreAbxHandler();
        break;
    case 0x60:
        rtsHandler();
        break;
    case 0x61:
        adcIzxHandler();
        break;
    case 0x62:
        kilHandler();
        break;
    case 0x63:
        rraIzxHandler();
        break;
    case 0x64:
        nopZpHandler();
        break;
    case 0x65:
        adcZpHandler();
        break;
    case 0x66:
        rorZpHandler();
        break;
    case 0x67:
        rraZpHandler();
        break;
    case 0x68:
        plaHandler();
        break;
    case 0x69:
        adcImmHandler();
        break;
    case 0x6A:
        rorAHandler();
        break;
    case 0x6B:
        rraImmHandler();
        break;
    case 0x6C:
        jmpIndHandler();
        break;
    case 0x6D:
        adcAbsHandler();
        break;
    case 0x6E:
        rorAbsHandler();
        break;
    case 0x6F:
        rraAbsHandler();
        break;
    case 0x70:
        bvsHandler();
        break;
    case 0x71:
        adcIzyHandler();
        break;
    case 0x72:
        kilHandler();
        break;
    case 0x73:
        rraIzyHandler();
        break;
    case 0x74:
        nopZpxHandler();
        break;
    case 0x75:
        adcZpxHandler();
        break;
    case 0x76:
        rorZpxHandler();
        break;
    case 0x77:
        rraZpxHandler();
        break;
    case 0x78:
        seiHandler();
        break;
    case 0x79:
        adcAbyHandler();
        break;
    case 0x7A:
        nopHandler();
        break;
    case 0x7B:
        rraAbyHandler();
        break;
    case 0x7C:
        nopAbxHandler();
        break;
    case 0x7D:
        adcAbxHandler();
        break;
    case 0x7E:
        rorAbxHandler();
        break;
    case 0x7F:
        rraAbxHandler();
        break;
    case 0x80:
        nopImmHandler();
        break;
    case 0x81:
        staIzxHandler();
        break;
    case 0x82:
        nopImmHandler();
        break;
    case 0x83:
        saxIzxHandler();
        break;
    case 0x84:
        styZpHandler();
        break;
    case 0x85:
        staZpHandler();
        break;
    case 0x86:
        stxZpHandler();
        break;
    case 0x87:
        saxZpHandler();
        break;
    case 0x88:
        deyHandler();
        break;
    case 0x89:
        nopImmHandler();
        break;
    case 0x8A:
        txaHandler();
        break;
    case 0x8B:
        xaaImmHandler();
        break;
    case 0x8C:
        styAbsHandler();
        break;
    case 0x8D:
        staAbsHandler();
        break;
    case 0x8E:
        stxAbsHandler();
        break;
    case 0x8F:
        saxAbsHandler();
        break;
    case 0x90:
        bccHandler();
        break;
    case 0x91:
        staIzyHandler();
        break;
    case 0x92:
        crashHandler();
        break;
    case 0x93:
        ahxIzyHandler();
        break;
    case 0x94:
        styZpxHandler();
        break;
    case 0x95:
        staZpxHandler();
        break;
    case 0x96:
        stxZpyHandler();
        break;
    case 0x97:
        saxZpyHandler();
        break;
    case 0x98:
        tyaHandler();
        break;
    case 0x99:
        staAbyHandler();
        break;
    case 0x9A:
        txsHandler();
        break;
    case 0x9B:
        tasAbyHandler();
        break;
    case 0x9C:
        shyAbxHandler();
        break;
    case 0x9D:
        staAbxHandler();
        break;
    case 0x9E:
        shxAbyHandler();
        break;
    case 0x9F:
        ahxAbyHandler();
        break;
    case 0xA0:
        ldyImmHandler();
        break;
    case 0xA1:
        ldaIzxHandler();
        break;
    case 0xA2:
        ldxImmHandler();
        break;
    case 0xA3:
        laxIzxHandler();
        break;
    case 0xA4:
        ldyZpHandler();
        break;
    case 0xA5:
        ldaZpHandler();
        break;
    case 0xA6:
        ldxZpHandler();
        break;
    case 0xA7:
        laxZpHandler();
        break;
    case 0xA8:
        tayHandler();
        break;
    case 0xA9:
        ldaImmHandler();
        break;
    case 0xAA:
        taxHandler();
        break;
    case 0xAB:
        laxImmHandler();
        break;
    case 0xAC:
        ldyAbsHandler();
        break;
    case 0xAD:
        ldaAbsHandler();
        break;
    case 0xAE:
        ldxAbsHandler();
        break;
    case 0xAF:
        laxAbsHandler();
        break;
    case 0xB0:
        bcsHandler();
        break;
    case 0xB1:
        ldaIzyHandler();
        break;
    case 0xB2:
        crashHandler();
        break;
    case 0xB3:
        laxIzyHandler();
        break;
    case 0xB4:
        ldyZpxHandler();
        break;
    case 0xB5:
        ldaZpxHandler();
        break;
    case 0xB6:
        ldxZpyHandler();
        break;
    case 0xB7:
        laxZpyHandler();
        break;
    case 0xB8:
        clvHandler();
        break;
    case 0xB9:
        ldaAbyHandler();
        break;
    case 0xBA:
        tsxHandler();
        break;
    case 0xBB:
        lasAbyHandler();
        break;
    case 0xBC:
        ldyAbxHandler();
        break;
    case 0xBD:
        ldaAbxHandler();
        break;
    case 0xBE:
        ldxAbyHandler();
        break;
    case 0xBF:
        laxAbyHandler();
        break;
    case 0xC0:
        cpyImmHandler();
        break;
    case 0xC1:
        cmpIzxHandler();
        break;
    case 0xC2:
        nopImmHandler();
        break;
    case 0xC3:
        dcpIzxHandler();
        break;
    case 0xC4:
        cpyZpHandler();
        break;
    case 0xC5:
        cmpZpHandler();
        break;
    case 0xC6:
        decZpHandler();
        break;
    case 0xC7:
        dcpZpHandler();
        break;
    case 0xC8:
        inyHandler();
        break;
    case 0xC9:
        cmpImmHandler();
        break;
    case 0xCA:
        dexHandler();
        break;
    case 0xCB:
        axsImmHandler();
        break;
    case 0xCC:
        cpyAbsHandler();
        break;
    case 0xCD:
        cmpAbsHandler();
        break;
    case 0xCE:
        decAbsHandler();
        break;
    case 0xCF:
        dcpAbsHandler();
        break;
    case 0xD0:
        bneHandler();
        break;
    case 0xD1:
        cmpIzyHandler();
        break;
    case 0xD2:
        crashHandler();
        break;
    case 0xD3:
        dcpIzyHandler();
        break;
    case 0xD4:
        nopZpxHandler();
        break;
    case 0xD5:
        cmpZpxHandler();
        break;
    case 0xD6:
        decZpxHandler();
        break;
    case 0xD7:
        dcpZpxHandler();
        break;
    case 0xD8:
        cldHandler();
        break;
    case 0xD9:
        cmpAbyHandler();
        break;
    case 0xDA:
        nopHandler();
        break;
    case 0xDB:
        dcpAbyHandler();
        break;
    case 0xDC:
        nopAbxHandler();
        break;
    case 0xDD:
        cmpAbxHandler();
        break;
    case 0xDE:
        decAbxHandler();
        break;
    case 0xDF:
        dcpAbxHandler();
        break;
    case 0xE0:
        cpxImmHandler();
        break;
    case 0xE1:
        sbcIzxHandler();
        break;
    case 0xE2:
        nopImmHandler();
        break;
    case 0xE3:
        iscIzxHandler();
        break;
    case 0xE4:
        cpxZpHandler();
        break;
    case 0xE5:
        sbcZpHandler();
        break;
    case 0xE6:
        incZpHandler();
        break;
    case 0xE7:
        iscZpHandler();
        break;
    case 0xE8:
        inxHandler();
        break;
    case 0xE9:
        sbcImmHandler();
        break;
    case 0xEA:
        nopHandler();
        break;
    case 0xEB:
        sbcImmHandler();
        break;
    case 0xEC:
        cpxAbsHandler();
        break;
    case 0xED:
        sbcAbsHandler();
        break;
    case 0xEE:
        incAbsHandler();
        break;
    case 0xEF:
        iscAbsHandler();
        break;
    case 0xF0:
        beqHandler();
        break;
    case 0xF1:
        sbcIzyHandler();
        break;
    case 0xF2:
        crashHandler();
        break;
    case 0xF3:
        iscIzyHandler();
        break;
    case 0xF4:
        nopZpxHandler();
        break;
    case 0xF5:
        sbcZpxHandler();
        break;
    case 0xF6:
        incZpxHandler();
        break;
    case 0xF7:
        iscZpxHandler();
        break;
    case 0xF8:
        sedHandler();
        break;
    case 0xF9:
        sbcAbyHandler();
        break;
    case 0xFA:
        nopHandler();
        break;
    case 0xFB:
        iscAbyHandler();
        break;
    case 0xFC:
        nopAbxHandler();
        break;
    case 0xFD:
        sbcAbxHandler();
        break;
    case 0xFE:
        incAbxHandler();
        break;
    case 0xFF:
        iscAbxHandler();
        break;
    default:
        cerr << "Unexpected opcode (0x" << hex << (int)opcode << ") in crashHandler!" << endl;
        break;
    }
}

void Assembly::brkHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->pushStack(this->cpu->getPC() >> 8);
    this->cpu->pushStack(this->cpu->getPC() & 0xFF);
    this->cpu->getStatus().setBreakFlag(true);
    this->cpu->pushStack(this->cpu->getStatus().getP());
    this->cpu->setPC(this->cpu->getMemory(0xFFFE) | (this->cpu->getMemory(0xFFFF) << 8));
    this->cpu->getStatus().setInterruptFlag(true);
    this->cpu->setCycles(this->cpu->getCycles() + 7);
}

void Assembly::aslAHandler()
{
    uint8_t accumulator = this->cpu->getAccumulator();
    this->cpu->getStatus().setCarryFlag(accumulator & 0x80);
    uint8_t result = accumulator << 1;
    this->cpu->setAccumulator(result);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::aslZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->getStatus().setCarryFlag(value & 0x80);
    uint8_t result = value << 1;
    this->cpu->write(operand, result);
    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::aslAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->getStatus().setCarryFlag(value & 0x80);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->getStatus().setZeroFlag(result == 0);
    this->cpu->getStatus().setNegativeFlag(result & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::oraImmHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | operand);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::oraZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::oraAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::sloZpHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(operand);
    this->cpu->getStatus().setCarryFlag(value & 0x80);
    uint8_t result = value << 1;
    this->cpu->write(operand, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::sloAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->getStatus().setCarryFlag(value & 0x80);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::bplHandler()
{
    int8_t offset = static_cast<int8_t>(this->cpu->getMemory(this->cpu->getPC() + 1));
    if (!this->cpu->getStatus().getNegativeFlag())
    {
        this->cpu->setPC(this->cpu->getPC() + 2 + offset);
        this->cpu->setCycles(this->cpu->getCycles() + 4);
    }
    else
    {
        this->cpu->setPC(this->cpu->getPC() + 2);
        this->cpu->setCycles(this->cpu->getCycles() + 2);
    }
}

void Assembly::jsrAbsHandler()
{
    uint16_t address = this->cpu->readMemory16(this->cpu->getPC() + 1);

    uint16_t returnAddress = this->cpu->getPC() + 2;

    this->cpu->pushStack(returnAddress >> 8);
    this->cpu->pushStack(returnAddress & 0xFF);
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

void Assembly::phpHandler()
{
    uint8_t status = this->cpu->getStatus().getP();
    this->cpu->pushStack(status);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 3);
}

void Assembly::nopZpHandler()
{
    uint8_t operand = this->cpu->read(this->cpu->getPC() + 1);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(2);
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

void Assembly::nopAbsHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 3);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
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

void Assembly::bvcHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    if (!this->cpu->getStatus().getOverflowFlag())
    {

        int8_t offset = static_cast<int8_t>(operand);
        this->cpu->setPC(this->cpu->getPC() + 2 + offset);
    }
    else
    {

        this->cpu->setPC(this->cpu->getPC() + 2);
    }

    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::rorAHandler()
{
    bool carry = this->cpu->getStatus().getCarryFlag();
    uint8_t accumulator = this->cpu->getAccumulator();
    uint8_t result = (accumulator >> 1) | (carry << 7);

    this->cpu->getStatus().setCarryFlag(accumulator & 0x01);

    this->cpu->setAccumulator(result);

    this->cpu->getStatus().setZeroFlag(result);
    this->cpu->getStatus().setNegativeFlag(result);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::rraImmHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    bool carry = this->cpu->getStatus().getCarryFlag();
    uint8_t result = (operand >> 1) | (carry << 7);

    this->cpu->getStatus().setCarryFlag(operand & 0x01);

    uint8_t accumulator = this->cpu->getAccumulator();
    uint8_t sum = accumulator + result + (carry ? 1 : 0);

    this->cpu->setAccumulator(sum);
    this->cpu->getStatus().setZeroFlag(sum);
    this->cpu->getStatus().setNegativeFlag(sum);
    this->cpu->getStatus().setCarryFlag(sum);
    this->cpu->getStatus().setOverflowFlagAOR(accumulator, result, sum);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
}

void Assembly::ancImmHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t result = this->cpu->getAccumulator() & operand;
    this->cpu->setAccumulator(result);

    bool carry = result & 0x80;
    this->cpu->getStatus().setCarryFlag(carry);

    this->cpu->getStatus().setNegativeFlag(result);

    this->cpu->getStatus().setZeroFlag(result);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
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

void Assembly::rlaImmHandler()
{
    uint8_t value = this->cpu->getMemory(this->cpu->getPC() + 1);

    uint8_t result = (value << 1) | this->cpu->getStatus().getCarryFlag();

    this->cpu->getStatus().setCarryFlag(value & 0x80);
    this->cpu->setAccumulator(this->cpu->getAccumulator() & result);
    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator());
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator());
}

void Assembly::bmiHandler()
{

    int8_t operand = static_cast<int8_t>(this->cpu->getMemory(this->cpu->getPC() + 1));

    if (this->cpu->getStatus().getNegativeFlag())
    {

        this->cpu->setPC(this->cpu->getPC() + 2 + operand);
    }
    else
    {

        this->cpu->setPC(this->cpu->getPC() + 2);
    }

    this->cpu->setCycles(this->cpu->getCycles() + 2 + (this->cpu->getPC() != operand ? 0 : 1));
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

void Assembly::lsrAHandler()
{

    uint8_t accumulator = this->cpu->getAccumulator();

    bool carry = accumulator & 0x01;

    accumulator >>= 1;

    this->cpu->setAccumulator(accumulator);

    this->cpu->getStatus().setCarryFlag(carry);

    this->cpu->getStatus().setZeroFlag(accumulator);
    this->cpu->getStatus().setNegativeFlag(accumulator);

    this->cpu->setPC(this->cpu->getPC() + 1);
    this->cpu->setCycles(this->cpu->getCycles() + 2);
}

void Assembly::nopZpxHandler()
{
    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 4);
}

void Assembly::sreImmHandler()
{

    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);

    bool carry = operand & 0x01;
    uint8_t result = operand >> 1;

    this->cpu->getStatus().setCarryFlag(carry);

    uint8_t accumulator = this->cpu->getAccumulator();
    this->cpu->setAccumulator(accumulator ^ result);

    this->cpu->write(this->cpu->getPC() + 1, result);

    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator());
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator());

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
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

void Assembly::oraIzxHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint8_t addressLow = this->cpu->getMemory(operand + this->cpu->getXRegister());
    uint8_t addressHigh = this->cpu->getMemory(operand + this->cpu->getXRegister() + 1);
    uint16_t address = (addressHigh << 8) | addressLow;
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 6);
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
    uint8_t lastOpcodeRead = this->lastOpcode;

    cerr << "Unexpected opcode (0x" << hex << (int)lastOpcodeRead << ") in crashHandler!" << endl;
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
    uint16_t address = operand + this->cpu->getXRegister();

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

void Assembly::oraIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint16_t baseAddress = this->cpu->getMemory(operand) | (this->cpu->getMemory((operand + 1) & 0xFF) << 8);
    uint16_t address = baseAddress + this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | value);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 5);
}

void Assembly::sloIzyHandler()
{
    uint8_t operand = this->cpu->getMemory(this->cpu->getPC() + 1);
    uint16_t baseAddress = this->cpu->getMemory(operand) | (this->cpu->getMemory((operand + 1) & 0xFF) << 8);
    uint16_t address = baseAddress + this->cpu->getYRegister();
    uint8_t value = this->cpu->getMemory(address);
    this->cpu->getStatus().setCarryFlag(value & 0x80);
    uint8_t result = value << 1;
    this->cpu->write(address, result);

    this->cpu->setAccumulator(this->cpu->getAccumulator() | result);
    this->cpu->getStatus().setZeroFlag(this->cpu->getAccumulator() == 0);
    this->cpu->getStatus().setNegativeFlag(this->cpu->getAccumulator() & 0x80);

    this->cpu->setPC(this->cpu->getPC() + 2);
    this->cpu->setCycles(this->cpu->getCycles() + 8);
}
