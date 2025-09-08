#pragma once

#include <windows.h>
#include <vector>
#include <string>
#include <thread>
#include "CPU/CPU6502.h"
#include "JIT/Compiler.h"
#include "Bus/Bus.h"
#include "PPU/PPU.h"

class GameWindow {
public:
    GameWindow(PPU* ppu_, CPU6502* cpu_, JITCompiler* jit_, Bus* bus_)
        : ppu(ppu_), cpu(cpu_), jit(jit_), bus(bus_),
          isPaused(true), isStepping(false)
    {
        screenWidth = 256;
        screenHeight = 240;
        framebuffer.resize(screenWidth * screenHeight, 0x00000000);
    }

    struct Pixel {
        uint8_t r, g, b, a;
    };

    [[nodiscard]]
    bool Create() {
        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProcStatic;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = "NESWindowClass";
        wc.cbWndExtra = sizeof(GameWindow*);

        if (!RegisterClass(&wc)) return false;

        hwnd = CreateWindowEx(
            0, "NESWindowClass", "NES Emulator",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, screenWidth*2, screenHeight*2,
            nullptr, nullptr, GetModuleHandle(nullptr), this
        );

        return hwnd != nullptr;
    }

    void Run() {
        MSG msg = {};
        while (true) {
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) return;
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            HandleInput();
            RunEmulationFrame();
            DrawScreen();

            std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60fps
        }
    }

private:
    HWND hwnd = nullptr;
    PPU* ppu;
    CPU6502* cpu;
    JITCompiler* jit;
    Bus* bus;

    int screenWidth;
    int screenHeight;
    std::vector<uint32_t> framebuffer;

    bool isPaused;
    bool isStepping;

    // --- Static WindowProc ---
    static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg == WM_CREATE) {
            CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
            return 0;
        }

        GameWindow* window = reinterpret_cast<GameWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if (window) return window->WindowProc(hwnd, uMsg, wParam, lParam);

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            BITMAPINFO bmi = {};
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = screenWidth;
            bmi.bmiHeader.biHeight = -screenHeight; // top-down
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;

            StretchDIBits(hdc,
                          0, 0, screenWidth, screenHeight,
                          0, 0, screenWidth, screenHeight,
                          framebuffer.data(), &bmi, DIB_RGB_COLORS, SRCCOPY);

            EndPaint(hwnd, &ps);
            return 0;
        }
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void HandleInput() {
        if (GetAsyncKeyState('P') & 0x8000) isPaused = !isPaused;
        if (GetAsyncKeyState('S') & 0x8000 && isPaused) isStepping = true;
    }

    void RunSingleInstruction() {
        if (cpu->getCycles() == 0) cpu->step(*jit);
        do {
            if (cpu->getCycles() == 0) cpu->step(*jit);
            cpu->clock(*jit);
        } while (cpu->getCycles() > 0);
    }

    void RunEmulationFrame() {
        if (isPaused && !isStepping) return;
        printf("oi");
        cpu->step(*jit);
        cpu->clock(*jit);

        if (isStepping) isStepping = false;
    }

    void DrawScreen() {
        if (!ppu) return;

        std::fill(framebuffer.begin(), framebuffer.end(), 0x00000000);
        ppu->renderNametableToBuffer(framebuffer.data(), screenWidth, screenHeight);
        ppu->renderSprites(framebuffer.data(), screenWidth, screenHeight);

        InvalidateRect(hwnd, nullptr, FALSE);
    }
};
