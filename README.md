# Traffic Management System

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Build](https://github.com/Xhadou/Traffic-Management-System/actions/workflows/build.yml/badge.svg?branch=main)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)

A sophisticated real-time traffic management simulation system built in modern C++17. It models vehicle movement through a network of interconnected traffic nodes, supports multiple vehicle types with priority-based routing, and provides multiple simulation modes.

---

## Key Features

- **Multi-threaded Simulation**: Utilizes a custom thread pool for concurrent and efficient processing of traffic nodes.
- **Priority-based Vehicle Routing**: Emergency vehicles (ambulances, fire trucks) are given precedence over regular traffic.
- **Real-time Visualization**: Offers an ANSI color-coded terminal dashboard for monitoring the simulation.
- **Optimal Pathfinding**: Implements BFS to calculate the shortest path for vehicles.
- **Dynamic Capacity Management**: Nodes have capacity limits, and vehicles queue when a node is full.
- **Comprehensive Statistics**: Tracks and displays detailed performance metrics.
- **Modular & Modern Codebase**: Written in C++17 with a clean separation of concerns, smart pointers for memory management, and a custom thread pool.

---

## Quick Start Guide

### Prerequisites

- A C++17 compatible compiler (GCC 7+, Clang 5+).
- `make` build utility.

```bash
# Check for prerequisites
g++ --version
make --version
```

### Build & Run

```bash
# 1. Clone the repository
# git clone github.com/Xhadou/Traffic-Management-System
# cd traffic-management-system

# 2. Set up project directories
make setup-dirs

# 3. Generate a sample input file
make sample-input

# 4. Build the project
make

# 5. Run the simulation
make run
```

---

## Project Structure

```
.
├── include/          # Header files (interfaces)
├── src/              # Source files (implementations)
├── input/            # Input configuration files
├── Makefile          # Build system configuration
├── README.md         # This file
└── DOCUMENTATION.md  # Detailed technical documentation
```

---

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any bugs or feature requests.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Full Documentation

For a deep dive into the project's architecture, algorithms, and implementation details, please see the [**Full Technical Documentation**](DOCUMENTATION.md).
