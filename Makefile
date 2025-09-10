# Makefile for Traffic Management System - Organized Structure
# Usage: make (compile), make clean (remove compiled files), make run (compile and run)

# Compiler and flags - Updated to C++17 for modern features and better support
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -O2 -Iinclude
TARGET = traffic_management

# Directory structure
SRCDIR = src
INCDIR = include
INPUTDIR = input

# Source and header files
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/display.cpp $(SRCDIR)/data_structures.cpp $(SRCDIR)/thread_pool.cpp $(SRCDIR)/traffic_validator.cpp $(SRCDIR)/traffic_network.cpp
OBJECTS = $(SRCDIR)/main.o $(SRCDIR)/display.o $(SRCDIR)/data_structures.o $(SRCDIR)/thread_pool.o $(SRCDIR)/traffic_validator.o $(SRCDIR)/traffic_network.o
HEADERS = $(INCDIR)/types.h $(INCDIR)/display.h $(INCDIR)/data_structures.h $(INCDIR)/thread_pool.h $(INCDIR)/traffic_validator.h $(INCDIR)/traffic_network.h

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build complete! Executable: $(TARGET)"

# Compile source files to object files
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program with default input
run: $(TARGET)
	@echo "Running $(TARGET) with default input..."
	./$(TARGET) $(INPUTDIR)/traffic_input.txt

# Run without input file (uses sample network)
run-no-input: $(TARGET)
	@echo "Running $(TARGET) without input file..."
	./$(TARGET)

# Clean compiled files
clean:
	@echo "Cleaning up..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete!"

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Release build with maximum optimization
release: CXXFLAGS += -O3 -DNDEBUG
release: $(TARGET)

# Create necessary directories
setup-dirs:
	@echo "Creating project directories..."
	mkdir -p $(SRCDIR) $(INCDIR) $(INPUTDIR)
	@echo "Directories created!"

# Create a sample input file
sample-input:
	@echo "Creating sample traffic_input.txt in $(INPUTDIR)/..."
	@mkdir -p $(INPUTDIR)
	@echo "4" > $(INPUTDIR)/traffic_input.txt
	@echo "0 1 1 0" >> $(INPUTDIR)/traffic_input.txt
	@echo "0 0 1 1" >> $(INPUTDIR)/traffic_input.txt
	@echo "0 0 0 1" >> $(INPUTDIR)/traffic_input.txt
	@echo "1 0 0 0" >> $(INPUTDIR)/traffic_input.txt
	@echo "" >> $(INPUTDIR)/traffic_input.txt
	@echo "# Node Capacities" >> $(INPUTDIR)/traffic_input.txt
	@echo "A:5" >> $(INPUTDIR)/traffic_input.txt
	@echo "B:3" >> $(INPUTDIR)/traffic_input.txt
	@echo "C:4" >> $(INPUTDIR)/traffic_input.txt
	@echo "D:6" >> $(INPUTDIR)/traffic_input.txt
	@echo "" >> $(INPUTDIR)/traffic_input.txt
	@echo "# Traffic Controller Nodes" >> $(INPUTDIR)/traffic_input.txt
	@echo "A,C" >> $(INPUTDIR)/traffic_input.txt
	@echo "" >> $(INPUTDIR)/traffic_input.txt
	@echo "# Initial Traffic Allocation" >> $(INPUTDIR)/traffic_input.txt
	@echo "A:2" >> $(INPUTDIR)/traffic_input.txt
	@echo "B:1" >> $(INPUTDIR)/traffic_input.txt
	@echo "C:2" >> $(INPUTDIR)/traffic_input.txt
	@echo "D:1" >> $(INPUTDIR)/traffic_input.txt
	@echo "" >> $(INPUTDIR)/traffic_input.txt
	@echo "# Ambulances" >> $(INPUTDIR)/traffic_input.txt
	@echo "B:1" >> $(INPUTDIR)/traffic_input.txt
	@echo "" >> $(INPUTDIR)/traffic_input.txt
	@echo "# Fire Trucks" >> $(INPUTDIR)/traffic_input.txt
	@echo "D:1" >> $(INPUTDIR)/traffic_input.txt
	@echo "" >> $(INPUTDIR)/traffic_input.txt
	@echo "# Destination Nodes" >> $(INPUTDIR)/traffic_input.txt
	@echo "A:D" >> $(INPUTDIR)/traffic_input.txt
	@echo "B:C" >> $(INPUTDIR)/traffic_input.txt
	@echo "C:A" >> $(INPUTDIR)/traffic_input.txt
	@echo "D:B" >> $(INPUTDIR)/traffic_input.txt
	@echo "Sample input file created: $(INPUTDIR)/traffic_input.txt"

# Performance build with profiling info
profile: CXXFLAGS += -pg -O2
profile: $(TARGET)

