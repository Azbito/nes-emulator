#include "Assembly.h"

void Assembly::execute(uint8_t opcode)
{
    static const std::map<uint8_t, std::function<void()>> opcodeMap = {
        {0xA9, [this]()
         { ldaHandler(); }},
        {0xA2, [this]()
         { ldxHandler(); }},
        {0xA0, [this]()
         { ldyHandler(); }},
        {0x85, [this]()
         { staHandler(); }},
        {0x18, [this]()
         { clcHandler(); }},
        {0x69, [this]()
         { adcHandler(); }},
        {0xE9, [this]()
         { sbcHandler(); }},
        {0x0A, [this]()
         { aslHandler(); }},
        {0x4A, [this]()
         { lsrHandler(); }},
        {0x1A, [this]()
         { nopHandler(); }},
        {0xD0, [this]()
         { bneHandler(); }},
        {0xF0, [this]()
         { beqHandler(); }},
        {0x24, [this]()
         { bitHandler(); }},
        {0xD6, [this]()
         { decHandler(); }},
        {0xCA, [this]()
         { dexHandler(); }},
        {0x88, [this]()
         { deyHandler(); }},
        {0x38, [this]()
         { secHandler(); }},
        {0xF8, [this]()
         { sedHandler(); }},
        {0x78, [this]()
         { seiHandler(); }},
        {0x90, [this]()
         { bccHandler(); }},
        {0xB0, [this]()
         { bcsHandler(); }},
        {0xAA, [this]()
         { taxHandler(); }},
        {0xA8, [this]()
         { tayHandler(); }},
        {0x8A, [this]()
         { txaHandler(); }},
        {0x98, [this]()
         { tyaHandler(); }},
        {0xBA, [this]()
         { tsxHandler(); }},
        {0x9A, [this]()
         { txsHandler(); }},
        {0x68, [this]()
         { plaHandler(); }},
        {0x48, [this]()
         { phaHandler(); }},
        {0x28, [this]()
         { plpHandler(); }},
        {0x08, [this]()
         { phpHandler(); }}};

    auto it = opcodeMap.find(opcode);
    if (it != opcodeMap.end())
    {
        it->second();
    }
    else
    {
        std::cerr << "Unknown opcode: " << std::hex << (int)opcode << std::dec << std::endl;
        cpu->PC++;
    }
}

void Assembly::ldaHandler()
{
    cpu->A = cpu->read(cpu->PC + 1);
    cpu->PC += 2;
}

void Assembly::ldxHandler()
{
    cpu->X = cpu->read(cpu->PC + 1);
    cpu->PC += 2;
}

void Assembly::ldyHandler()
{
    cpu->Y = cpu->read(cpu->PC + 1);
    cpu->PC += 2;
}

void Assembly::staHandler()
{
    cpu->write(cpu->read(cpu->PC + 1), cpu->A);
    cpu->PC += 2;
}

void Assembly::clcHandler()
{
    cpu->P &= ~0x01;
    cpu->PC++;
}

void Assembly::adcHandler()
{
    uint8_t value = cpu->read(cpu->PC + 1);
    cpu->A += value;
    cpu->PC += 2;
}

void Assembly::sbcHandler()
{
    uint8_t value = cpu->read(cpu->PC + 1);
    cpu->A -= value;
    cpu->PC += 2;
}

void Assembly::aslHandler()
{
    cpu->A <<= 1;
    cpu->PC++;
}

void Assembly::lsrHandler()
{
    cpu->A >>= 1;
    cpu->PC++;
}

void Assembly::nopHandler()
{
    cpu->PC++;
}

void Assembly::bneHandler()
{
    if ((cpu->P & 0x02) == 0)
    {
        cpu->PC = cpu->read(cpu->PC + 1);
    }
    else
    {
        cpu->PC += 2;
    }
}

void Assembly::beqHandler()
{
    if (cpu->getZeroFlag())
    {
        cpu->PC = cpu->operand;
    }
}

void Assembly::bitHandler() { cpu->PC++; }

void Assembly::decHandler() { cpu->PC++; }

void Assembly::dexHandler() { cpu->PC++; }

void Assembly::deyHandler() { cpu->PC++; }

void Assembly::secHandler()
{
    cpu->P |= 0x01;
    cpu->PC++;
}

void Assembly::sedHandler()
{
    cpu->P |= 0x08;
    cpu->PC++;
}

void Assembly::seiHandler()
{
    cpu->P |= 0x04;
    cpu->PC++;
}

void Assembly::bccHandler() { cpu->PC++; }

void Assembly::bcsHandler() { cpu->PC++; }

void Assembly::taxHandler()
{
    cpu->X = cpu->A;
    cpu->PC++;
}
void Assembly::tayHandler()
{
    cpu->Y = cpu->A;
    cpu->PC++;
}

void Assembly::txaHandler()
{
    cpu->A = cpu->X;
    cpu->PC++;
}

void Assembly::tyaHandler()
{
    cpu->A = cpu->Y;
    cpu->PC++;
}

void Assembly::tsxHandler()
{
    cpu->X = cpu->SP;
    cpu->PC++;
}

void Assembly::txsHandler()
{
    cpu->SP = cpu->X;
    cpu->PC++;
}

void Assembly::plaHandler()
{
    cpu->A = cpu->read(cpu->SP--);
    cpu->PC++;
}

void Assembly::phaHandler()
{
    cpu->write(cpu->SP--, cpu->A);
    cpu->PC++;
}

void Assembly::plpHandler()
{
    cpu->P = cpu->read(cpu->SP--);
    cpu->PC++;
}

void Assembly::phpHandler()
{
    cpu->write(cpu->SP--, cpu->P);
    cpu->PC++;
}
