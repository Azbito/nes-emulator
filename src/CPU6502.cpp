#include "CPU6502.h"

using BYTE = unsigned char;
using WORD = unsigned short;
using U32 = unsigned int;

BYTE CPU6502::init(U32 cycles, Memory &memory)
{
    BYTE data = memory.readOperator(processor.PC);

    processor.PC++;
    cycles--;

    return data;
};

void CPU6502::Memory::init()
{
    for (U32 i = 0; i < MAX_MEM; i++)
    {
        data[i] = 0;
    }
}

BYTE CPU6502::Memory::readOperator(U32 address)
{
    return data[address];
}

void CPU6502::Memory::writeOperator(U32 address, BYTE value)
{
    data[address] = value;
}

void CPU6502::reset(Memory &memory)
{
    processor.PC = 0xFFFC;
    processor.SP = 0x00FF;

    processor.DECIMAL_MODE = processor.CARRY_FLAG = processor.ZERO_FLAG = processor.BREAK_COMMAND = processor.INTERRUPT_DISABLE = processor.NEGATIVE_FLAG = processor.OVERFLOW_FLAG = 0;
    processor.A = processor.X = processor.Y = 0;

    memory.init();

    Cycles cycles;
    cycles.reset();
}

BYTE CPU6502::fetch(Cycles &cycles, Memory &memory)
{
    BYTE data = memory.readOperator(processor.PC);

    processor.PC++;
    cycles.consume(1);

    return data;
};

BYTE CPU6502::popStack()
{
    CPU6502::Memory memory;

    BYTE value = memory.readMemory(processor.SP + 0x0100);
    processor.SP++;

    return value;
}

BYTE CPU6502::read(U32 &cycles, Memory &memory)
{
    BYTE data = memory.readOperator(processor.PC);

    cycles--;

    return data;
};

void CPU6502::pushStack(BYTE value)
{
    processor.SP--;

    memory.writeOperator(0x0100 + processor.SP, value);
}

void CPU6502::PHA()
{
    pushStack(processor.A);

    std::cout << "PHA - Pushed A (" << (int)processor.A << ") to stack at SP: " << (int)processor.SP << std::endl;
}

WORD CPU6502::Memory::fetchWord(U32 address)
{
    BYTE lowByte = readMemory(address);
    BYTE highByte = readMemory(address + 1);

    return (highByte << 8) | lowByte;
}

void CPU6502::pushStatus(Memory &memory)
{
    WORD address = 0x0100 + processor.SP;

    BYTE status = 0;
    status |= processor.CARRY_FLAG << 0;
    status |= processor.ZERO_FLAG << 1;
    status |= processor.INTERRUPT_DISABLE << 2;
    status |= processor.DECIMAL_MODE << 3;
    status |= processor.BREAK_COMMAND << 4;
    status |= processor.OVERFLOW_FLAG << 6;
    status |= processor.NEGATIVE_FLAG << 7;

    memory.writeOperator(address, status);

    processor.SP--;
}

void CPU6502::pushRegisters(Memory &memory)
{

    WORD address = 0x0100 + processor.SP;
    memory.writeOperator(address, processor.A);
    processor.SP--;

    address = 0x0100 + processor.SP;
    memory.writeOperator(address, processor.X);
    processor.SP--;

    address = 0x0100 + processor.SP;
    memory.writeOperator(address, processor.Y);
    processor.SP--;
}

BYTE CPU6502::Memory::readMemory(WORD address)
{
    if (address < MAX_MEM)
    {
        return CPU6502::Memory::data[address];
    }

    return 0;
}

