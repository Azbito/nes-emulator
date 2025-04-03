CXX = g++
CXXFLAGS = -std=c++17 -I./src
LDFLAGS = -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs
SRC_DIR = ./src
TARGET = emulator.exe

SOURCES = main.cpp $(SRC_DIR)/Screen/Renderer.cpp $(SRC_DIR)/ROM/PPU.cpp $(SRC_DIR)/ROM/Loader.cpp $(SRC_DIR)/ROM/Colours.cpp \
          $(SRC_DIR)/JIT/Compiler.cpp $(SRC_DIR)/CPU/CPU6502.cpp $(SRC_DIR)/Assembly/Addressing.cpp $(SRC_DIR)/Assembly/Instructions.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
