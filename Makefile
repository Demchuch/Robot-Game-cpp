CXX ?= g++
CXXFLAGS := -std=c++20 -Wall -Wextra -MMD -MP

ifeq ($(OS),Windows_NT)
EXE := .exe
CLEAN = del /Q /S *.o *.d $(TARGET) 2>nul
else
EXE :=
CLEAN = rm -f $(OBJ) $(DEP) $(TARGET)
endif

TARGET := game$(EXE)
SRC := main.cpp $(wildcard robot/*.cpp cell/*.cpp gamefield/*.cpp movement/*.cpp gameloop/*.cpp visualizer/*.cpp robotfactory/*.cpp enemycontroller/*.cpp)
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(CLEAN)

-include $(DEP)

.PHONY: clean