void CPU6502::execute(Cycles &cycles, Memory &memory)
{
    CPU6502::Memory mem;
    CPU6502::Handlers handle;

    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE fetchedInstruction = cpu.fetch(cycles, memory);
    std::cout << "data: 0x" << std::hex << static_cast<int>(fetchedInstruction) << std::endl;

    while (cycles.cyclesLeft > 0)
    {

        switch (fetchedInstruction)
        {
        case instructions.BRK:
            handle.BRK_HANDLER(cycles, memory);
            break;
        case instructions.ORA_IZX:
            handle.ORA_IZX_HANDLER(cycles, memory);
            break;
        case instructions.KIL_FIRST:
            handle.KIL_FIRST_HANDLER(cycles, memory);
            break;
        case instructions.SLO_IZX:
            handle.SLO_IZX_HANDLER(cycles, memory);
            break;
        case instructions.NOP_ZP:
            handle.NOP_ZP_HANDLER(cycles, memory);
            break;
        case instructions.ORA_ZP:
            handle.ORA_ZP_HANDLER(cycles, memory);
            break;
        case instructions.ASL_ZP:
            handle.ASL_ZP_HANDLER(cycles, memory);
            break;
        case instructions.SLO_ZP:
            handle.SLO_ZP_HANDLER(cycles, memory);
            break;
        case instructions.PHP:
            handle.PHP_HANDLER(cycles, memory);
            break;
        case instructions.ORA_IM:
            handle.ORA_IM_HANDLER(cycles, memory);
            break;
        case instructions.ASL:
            handle.ASL_HANDLER(cycles, memory);
            break;
        case instructions.ANC_IM:
            handle.ANC_IM_HANDLER(cycles, memory);
            break;
        case instructions.NOP_ABS:
            handle.NOP_ABS_HANDLER(cycles, memory);
            break;
        case instructions.ORA_ABS:
            handle.ORA_ABS_HANDLER(cycles, memory);
            break;
        case instructions.ASL_ABS:
            handle.ASL_ABS_HANDLER(cycles, memory);
            break;
        case instructions.SLO_ABS:
            handle.SLO_ABS_HANDLER(cycles, memory);
            break;
        case instructions.BPL_REL:
            handle.BPL_REL_HANDLER(cycles, memory);
            break;
        case instructions.ORA_IZY:
            handle.ORA_IZY_HANDLER(cycles, memory);
            break;
        case instructions.KIL_2:
            handle.KIL_2_HANDLER(cycles, memory);
            break;
        case instructions.SLO_IZY:
            handle.SLO_IZY_HANDLER(cycles, memory);
            break;
        case instructions.NOP_ZPX_1:
            handle.NOP_ZPX_HANDLER(cycles, memory);
            break;
        case instructions.ORA_ZPX:
            handle.ORA_ZPX_HANDLER(cycles, memory);
            break;
        case instructions.ASL_ZPX:
            handle.ASL_ZPX_HANDLER(cycles, memory);
            break;
        case instructions.NOP_2:
            handle.NOP_IMPLIED_HANDLER(cycles, memory);
            break;
        case instructions.SLO_ZPX:
            handle.SLO_ZPX_HANDLER(cycles, memory);
            break;
        case instructions.CLC:
            handle.CLC_HANDLER(cycles, memory);
            break;
        case instructions.ORA_ABSY:
            handle.ORA_ABSY_HANDLER(cycles, memory);
            break;
        case instructions.SLO_ABSY:
            handle.SLO_ABSY_HANDLER(cycles, memory);
            break;
        case instructions.NOP_ABX_1:
            handle.NOP_ABSX_HANDLER(cycles, memory);
            break;
        case instructions.ORA_ABSX:
            handle.ORA_ABSX_HANDLER(cycles, memory);
            break;
        case instructions.ASL_ABSX:
            handle.ASL_ABSX_HANDLER(cycles, memory);
            break;
        case instructions.SLO_ABSX:
            handle.SLO_ABSX_HANDLER(cycles, memory);
            break;
        case instructions.JSR_ABS:
            handle.JSR_ABS_HANDLER(cycles, memory);
            break;
        case instructions.AND_IZX:
            handle.AND_IZX_HANDLER(cycles, memory);
            break;
        case instructions.KIL_3:
            handle.KIL_3_HANDLER(cycles, memory);
            break;
        case instructions.RLA_IZX:
            handle.RLA_IZX_HANDLER(cycles, memory);
            break;
        case instructions.BIT_ZP:
            handle.BIT_ZP_HANDLER(cycles, memory);
            break;
        case instructions.AND_ZP:
            handle.AND_ZP_HANDLER(cycles, memory);
            break;
        case instructions.ROL_ZP:
            handle.ROL_ZP_HANDLER(cycles, memory);
            break;
        case instructions.RLA_ZP:
            handle.RLA_ZP_HANDLER(cycles, memory);
            break;
        case instructions.PLP:
            handle.PLP_HANDLER(cycles, memory);
            break;
        case instructions.AND_IM:
            handle.AND_IM_HANDLER(cycles, memory);
            break;
        case instructions.ROL:
            handle.ROL_HANDLER(cycles, memory);
            break;
        case instructions.ANC_IM_2:
            handle.ANC_IM_HANDLER(cycles, memory);
            break;
        case instructions.BIT_ABS:
            handle.BIT_ABS_HANDLER(cycles, memory);
            break;
        case instructions.AND_ABS:
            handle.AND_ABS_HANDLER(cycles, memory);
            break;
        case instructions.ROL_ABS:
            handle.ROL_ABS_HANDLER(cycles, memory);
            break;
        case instructions.RLA_ABS:
            handle.RLA_ABS_HANDLER(cycles, memory);
            break;
        case instructions.BMI_REL:
            handle.BMI_REL_HANDLER(cycles, memory);
            break;
        case instructions.AND_IZY:
            handle.AND_IZY_HANDLER(cycles, memory);
            break;
        case instructions.KIL_4:
            handle.KIL_4_HANDLER(cycles, memory);
            break;
        case instructions.RLA_IZY:
            handle.RLA_IZY_HANDLER(cycles, memory);
            break;
        case instructions.NOP_ZPX_2:
            handle.NOP_ZPX_HANDLER(cycles, memory);
            break;
        case instructions.AND_ZPX:
            handle.AND_ZPX_HANDLER(cycles, memory);
            break;
        case instructions.ROL_ZPX:
            handle.ROL_ZPX_HANDLER(cycles, memory);
            break;
        case instructions.RLA_ZPX:
            handle.RLA_ZPX_HANDLER(cycles, memory);
            break;
        case instructions.SEC:
            handle.SEC_HANDLER(cycles, memory);
            break;
        case instructions.AND_ABSY:
            handle.AND_ABSY_HANDLER(cycles, memory);
            break;
        case instructions.NOP_3:
            handle.NOP_IMPLIED_HANDLER(cycles, memory);
            break;
        case instructions.RLA_ABSY:
            handle.RLA_ABSY_HANDLER(cycles, memory);
            break;
        case instructions.NOP_ABX_2:
            handle.NOP_ABSX_HANDLER(cycles, memory);
            break;
        case instructions.AND_ABSX:
            handle.AND_ABSX_HANDLER(cycles, memory);
            break;
        case instructions.ROL_ABSX:
            handle.ROL_ABSX_HANDLER(cycles, memory);
            break;
        case instructions.RLA_ABSX:
            handle.RLA_ABSX_HANDLER(cycles, memory);
            break;
        case instructions.RTI:
            handle.RTI_HANDLER(cycles, memory);
            break;
        case instructions.EOR_IZX:
            handle.EOR_IZX_HANDLER(cycles, memory);
            break;
        case instructions.KIL_5:
            handle.KIL_5_HANDLER(cycles, memory);
            break;
        case instructions.SRE_IZX:
            handle.SRE_IZX_HANDLER(cycles, memory);
            break;
        case instructions.NOP_ZP_2:
            handle.NOP_ZP_HANDLER(cycles, memory);
            break;
        case instructions.EOR_ZP:
            handle.EOR_ZP_HANDLER(cycles, memory);
            break;
        case instructions.LSR_ZP:
            handle.LSR_ZP_HANDLER(cycles, memory);
            break;
        case instructions.SRE_ZP:
            handle.SRE_ZP_HANDLER(cycles, memory);
            break;
        case instructions.PHA:
            handle.PHA_HANDLER(cycles, memory);
            break;
        case instructions.EOR_IM:
            handle.EOR_IM_HANDLER(cycles, memory);
            break;
        case instructions.LSR:
            handle.LSR_HANDLER(cycles, memory);
            break;
        case instructions.ALR_IM:
            handle.ALR_IM_HANDLER(cycles, memory);
            break;
        case instructions.JMP_ABS:
            handle.JMP_ABS_HANDLER(cycles, memory);
            break;
        case instructions.EOR_ABS:
            handle.EOR_ABS_HANDLER(cycles, memory);
            break;
        case instructions.LSR_ABS:
            handle.LSR_ABS_HANDLER(cycles, memory);
            break;
        case instructions.SRE_ABS:
            handle.SRE_ABS_HANDLER(cycles, memory);
            break;
        case instructions.BVC_REL:
            handle.BVC_REL_HANDLER(cycles, memory);
            break;
        case instructions.EOR_IZY:
            handle.EOR_IZY_HANDLER(cycles, memory);
            break;
        default:
        {
            printf("Instruction not recognized %d: ", fetchedInstruction);
            break;
        };
        };
    };
};

