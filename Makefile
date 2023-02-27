CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDES = -I./gfx/bgfx/include/bgfx/ -I./gfx/bimg/include/ -I./gfx/bx/include/bx/ -I./gfx/bx/include/tinystl/ -I./gfx/bx/include/compat/linux/
LINKING = ./gfx/bgfx/.build/linux64_gcc/bin/*.a

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = HeatSim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $^ $(LINKING) -o $@

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
