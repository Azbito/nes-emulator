#include <windows.h>
#include "CPU6502.h"

using namespace std;

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
int main()
{
    CPU6502 cpu;
    CPU6502::Memory memory;

    cpu.reset(memory);

    //! fake program
    memory.writeOperator(0xFFFC, 0xA9);
    memory.writeOperator(0xFFFD, 0xA2);
    //!

    // cpu.execute(2, memory);

    system("pause");

    return 0;
}