void CPU6502::Handlers::BRK_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502 cpu;
    CPU6502::Memory mem;
    CPU6502::ProcessorState processor;

    processor.BREAK_COMMAND = true;

    cpu.pushStack(static_cast<BYTE>((cpu.processor.PC >> 8) & 0xFF));
    cpu.pushStack(static_cast<BYTE>(cpu.processor.PC & 0xFF));

    BYTE status = 0;
    status |= (processor.CARRY_FLAG << 0);
    status |= (processor.ZERO_FLAG << 1);
    status |= (processor.INTERRUPT_DISABLE << 2);
    status |= (processor.DECIMAL_MODE << 3);
    status |= (processor.BREAK_COMMAND << 4);
    status |= (processor.OVERFLOW_FLAG << 6);
    status |= (processor.NEGATIVE_FLAG << 7);

    cpu.pushStack(status);

    processor.PC = mem.readMemory(0xFFFE) | (mem.readMemory(0xFFFF) << 8);

    processor.PC++;

    std::cout << "Interrupt triggered, new PC: 0x"
              << std::hex << static_cast<int>(processor.PC) << std::endl;

    cycles.consume(7);
}

void CPU6502::Handlers::ORA_IZX_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::ProcessorState processor;
    CPU6502 cpu;

    BYTE value = cpu.fetch(cycles, memory);
    processor.A |= value;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(6); // Consome os ciclos
    std::cout << "ORA (Indexed, X)" << std::endl;
}

