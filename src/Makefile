CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall

SRC_DIR = solutions
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
EXECUTABLES = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.exe,$(SOURCES))

all: $(EXECUTABLES)

$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean