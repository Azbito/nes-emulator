#include "Assembly.h"

void Assembly::executeOpcode(uint8_t opcode)
{
    auto it = Assembly::opcodeMap.find(opcode);
    if (it != Assembly::opcodeMap.end())
    {
        cout << "OPCODE: " << hex << opcode;
        it->second(*this);

        if (cpu->status.getZeroFlag())
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

void Assembly::invokeAllHandlers()
{
    auto handlerLambda = [this]()
    {
        this->ldaHandler();
        this->ldxHandler();
        this->ldyHandler();
        this->staHandler();
        this->clcHandler();
        this->adcHandler();
        this->sbcHandler();
        this->aslHandler();
        this->lsrHandler();
        this->nopHandler();
        this->bneHandler();
        this->beqHandler();
        this->bitHandler();
        this->decHandler();
        this->dexHandler();
        this->deyHandler();
        this->secHandler();
        this->sedHandler();
        this->seiHandler();
        this->bccHandler();
        this->bcsHandler();
        this->taxHandler();
        this->tayHandler();
        this->txaHandler();
        this->tyaHandler();
        this->tsxHandler();
        this->txsHandler();
        this->plaHandler();
        this->phaHandler();
        this->plpHandler();
        this->phpHandler();
        this->brkHandler();
        this->oraHandler();
        this->bplHandler();
        this->jsrHandler();
        this->andHandler();
        this->rolHandler();
        this->bmiHandler();
        this->eorHandler();
        this->rorHandler();
        this->rtiHandler();
        this->cliHandler();
        this->bvcHandler();
        this->rtsHandler();
        this->bvsHandler();
        this->styHandler();
        this->stxHandler();
    };

    handlerLambda();
}

map<uint8_t, function<void(Assembly &)>> Assembly::opcodeMap = {
    {0x00, [](Assembly &assembly)
     { assembly.brkHandler(); }},
    {0x01, [](Assembly &assembly)
     { assembly.oraHandler(); }},
    {0x05, [](Assembly &assembly)
     { assembly.oraHandler(); }},
    {0x06, [](Assembly &assembly)
     { assembly.aslHandler(); }},
    {0x08, [](Assembly &assembly)
     { assembly.phpHandler(); }},
    {0x09, [](Assembly &assembly)
     { assembly.oraHandler(); }},
    {0x0A, [](Assembly &assembly)
     { assembly.aslHandler(); }},
    {0x0D, [](Assembly &assembly)
     { assembly.oraHandler(); }},
    {0x0E, [](Assembly &assembly)
     { assembly.aslHandler(); }},

    {0x10, [](Assembly &assembly)
     { assembly.bplHandler(); }},
    {0x11, [](Assembly &assembly)
     { assembly.oraHandler(); }},
    {0x15, [](Assembly &assembly)
     { assembly.oraHandler(); }},
    {0x16, [](Assembly &assembly)
     { assembly.aslHandler(); }},
    {0x18, [](Assembly &assembly)
     { assembly.clcHandler(); }},
    {0x19, [](Assembly &assembly)
     { assembly.oraHandler(); }},
    {0x1D, [](Assembly &assembly)
     { assembly.oraHandler(); }},
    {0x1E, [](Assembly &assembly)
     { assembly.aslHandler(); }},

    {0x20, [](Assembly &assembly)
     { assembly.jsrHandler(); }},
    {0x21, [](Assembly &assembly)
     { assembly.andHandler(); }},
    {0x24, [](Assembly &assembly)
     { assembly.bitHandler(); }},
    {0x25, [](Assembly &assembly)
     { assembly.andHandler(); }},
    {0x26, [](Assembly &assembly)
     { assembly.rolHandler(); }},
    {0x28, [](Assembly &assembly)
     { assembly.plpHandler(); }},
    {0x29, [](Assembly &assembly)
     { assembly.andHandler(); }},
    {0x2A, [](Assembly &assembly)
     { assembly.rolHandler(); }},
    {0x2C, [](Assembly &assembly)
     { assembly.bitHandler(); }},
    {0x2D, [](Assembly &assembly)
     { assembly.andHandler(); }},
    {0x2E, [](Assembly &assembly)
     { assembly.rolHandler(); }},

    {0x30, [](Assembly &assembly)
     { assembly.bmiHandler(); }},
    {0x31, [](Assembly &assembly)
     { assembly.andHandler(); }},
    {0x35, [](Assembly &assembly)
     { assembly.andHandler(); }},
    {0x36, [](Assembly &assembly)
     { assembly.rolHandler(); }},
    {0x38, [](Assembly &assembly)
     { assembly.secHandler(); }},
    {0x39, [](Assembly &assembly)
     { assembly.andHandler(); }},
    {0x3D, [](Assembly &assembly)
     { assembly.andHandler(); }},
    {0x3E, [](Assembly &assembly)
     { assembly.rolHandler(); }},

    {0x40, [](Assembly &assembly)
     { assembly.rtiHandler(); }},
    {0x41, [](Assembly &assembly)
     { assembly.eorHandler(); }},
    {0x45, [](Assembly &assembly)
     { assembly.eorHandler(); }},
    {0x46, [](Assembly &assembly)
     { assembly.lsrHandler(); }},
    {0x48, [](Assembly &assembly)
     { assembly.phaHandler(); }},
    {0x49, [](Assembly &assembly)
     { assembly.eorHandler(); }},
    {0x4A, [](Assembly &assembly)
     { assembly.lsrHandler(); }},
    {0x4C, [](Assembly &assembly)
     { assembly.jmpHandler(); }},
    {0x4D, [](Assembly &assembly)
     { assembly.eorHandler(); }},
    {0x4E, [](Assembly &assembly)
     { assembly.lsrHandler(); }},

    {0x50, [](Assembly &assembly)
     { assembly.bvcHandler(); }},
    {0x51, [](Assembly &assembly)
     { assembly.eorHandler(); }},
    {0x55, [](Assembly &assembly)
     { assembly.eorHandler(); }},
    {0x56, [](Assembly &assembly)
     { assembly.lsrHandler(); }},
    {0x58, [](Assembly &assembly)
     { assembly.cliHandler(); }},
    {0x59, [](Assembly &assembly)
     { assembly.eorHandler(); }},
    {0x5D, [](Assembly &assembly)
     { assembly.eorHandler(); }},
    {0x5E, [](Assembly &assembly)
     { assembly.lsrHandler(); }},

    {0x60, [](Assembly &assembly)
     { assembly.rtsHandler(); }},
    {0x61, [](Assembly &assembly)
     { assembly.adcHandler(); }},
    {0x65, [](Assembly &assembly)
     { assembly.adcHandler(); }},
    {0x66, [](Assembly &assembly)
     { assembly.rorHandler(); }},
    {0x68, [](Assembly &assembly)
     { assembly.plaHandler(); }},
    {0x69, [](Assembly &assembly)
     { assembly.adcHandler(); }},
    {0x6A, [](Assembly &assembly)
     { assembly.rorHandler(); }},
    {0x6C, [](Assembly &assembly)
     { assembly.jmpHandler(); }},
    {0x6D, [](Assembly &assembly)
     { assembly.adcHandler(); }},
    {0x6E, [](Assembly &assembly)
     { assembly.rorHandler(); }},

    {0x70, [](Assembly &assembly)
     { assembly.bvsHandler(); }},
    {0x71, [](Assembly &assembly)
     { assembly.adcHandler(); }},
    {0x75, [](Assembly &assembly)
     { assembly.adcHandler(); }},
    {0x76, [](Assembly &assembly)
     { assembly.rorHandler(); }},
    {0x78, [](Assembly &assembly)
     { assembly.seiHandler(); }},
    {0x79, [](Assembly &assembly)
     { assembly.adcHandler(); }},
    {0x7D, [](Assembly &assembly)
     { assembly.adcHandler(); }},
    {0x7E, [](Assembly &assembly)
     { assembly.rorHandler(); }},

    {0x80, [](Assembly &assembly)
     { assembly.nopHandler(); }},
    {0x81, [](Assembly &assembly)
     { assembly.staHandler(); }},
    {0x84, [](Assembly &assembly)
     { assembly.styHandler(); }},
    {0x85, [](Assembly &assembly)
     { assembly.staHandler(); }},
    {0x86, [](Assembly &assembly)
     { assembly.stxHandler(); }},
    {0x88, [](Assembly &assembly)
     { assembly.deyHandler(); }},
    {0x8A, [](Assembly &assembly)
     { assembly.txaHandler(); }},
    {0x8C, [](Assembly &assembly)
     { assembly.styHandler(); }},
    {0x8D, [](Assembly &assembly)
     { assembly.staHandler(); }},
    {0x8E, [](Assembly &assembly)
     { assembly.stxHandler(); }},

    {0x90, [](Assembly &assembly)
     { assembly.bccHandler(); }},
    {0x91, [](Assembly &assembly)
     { assembly.staHandler(); }},
    {0x94, [](Assembly &assembly)
     { assembly.styHandler(); }},
    {0x95, [](Assembly &assembly)
     { assembly.staHandler(); }},
    {0x96, [](Assembly &assembly)
     { assembly.stxHandler(); }},
    {0x98, [](Assembly &assembly)
     { assembly.tyaHandler(); }},
    {0x99, [](Assembly &assembly)
     { assembly.staHandler(); }},
    {0x9A, [](Assembly &assembly)
     { assembly.txsHandler(); }},
    {0x9D, [](Assembly &assembly)
     { assembly.staHandler(); }},
};

void Assembly::ldaHandler()
{
    cpu->A = cpu->read(cpu->PC + 1);
    cpu->PC += 2;
    cpu->cycles += 2;
}

void Assembly::ldxHandler()
{
    cpu->X = cpu->read(cpu->PC + 1);
    cpu->PC += 2;
    cpu->cycles += 2;
}

void Assembly::ldyHandler()
{
    cpu->Y = cpu->read(cpu->PC + 1);
    cpu->PC += 2;
    cpu->cycles += 2;
}

void Assembly::staHandler()
{
    cpu->write(cpu->read(cpu->PC + 1), cpu->A);
    cpu->PC += 2;
    cpu->cycles += 3;
}

void Assembly::clcHandler()
{
    cpu->status.P &= ~0x01;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::adcHandler()
{
    uint8_t value = cpu->read(cpu->PC + 1);
    uint16_t result = cpu->A + value + (cpu->status.getCarryFlag() ? 1 : 0);

    cpu->A = result & 0xFF;
    cpu->status.setCarryFlag(result > 0xFF);
    cpu->status.setZeroFlag(cpu->A == 0);
    cpu->status.setNegativeFlag(cpu->A & 0x80);

    cpu->PC += 2;
    cpu->cycles += 2;
}

void Assembly::sbcHandler()
{
    uint8_t value = cpu->read(cpu->PC + 1);
    uint16_t result = cpu->A - value - (cpu->status.getCarryFlag() ? 0 : 1);

    cpu->A = result & 0xFF;
    cpu->status.setCarryFlag(result < 0x100);
    cpu->status.setZeroFlag(cpu->A == 0);
    cpu->status.setNegativeFlag(cpu->A & 0x80);

    cpu->PC += 2;
    cpu->cycles += 2;
}

void Assembly::aslHandler()
{
    cpu->status.setCarryFlag(cpu->A & 0x80);
    cpu->A <<= 1;
    cpu->status.setZeroFlag(cpu->A == 0);
    cpu->status.setNegativeFlag(cpu->A & 0x80);
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::lsrHandler()
{
    cpu->status.setCarryFlag(cpu->A & 0x01);
    cpu->A >>= 1;
    cpu->status.setZeroFlag(cpu->A == 0);
    cpu->status.setNegativeFlag(false);
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::nopHandler()
{
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::bneHandler()
{
    if ((cpu->status.getZeroFlag()) == 0)
    {
        cpu->PC = cpu->read(cpu->PC + 1);
        cpu->cycles += 3;
    }
    else
    {
        cpu->PC += 2;
        cpu->cycles += 2;
    }
}

void Assembly::beqHandler()
{
    if (cpu->status.getZeroFlag())
    {
        cpu->PC = cpu->operand;
        cpu->cycles += 3;
    }
    else
    {
        cpu->PC += 2;
        cpu->cycles += 2;
    }
}

void Assembly::bitHandler()
{
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::decHandler()
{
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::dexHandler()
{
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::deyHandler()
{
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::secHandler()
{
    cpu->status.P |= 0x01;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::sedHandler()
{
    cpu->status.P |= 0x08;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::seiHandler()
{
    cpu->status.P |= 0x04;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::bccHandler()
{
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::bcsHandler()
{
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::taxHandler()
{
    cpu->X = cpu->A;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::tayHandler()
{
    cpu->Y = cpu->A;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::txaHandler()
{
    cpu->A = cpu->X;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::tyaHandler()
{
    cpu->A = cpu->Y;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::tsxHandler()
{
    cpu->X = cpu->SP;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::txsHandler()
{
    cpu->SP = cpu->X;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::plaHandler()
{
    cpu->A = cpu->read(cpu->SP--);
    cpu->PC++;
    cpu->cycles += 4;
}

void Assembly::phaHandler()
{
    cpu->write(cpu->SP--, cpu->A);
    cpu->PC++;
    cpu->cycles += 3;
}

void Assembly::plpHandler()
{
    cpu->status.P = cpu->read(cpu->SP--);
    cpu->PC++;
    cpu->cycles += 4;
}

void Assembly::phpHandler()
{
    cpu->write(cpu->SP--, cpu->status.P);
    cpu->PC++;
    cpu->cycles += 3;
}

void Assembly::brkHandler()
{
    cout << "BRK!";

    uint8_t lowByte = cpu->read(cpu->PC);
    uint8_t highByte = cpu->read(cpu->PC + 1);
    cpu->PC += 2;

    cpu->write(0x0100 + cpu->SP, (cpu->PC >> 8) & 0xFF);
    cpu->SP--;
    cpu->write(0x0100 + cpu->SP, cpu->PC & 0xFF);
    cpu->SP--;

    cpu->write(0x0100 + cpu->SP, cpu->status.P);
    cpu->SP--;

    cpu->status.setBreakFlag(true);

    uint8_t lowByte2 = cpu->read(0xFFFE);
    uint8_t highByte2 = cpu->read(0xFFFF);
    cpu->PC = (highByte2 << 8) | lowByte2;

    cpu->cycles = 7;
}

void Assembly::oraHandler()
{
    uint8_t value = cpu->read(cpu->PC + 1);
    cpu->A |= value;
    cpu->PC += 2;
    cpu->cycles += 2;
}

void Assembly::bplHandler()
{
    if ((cpu->status.getNegativeFlag()) == 0)
    {
        cpu->PC = cpu->read(cpu->PC + 1);
        cpu->cycles += 3;
    }
    else
    {
        cpu->PC += 2;
        cpu->cycles += 2;
    }
}

void Assembly::jsrHandler()
{
    uint16_t addr = cpu->read(cpu->PC + 1) | (cpu->read(cpu->PC + 2) << 8);
    cpu->PC += 3;
    cpu->write(0x0100 + cpu->SP, (cpu->PC >> 8) & 0xFF);
    cpu->SP--;
    cpu->write(0x0100 + cpu->SP, cpu->PC & 0xFF);
    cpu->SP--;
    cpu->PC = addr - 1;
    cpu->cycles += 6;
}

void Assembly::andHandler()
{
    uint8_t value = cpu->read(cpu->PC + 1);
    cpu->A &= value;
    cpu->PC += 2;
    cpu->cycles += 2;
}

void Assembly::rolHandler()
{
    uint8_t value = cpu->A;
    cpu->A = (cpu->A << 1) | (cpu->status.getCarryFlag() ? 1 : 0);
    cpu->status.setCarryFlag(value & 0x80);
    cpu->status.setZeroFlag(cpu->A == 0);
    cpu->status.setNegativeFlag(cpu->A & 0x80);
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::bmiHandler()
{
    if (cpu->status.getNegativeFlag())
    {
        cpu->PC = cpu->read(cpu->PC + 1);
        cpu->cycles += 3;
    }
    else
    {
        cpu->PC += 2;
        cpu->cycles += 2;
    }
}

void Assembly::eorHandler()
{
    uint8_t value = cpu->read(cpu->PC + 1);
    cpu->A ^= value;
    cpu->PC += 2;
    cpu->cycles += 2;
}

void Assembly::rorHandler()
{
    uint8_t value = cpu->A;
    cpu->A = (cpu->status.getCarryFlag() ? 0x80 : 0) | (cpu->A >> 1);
    cpu->status.setCarryFlag(value & 0x01);
    cpu->status.setZeroFlag(cpu->A == 0);
    cpu->status.setNegativeFlag(cpu->A & 0x80);
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::rtiHandler()
{
    cpu->status.P = cpu->read(0x0100 + cpu->SP);
    cpu->SP++;
    cpu->PC = cpu->read(0x0100 + cpu->SP) | (cpu->read(0x0100 + cpu->SP + 1) << 8);
    cpu->SP += 2;
    cpu->cycles += 6;
}

void Assembly::cliHandler()
{
    cpu->status.P &= ~0x04;
    cpu->PC++;
    cpu->cycles += 2;
}

void Assembly::bvcHandler()
{
    if (!(cpu->status.getOverflowFlag()))
    {
        cpu->PC = cpu->read(cpu->PC + 1);
        cpu->cycles += 3;
    }
    else
    {
        cpu->PC += 2;
        cpu->cycles += 2;
    }
}

void Assembly::bvsHandler()
{
    if (cpu->status.getOverflowFlag())
    {
        cpu->PC = cpu->read(cpu->PC + 1);
        cpu->cycles += 3;
    }
    else
    {
        cpu->PC += 2;
        cpu->cycles += 2;
    }
}

void Assembly::styHandler()
{
    uint16_t addr = cpu->read(cpu->PC + 1) | (cpu->read(cpu->PC + 2) << 8);
    cpu->write(addr, cpu->Y);
    cpu->PC += 3;
    cpu->cycles += 4;
}

void Assembly::stxHandler()
{
    uint16_t addr = cpu->read(cpu->PC + 1) | (cpu->read(cpu->PC + 2) << 8);
    cpu->write(addr, cpu->X);
    cpu->PC += 3;
    cpu->cycles += 4;
}

void Assembly::jmpHandler()
{
    uint8_t opcode = cpu->read(cpu->PC);
    uint16_t address;

    if (opcode == 0x4C)
    {
        address = cpu->read(cpu->PC + 1) | (cpu->read(cpu->PC + 2) << 8);
        cpu->PC = address;
        cpu->cycles += 3;
    }
    else if (opcode == 0x6C)
    {
        uint16_t indirectAddress = cpu->read(cpu->PC + 1) | (cpu->read(cpu->PC + 2) << 8);
        uint16_t jumpAddress = cpu->read(indirectAddress) | (cpu->read(indirectAddress + 1) << 8);
        cpu->PC = jumpAddress;
        cpu->cycles += 5;
    }
    cpu->PC += 3;
}

void Assembly::rtsHandler()
{
    uint8_t lowByte = cpu->read(0x0100 + cpu->SP);
    cpu->SP++;

    uint8_t highByte = cpu->read(0x0100 + cpu->SP);
    cpu->SP++;

    uint16_t returnAddress = (highByte << 8) | lowByte;

    cpu->PC = returnAddress;

    cpu->PC++;

    cpu->cycles += 6;
}