void CPU6502::Handlers::KIL_FIRST_HANDLER(Cycles &cycles, Memory &memory)
{
    system("pause");
}

void CPU6502::Handlers::SLO_IZX_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::ProcessorState processor;
    CPU6502::Cycles cyclesStruct;
    CPU6502::Memory memoryStruct;
    CPU6502 cpu;

    BYTE value = cpu.fetch(cycles, memoryStruct);
    processor.A |= value;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(8);

    std::cout << "SLO (Indexed, X)" << std::endl;
}

void CPU6502::Handlers::NOP_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    CPU6502::Memory memoryStruct;
    CPU6502 cpu;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    BYTE address = cpu.fetch(cycles, memory);
    BYTE value = memoryStruct.readMemory(address);
    cycles.consume(3);

    std::cout << "NOP (Zero Page) executed at address: 0x"
              << std::hex << static_cast<int>(address) << std::endl;
}
void CPU6502::Handlers::ORA_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    CPU6502::ProcessorState processor;
    CPU6502 cpu;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    BYTE value = cpu.fetch(cycles, memory);
    processor.A |= value;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(3);

    std::cout << "ORA (Zero Page)" << std::endl;
}
void CPU6502::Handlers::ASL_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    CPU6502::ProcessorState processor;

    CPU6502 cpu;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    BYTE value = cpu.fetch(cycles, memory);
    BYTE result = value << 1;
    processor.ZERO_FLAG = (result == 0);
    processor.NEGATIVE_FLAG = (result & 0x80) > 0;
    cycles.consume(5);

    std::cout << "ASL (Zero Page)" << std::endl;
}
void CPU6502::Handlers::SLO_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);
    BYTE result = value << 1;
    processor.A |= result;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(5);

    std::cout << "SLO (Zero Page)" << std::endl;
}

void CPU6502::Handlers::PHP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "PHP (Push Processor Status)" << std::endl;
    CPU6502::ProcessorState processor;
    CPU6502 cpu;

    BYTE status = (processor.CARRY_FLAG << 0) |
                  (processor.ZERO_FLAG << 1) |
                  (processor.INTERRUPT_DISABLE << 2) |
                  (processor.DECIMAL_MODE << 3) |
                  (1 << 4) |
                  (processor.OVERFLOW_FLAG << 6) |
                  (processor.NEGATIVE_FLAG << 7);

    cpu.pushStack(status);
    cycles.consume(3);
}
void CPU6502::Handlers::ORA_IM_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);

    processor.A |= value;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    processor.PC += 2;

    cycles.consume(2); // A instrução ORA (imediata) consome 2 ciclos

    std::cout << "ORA (Immediate)" << std::endl;
}

void CPU6502::Handlers::ASL_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::ProcessorState processor;

    processor.A <<= 1;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(2);
    processor.PC += 1;
    std::cout << "ASL (Accumulator)" << std::endl;
}

void CPU6502::Handlers::ANC_IM_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);

    processor.A &= value;
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    processor.ZERO_FLAG = (processor.A == 0);
    cycles.consume(2);

    std::cout << "ANC (Immediate)" << std::endl;
}

void CPU6502::Handlers::ORA_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);
    processor.A |= value;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    processor.PC += 2;

    std::cout << "ORA (Absolute)" << std::endl;

    cycles.consume(4);
}
void CPU6502::Handlers::ASL_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);
    BYTE result = value << 1;
    processor.ZERO_FLAG = (result == 0);
    processor.NEGATIVE_FLAG = (result & 0x80) > 0;
    std::cout << "ASL (Absolute)" << std::endl;
    cycles.consume(6);
}

void CPU6502::Handlers::SLO_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);
    BYTE result = value << 1;
    processor.A |= result;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(6);
    std::cout << "SLO (Absolute)" << std::endl;
}

void CPU6502::Handlers::BPL_REL_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "BPL (Branch if Positive)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE offset = cpu.fetch(cycles, memory);

    if (!processor.NEGATIVE_FLAG)
    {
        processor.PC += static_cast<BYTE>(offset);
    }

    processor.PC += 1;
    cycles.consume(2);
}

