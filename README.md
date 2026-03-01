# Algorithm Visualizer

## A desktop application made in C++ using the SFML library, created to visualize algorithms

This project is mainly used to visualize algorithms, but an additional benefit is learning. That is, understanding how a particular algorithm works. The project is mainly based on the literature ‘Introduction to Algorithms’ by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
I have divided the algorithms into 7 groups:

- Sorting algorithms
- Search algorithms
- Data structures
- Dynamic programming
- Advanced data structures
- Graph algorithms

## Table of Contents

- [Installation Guide](#installation-guide)
  - [Prerequisites](#prerequisites)
  - [Linux](#linux)
  - [Windows](#windows)
- [How To Use](#how-to-use)

## Installation Guide

### Prerequisites

- CMake (>= 3.28.3)

#### Linux

1. Clone this repository:
   ```bash
   git clone https://github.com/Misieeeek/Algorithm_Visualizer.git
   cd Algorithm_Visualizer
   mkdir build
   cd build
   ```
2. Configure the project with CMake:
   ```bash
   cmake ..
   ```
3. Compile the project:
   ```bash
   make
   ```

#### Windows

1. Clone this repository:
   ```cmd
   git clone https://github.com/Misieeeek/Algorithm_Visualizer.git
   cd Algorithm_Visualizer
   mkdir build
   cd build
   ```
2. Configure the project with CMake:

   ```cmd
   cmake ..
   ```

3. Compile the project:
   ```cmd
   cmake --build .
   ```

## How To Use

1. Run the executable file `Algorithm_Visualizer` located in the `build` directory.
2. Move using the arrow keys and select using the Enter key.
