CXX = g++
CXXFLAGS = -std=c++11 -Wall -L./gfx/bgfx/.build/bin/ -l*.a

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = HeatSim.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