void CPU6502::Handlers::ORA_IZY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ORA (Indexed Indirect, Y)" << std::endl;

    CPU6502::Memory memoryStruct;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.Y;

    BYTE value = memoryStruct.readMemory(address);
    processor.A |= value;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(5);
}

void CPU6502::Handlers::KIL_2_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "KIL (Illegal Operation)" << std::endl;
    system("pause");
}

void CPU6502::Handlers::SLO_IZY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "SLO (Indexed Indirect, Y)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    CPU6502::Memory memoryStruct;

    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.Y;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value << 1;

    processor.A |= result;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(8);
}

void CPU6502::Handlers::NOP_ZPX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "NOP (Zero Page, X)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);
    address += processor.X;

    cycles.consume(4);
}

void CPU6502::Handlers::ORA_ZPX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ORA (Zero Page, X)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    CPU6502::Memory memoryStruct;

    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);
    address += processor.X;

    BYTE value = memoryStruct.readMemory(address);
    processor.A |= value;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(4);
}

void CPU6502::Handlers::ASL_ZPX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ASL (Zero Page, X)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    CPU6502::Memory memoryStruct;

    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);
    address += processor.X;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value << 1;

    processor.ZERO_FLAG = (result == 0);
    processor.NEGATIVE_FLAG = (result & 0x80) > 0;
    cycles.consume(6);
}

void CPU6502::Handlers::NOP_IMPLIED_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "NOP (Implied)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);
    cycles.consume(2);
}

void CPU6502::Handlers::SLO_ZPX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "SLO (Zero Page, X)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;

    CPU6502::Memory memoryStruct;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);
    address += processor.X;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value << 1;

    processor.A |= result;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(6);
}

void CPU6502::Handlers::CLC_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "CLC (Clear Carry Flag)" << std::endl;
    CPU6502::ProcessorState processor;

    processor.CARRY_FLAG = 0;
    cycles.consume(2);
}

void CPU6502::Handlers::ORA_ABSY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ORA (Absolute, Y)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    CPU6502::Memory memoryStruct;

    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.Y;

    BYTE value = memoryStruct.readMemory(address);
    processor.A |= value;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(4);
}

void CPU6502::Handlers::SLO_ABSY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "SLO (Absolute, Y-indexed)" << std::endl;

    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.Y;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value << 1;

    processor.A |= result;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(7);
}

void CPU6502::Handlers::NOP_ABSX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "NOP (Absolute, X-indexed)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    cycles.consume(4);
}

void CPU6502::Handlers::NOP_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "NOP (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);

    WORD address = (highByte << 8) | lowByte;

    cycles.consume(4);
}

void CPU6502::Handlers::ORA_ABSX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ORA (Absolute, X-indexed)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    processor.A |= value;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(4);
}

void CPU6502::Handlers::ASL_ABSX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ASL (Absolute, X-indexed)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value << 1;

    processor.ZERO_FLAG = (result == 0);
    processor.NEGATIVE_FLAG = (result & 0x80) > 0;

    cycles.consume(7);
}

void CPU6502::Handlers::SLO_ABSX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "SLO (Absolute, X-indexed)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value << 1;

    processor.A |= result;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(7);
}

void CPU6502::Handlers::JSR_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "JSR (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;

    cpu.pushStack(static_cast<BYTE>((processor.PC + 2) >> 8));
    cpu.pushStack(static_cast<BYTE>((processor.PC + 2) & 0xFF));

    processor.PC = address;

    cycles.consume(6);
}

void CPU6502::Handlers::AND_IZX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "AND (Indexed, X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);
    WORD address = (value + processor.X) & 0xFF;

    CPU6502::Memory memoryStruct;

    processor.A &= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(6);
}

void CPU6502::Handlers::KIL_3_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "KIL (Illegal Operation)" << std::endl;
    system("pause");
}

void CPU6502::Handlers::RLA_IZX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "RLA (Indexed, X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);
    WORD address = (value + processor.X) & 0xFF;

    CPU6502::Memory memoryStruct;

    BYTE readValue = memoryStruct.readMemory(address);
    BYTE result = (readValue << 1) | (processor.CARRY_FLAG ? 1 : 0);

    processor.A &= result;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(8);
}

void CPU6502::Handlers::BIT_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "BIT (Zero Page)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = processor.A & value;

    processor.ZERO_FLAG = (result == 0);
    processor.NEGATIVE_FLAG = (value & 0x80) > 0;
    processor.OVERFLOW_FLAG = (value & 0x40) > 0;

    cycles.consume(3);
}

void CPU6502::Handlers::AND_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "AND (Zero Page)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);

    CPU6502::Memory memoryStruct;

    processor.A &= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(3);
}

