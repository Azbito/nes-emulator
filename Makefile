CXX = g++
CXXFLAGS = -std=c++17 -I./src
LDFLAGS = -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi
SRC_DIR = ./src
TARGET = emulator.exe

SOURCES := $(wildcard $(SRC_DIR)/**/*.cpp) main.cpp
OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
