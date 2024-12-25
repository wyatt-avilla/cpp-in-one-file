# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17

# Target executable
TARGET = library

# Source files
SRC = library-assignment.cpp

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean rule to remove generated files
clean:
	rm -f $(TARGET)

.PHONY: all clean