void CPU6502::Handlers::ROL_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ROL (Zero Page)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    memoryStruct.writeOperator(address, result);

    processor.CARRY_FLAG = (value & 0x80) > 0;
    processor.NEGATIVE_FLAG = (result & 0x80) > 0;

    cycles.consume(5);
}

void CPU6502::Handlers::RLA_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "RLA (Zero Page)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    processor.A &= result;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(5);
}

void CPU6502::Handlers::PLP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "PLP (Pull Processor Status)" << std::endl;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE status = cpu.popStack();

    processor.CARRY_FLAG = status & 0x01;
    processor.ZERO_FLAG = (status >> 1) & 0x01;
    processor.INTERRUPT_DISABLE = (status >> 2) & 0x01;
    processor.DECIMAL_MODE = (status >> 3) & 0x01;
    processor.BREAK_COMMAND = (status >> 4) & 0x01;
    processor.OVERFLOW_FLAG = (status >> 6) & 0x01;
    processor.NEGATIVE_FLAG = (status >> 7) & 0x01;

    cycles.consume(4);
}

void CPU6502::Handlers::AND_IM_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "AND (Immediate)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);

    processor.A &= value;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(2);
}

void CPU6502::Handlers::ROL_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ROL (Accumulator)" << std::endl;

    CPU6502 cpu;
    CPU6502::ProcessorState &processor = cpu.processor;

    U32 actualCycles = cycles.cyclesLeft;
    cpu.fetch(cycles, memory);

    BYTE result = (processor.A << 1) | (processor.CARRY_FLAG ? 1 : 0);

    processor.A = result;
    processor.CARRY_FLAG = (processor.A & 0x80) > 0;
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(2);
}

void CPU6502::Handlers::BIT_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "BIT (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = processor.A & value;

    processor.ZERO_FLAG = (result == 0);
    processor.NEGATIVE_FLAG = (value & 0x80) > 0;
    processor.OVERFLOW_FLAG = (value & 0x40) > 0;

    cycles.consume(4);
}

void CPU6502::Handlers::AND_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "AND (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;

    CPU6502::Memory memoryStruct;

    processor.A &= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(4);
}

void CPU6502::Handlers::ROL_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ROL (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    memoryStruct.writeOperator(address, result);

    processor.CARRY_FLAG = (value & 0x80) > 0;
    processor.NEGATIVE_FLAG = (result & 0x80) > 0;

    cycles.consume(6);
}

void CPU6502::Handlers::RLA_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "RLA (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    processor.A &= result;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(6);
}

void CPU6502::Handlers::BMI_REL_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "BMI (Relative)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE offset = cpu.fetch(cycles, memory);

    if (processor.NEGATIVE_FLAG)
    {

        processor.PC += static_cast<signed char>(offset);
    }

    cycles.consume(2);
}

void CPU6502::Handlers::AND_IZY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "AND (Indexed, Y)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);
    WORD address = (value + processor.Y) & 0xFF;

    CPU6502::Memory memoryStruct;

    processor.A &= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(5);
}

void CPU6502::Handlers::KIL_4_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "KIL (Illegal Operation)" << std::endl;
}

void CPU6502::Handlers::RLA_IZY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "RLA (Indexed, Y)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE value = cpu.fetch(cycles, memory);
    WORD address = (value + processor.Y) & 0xFF;

    CPU6502::Memory memoryStruct;

    BYTE readValue = memoryStruct.readMemory(address);
    BYTE result = (readValue << 1) | (processor.CARRY_FLAG ? 1 : 0);

    processor.A &= result;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(8);
}

void CPU6502::Handlers::AND_ZPX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "AND (Zero Page, Indexed by X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);
    address = (address + processor.X) & 0xFF;

    CPU6502::Memory memoryStruct;

    processor.A &= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(4);
}

void CPU6502::Handlers::ROL_ZPX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ROL (Zero Page, Indexed by X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);
    address = (address + processor.X) & 0xFF;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    memoryStruct.writeOperator(address, result);

    processor.CARRY_FLAG = (value & 0x80) > 0;
    processor.NEGATIVE_FLAG = (result & 0x80) > 0;

    cycles.consume(6);
}

void CPU6502::Handlers::RLA_ZPX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "RLA (Zero Page, Indexed by X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);
    address = (address + processor.X) & 0xFF;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    processor.A &= result;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(6);
}

void CPU6502::Handlers::SEC_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "SEC (Set Carry Flag)" << std::endl;

    CPU6502::ProcessorState processor;

    processor.CARRY_FLAG = true;

    cycles.consume(2);
}

void CPU6502::Handlers::AND_ABSY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "AND (Absolute, Indexed by Y)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.Y;

    CPU6502::Memory memoryStruct;

    processor.A &= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(4);
}

void CPU6502::Handlers::NOP_3_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "NOP (No Operation)" << std::endl;
}