# Static analysis (requires additional tools)
analyze:
	@echo "Running static analysis..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c++17 $(SOURCES); \
	else \
		echo "cppcheck not found. Install it for static analysis."; \
	fi

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build the project (default)"
	@echo "  run              - Build and run with default input file"
	@echo "  run-no-input     - Build and run without input file"
	@echo "  debug            - Build with debug symbols (-g -DDEBUG)"
	@echo "  release          - Build with maximum optimization (-O3)"
	@echo "  profile          - Build with profiling support (-pg)"
	@echo "  setup-dirs       - Create project directory structure"
	@echo "  sample-input     - Create a sample input file"
	@echo "  clean            - Remove compiled files"
	@echo "  check-structure  - Verify project structure"
	@echo "  analyze          - Run static code analysis (requires cppcheck)"
	@echo "  help             - Show this help message"

# File structure validation
check-structure:
	@echo "Checking project structure..."
	@echo "=== Compiler Information ==="
	@$(CXX) --version | head -1
	@echo "Standard: C++17"
	@echo ""
	@echo "=== Required Directories ==="
	@if [ -d "$(SRCDIR)" ]; then echo "✓ $(SRCDIR)/ exists"; else echo "✗ $(SRCDIR)/ missing"; fi
	@if [ -d "$(INCDIR)" ]; then echo "✓ $(INCDIR)/ exists"; else echo "✗ $(INCDIR)/ missing"; fi
	@if [ -d "$(INPUTDIR)" ]; then echo "✓ $(INPUTDIR)/ exists"; else echo "✗ $(INPUTDIR)/ missing"; fi
	@echo ""
	@echo "=== Header Files ==="
	@for header in $(HEADERS); do if [ -f $$header ]; then echo "✓ $$header"; else echo "✗ $$header missing"; fi; done
	@echo ""
	@echo "=== Source Files ==="
	@for source in $(SOURCES); do if [ -f $$source ]; then echo "✓ $$source"; else echo "✗ $$source missing"; fi; done
	@echo ""
	@echo "=== Input Files ==="
	@if [ -f "$(INPUTDIR)/traffic_input.txt" ]; then echo "✓ $(INPUTDIR)/traffic_input.txt"; else echo "✗ $(INPUTDIR)/traffic_input.txt missing (run 'make sample-input' to create)"; fi

# Show project structure
show-structure:
	@echo "Traffic Management System - C++17 Project Structure:"
	@echo "project_root/"
	@echo "├── $(INCDIR)/"
	@echo "│   ├── types.h               # Core enums and types"
	@echo "│   ├── display.h             # Terminal display utilities"
	@echo "│   ├── data_structures.h     # Vehicle, Node, Config structs"
	@echo "│   ├── thread_pool.h         # Thread pool implementation"
	@echo "│   ├── traffic_validator.h   # Input validation logic"
	@echo "│   └── traffic_network.h     # Main traffic network class"
	@echo "├── $(SRCDIR)/"
	@echo "│   ├── main.cpp              # Program entry point"
	@echo "│   ├── display.cpp           # Display implementations"
	@echo "│   ├── data_structures.cpp   # Data structure implementations"
	@echo "│   ├── thread_pool.cpp       # Threading implementations"
	@echo "│   ├── traffic_validator.cpp # Validation implementations"
	@echo "│   └── traffic_network.cpp   # Main simulation logic"
	@echo "├── $(INPUTDIR)/"
	@echo "│   └── traffic_input.txt     # Simulation input data"
	@echo "├── Makefile                  # This build system (C++17)"
	@echo "└── README.md                 # Project documentation"

# Compiler version check
check-compiler:
	@echo "Checking C++ compiler support for C++17..."
	@$(CXX) --version
	@echo ""
	@echo "Testing C++17 features..."
	@echo '#include <iostream>' > /tmp/test_cpp17.cpp
	@echo 'int main() { auto x = []() constexpr { return 42; }; std::cout << x() << std::endl; return 0; }' >> /tmp/test_cpp17.cpp
	@if $(CXX) -std=c++17 /tmp/test_cpp17.cpp -o /tmp/test_cpp17 2>/dev/null; then \
		echo "✓ C++17 support confirmed"; \
		rm -f /tmp/test_cpp17 /tmp/test_cpp17.cpp; \
	else \
		echo "✗ C++17 not supported by your compiler"; \
		rm -f /tmp/test_cpp17.cpp; \
	fi

# Quick setup for new project
quick-setup: setup-dirs sample-input
	@echo "C++17 Traffic Management System setup complete!"
	@echo "Next steps:"
	@echo "1. Place your header files in $(INCDIR)/"
	@echo "2. Place your source files in $(SRCDIR)/"
	@echo "3. Run 'make check-structure' to verify"
	@echo "4. Run 'make check-compiler' to verify C++17 support"
	@echo "5. Run 'make' to build"
	@echo "6. Run 'make run' to execute"

# Phony targets
.PHONY: all run run-no-input clean debug release profile setup-dirs sample-input help check-structure show-structure check-compiler quick-setup analyze