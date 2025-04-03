# Algorithm Visualizer

## A desktop application made in C++ using the SFML library, created to visualise algorithms

This project is mainly used to visualise algorithms, but an additional benefit is learning. That is, understanding how a particular algorithm works. The project is mainly based on the literature ‘Introduction to Algorithms’ by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
I have divided the algorithms into 7 groups:

- Sorting algorithms
- Search algorithms
- Data structures
- Dynamic programming
- Advanced data structures
- Graph algorithms

## Installation Guide

### Prerequisites

- CMake (>= 3.28.3)

#### Linux

1. Clone this repository:
   ```bash
   git clone https://github.com/Misieeeek/Algorithm_Visualizer.git
   cd Algorithm_Visualizer/build
   ```
2. Configure the project with CMake:
   ```bash
   cmake ..
   ```
3. Compile the project:
   ```bash
   make
   ```

#### Windows (using Visual Studio)

1. Clone this repository:
   ```cmd
   git clone https://github.com/Misieeeek/Algorithm_Visualizer.git
   cd Algorithm_Visualizer/build
   ```
2. Configure the project with CMake:

   ```cmd
   cmake .. -G "Visual Studio 17 2022" -A x64
   ```

   Note: Adjust the Visual Studio version to match the one you have installed.

3. Open the generated .sln file in Visual Studio and build the project, or use the command line:
   ```cmd
   cmake --build . --config Release
   ```

#### Windows (using MinGW)

1. Clone this repository:
   ```cmd
   git clone https://github.com/Misieeeek/Algorithm_Visualizer.git
   cd Algorithm_Visualizer/build
   ```
2. Configure the project with CMake:

   ```cmd
   cmake .. -G "MinGW Makefiles"
   ```

3. Compile the project:
   ```cmd
   mingw32-make
   ```