void CPU6502::Handlers::RLA_ABSY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "RLA (Absolute, Indexed by Y)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.Y;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    processor.A &= result;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(7);
}

void CPU6502::Handlers::NOP_ABX_2_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "NOP (Absolute, Indexed by X)" << std::endl;
    cycles.consume(4);
}
void CPU6502::Handlers::AND_ABSX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "AND (Absolute, Indexed by X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    CPU6502::Memory memoryStruct;

    processor.A &= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(4);
}
void CPU6502::Handlers::ROL_ABSX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ROL (Absolute, Indexed by X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    memoryStruct.writeOperator(address, result);

    processor.CARRY_FLAG = (value & 0x80) > 0;
    processor.NEGATIVE_FLAG = (result & 0x80) > 0;

    cycles.consume(7);
}

void CPU6502::Handlers::RLA_ABSX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "RLA (Absolute, Indexed by X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = (value << 1) | (processor.CARRY_FLAG ? 1 : 0);

    processor.A &= result;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(7);
}
void CPU6502::Handlers::RTI_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "RTI (Return from Interrupt)" << std::endl;

    CPU6502::ProcessorState processor;
    CPU6502 cpu;

    processor.STATUS = cpu.popStack();
    WORD address = cpu.popStack() | (cpu.popStack() << 8);
    processor.PC = address;

    cycles.consume(6);
}
void CPU6502::Handlers::EOR_IZX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "EOR (Indexed Indirect X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    CPU6502::Memory memoryStruct;

    processor.A ^= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(6);
}
void CPU6502::Handlers::KIL_5_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "Illegal Opcode (KIL_5)" << std::endl;

    system("pause");
}
void CPU6502::Handlers::SRE_IZX_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "SRE (Indexed Indirect X)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD address = (highByte << 8) | lowByte;
    address += processor.X;

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value >> 1;

    processor.A ^= result;

    processor.CARRY_FLAG = (value & 0x01) > 0;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(8);
}
void CPU6502::Handlers::NOP_ZP_2_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "NOP (Zero Page)" << std::endl;
}
void CPU6502::Handlers::EOR_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "EOR (Zero Page)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);

    CPU6502::Memory memoryStruct;

    processor.A ^= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(3);
}
void CPU6502::Handlers::LSR_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "LSR (Zero Page)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value >> 1;

    memoryStruct.writeOperator(address, result);

    processor.CARRY_FLAG = (value & 0x01) > 0;
    processor.ZERO_FLAG = (result == 0);
    processor.NEGATIVE_FLAG = false;

    cycles.consume(5);
}
void CPU6502::Handlers::SRE_ZP_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "SRE (Zero Page)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE address = cpu.fetch(cycles, memory);

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value >> 1;

    processor.A ^= result;

    processor.CARRY_FLAG = (value & 0x01) > 0;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(5);
}
void CPU6502::Handlers::PHA_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "PHA (Push Accumulator)" << std::endl;
    CPU6502::ProcessorState processor;
    CPU6502 cpu;

    cpu.pushStack(processor.A);
    cycles.consume(3);
}
void CPU6502::Handlers::EOR_IM_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "EOR (Immediate)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    processor.A ^= cpu.fetch(cycles, memory);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(2);
}
void CPU6502::Handlers::LSR_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "LSR (Accumulator)" << std::endl;
    CPU6502::ProcessorState processor;

    processor.CARRY_FLAG = (processor.A & 0x01) > 0;
    processor.A >>= 1;

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = false;
}
void CPU6502::Handlers::ALR_IM_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "ALR (Immediate)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    CPU6502::ProcessorState processor;
    CPU6502 cpu;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    processor.CARRY_FLAG = (processor.A & 0x01) > 0;
    processor.A = (processor.A >> 1) & cpu.fetch(cycles, memory);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
}

void CPU6502::Handlers::JMP_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "JMP (Absolute)" << std::endl;

    CPU6502::ProcessorState processor;

    WORD address = memory.fetchWord(processor.PC);

    processor.PC = address;

    cycles.consume(3);
}

void CPU6502::Handlers::EOR_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "EOR (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    CPU6502::ProcessorState processor;
    CPU6502::Memory memoryStruct;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    WORD address = memory.fetchWord(processor.PC);
    processor.A ^= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(4);
}

void CPU6502::Handlers::LSR_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "LSR (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    CPU6502::Memory memoryStruct;
    CPU6502::ProcessorState processor;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    WORD address = memoryStruct.fetchWord(processor.PC);

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value >> 1;

    memoryStruct.writeOperator(address, result);

    processor.CARRY_FLAG = (value & 0x01) > 0;
    processor.ZERO_FLAG = (result == 0);
    processor.NEGATIVE_FLAG = false;

    cycles.consume(6);
}

