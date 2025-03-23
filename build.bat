@echo off
setlocal enabledelayedexpansion

set MSYS64=C:/msys64/ucrt64
set NES_EMU=D:/nes-emulator

set COMPILER="%MSYS64%/bin/g++.exe"
set CXXFLAGS=-fdiagnostics-color=always -v -g -std=c++17
set INCLUDES=-I "%NES_EMU%/src" -I "%MSYS64%/include"
set LIBS=-L "%MSYS64%/lib" -lgdi32 -luser32 -lopengl32 -lgdiplus -lshlwapi -ldwmapi -lstdc++fs

set SRC_FILES=^
    "%NES_EMU%/main.cpp" ^
    "%NES_EMU%/src/CPU/CPU6502.cpp" ^
    "%NES_EMU%/src/Assembly/Instructions.cpp" ^
    "%NES_EMU%/src/JIT/Compiler.cpp" ^
    "%NES_EMU%/src/Screen/Renderer.cpp" ^
    "%NES_EMU%/src/ROM/PPU.cpp" ^
    "%NES_EMU%/src/ROM/Colours.cpp" ^
    "%NES_EMU%/src/ROM/Loader.cpp" ^
    "%NES_EMU%/src/Assembly/Addressing.cpp"

set OUTPUT="%NES_EMU%/main.exe"

%COMPILER% %CXXFLAGS% %SRC_FILES% %INCLUDES% %LIBS% -o %OUTPUT%