void CPU6502::Handlers::SRE_ABS_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "SRE (Absolute)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    CPU6502::ProcessorState processor;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    WORD address = memory.fetchWord(processor.PC);

    CPU6502::Memory memoryStruct;

    BYTE value = memoryStruct.readMemory(address);
    BYTE result = value >> 1;

    processor.A ^= result;

    processor.CARRY_FLAG = (value & 0x01) > 0;
    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;
    cycles.consume(6);
}

void CPU6502::Handlers::BVC_REL_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "BVC (Branch if Overflow Clear)" << std::endl;
    CPU6502::ProcessorState processor;
    CPU6502::Cycles cyclesStruct;
    CPU6502::Memory memoryStruct;
    CPU6502 cpu;

    U32 actualCycles = cyclesStruct.cyclesLeft;

    if (!processor.OVERFLOW_FLAG)
    {
        BYTE fetchedByte = cpu.fetch(cycles, memoryStruct);

        processor.PC = (processor.PC + (signed char)fetchedByte);
    }

    cycles.consume(2);
}

void CPU6502::Handlers::EOR_IZY_HANDLER(Cycles &cycles, Memory &memory)
{
    std::cout << "EOR (Indexed Indirect Y)" << std::endl;
    CPU6502::Cycles cyclesStruct;
    U32 actualCycles = cyclesStruct.cyclesLeft;
    CPU6502 cpu;
    CPU6502::ProcessorState processor;

    BYTE lowByte = cpu.fetch(cycles, memory);
    BYTE highByte = cpu.fetch(cycles, memory);
    WORD baseAddress = (highByte << 8) | lowByte;
    WORD address = baseAddress + processor.Y;

    CPU6502::Memory memoryStruct;

    processor.A ^= memoryStruct.readMemory(address);

    processor.ZERO_FLAG = (processor.A == 0);
    processor.NEGATIVE_FLAG = (processor.A & 0x80) > 0;

    cycles.consume(5);
}

void CPU6502::Handlers::KIL_6_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SRE_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_ZPX_3_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::EOR_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LSR_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SRE_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CLI_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::EOR_ABSY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_4_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SRE_ABSY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_ABX_3_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::EOR_ABSX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LSR_ABSX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SRE_ABSX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::RTS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ADC_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::KIL_7_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::RRA_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_ZP_3_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ADC_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ROR_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::RRA_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::PLA_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ADC_IM_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ROR_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ARR_IM_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::JMP_IND_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ADC_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ROR_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::RRA_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::BVS_REL_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ADC_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::KIL_8_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::RRA_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_ZPX_4_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ADC_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ROR_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::RRA_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SEI_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ADC_ABSY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_5_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::RRA_ABSY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_ABX_4_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ADC_ABSX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ROR_ABSX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::RRA_ABSX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STA_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_IMM_2_ALT_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SAX_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STY_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STA_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STX_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SAX_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DEY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_IMM_2_ALT2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::TXA_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::XAA_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STY_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STA_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STX_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SAX_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::BCC_REL_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STA_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::KIL_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::AHX_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STY_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STA_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STX_ZPY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SAX_ZPY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::TYA_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STA_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::TXS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::TAS_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SHY_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::STA_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SHX_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::AHX_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDY_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDA_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDX_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LAX_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDY_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDA_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDX_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LAX_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::TAY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDA_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::TAX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LAX_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDY_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDA_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDX_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LAX_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::BCS_REL_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDA_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::KIL_B_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LAX_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDY_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDA_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDX_ZPY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LAX_ZPY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CLV_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDA_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::TSX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LAS_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDY_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDA_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LDX_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::LAX_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CPY_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CMP_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_IMM_2_C2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DCP_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CPY_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CMP_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DEC_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DCP_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::INY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CMP_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DEX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::AXS_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CPY_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CMP_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DEC_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DCP_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::BNE_REL_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CMP_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::KIL_D_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DCP_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CMP_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DEC_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DCP_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CLD_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CMP_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_DA_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DCP_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CMP_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DEC_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::DCP_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CPX_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_IMM_2_E2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ISC_IZX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CPX_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::INC_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ISC_ZP_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::INX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_IMM_2_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_EA_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_IMM_2_ALT_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::CPX_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::INC_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ISC_ABS_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::BEQ_REL_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::KIL_F_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ISC_IZY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_ZPX_F4_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::INC_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ISC_ZPX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SED_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_ABY_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_FA_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_ABY_ALT_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::NOP_ABX_FC_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::SBC_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::INC_ABX_HANDLER(Cycles &cycles, Memory &memory) {}
void CPU6502::Handlers::ISC_ABX_HANDLER(Cycles &cycles, Memory &memory) {}