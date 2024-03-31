# MEEv

## Introduction
MEEv, short for Math Expression Evaluator, is a versatile command-line application designed to evaluate mathematical expressions. It gracefully handles both integer and double values, performing an array of basic operations and standard math functions. Users can adjust the precision of the results, which by default is set to six, through a simple command-line argument, tailoring the output to their specific needs.

## Supported Functions
MEEv efficiently calculates the following mathematical functions, ensuring broad utility for various mathematical computations:

- Trigonometric Functions: `cos`, `sin`, `tan`, along with their inverse functions `acos`, `asin`, `atan`.
- Arithmetic Functions: `sqrt` for square roots, `pow` for exponentiation.

## Prerequisites
Before installing MEEv, ensure your system has the following tools:

- CMake: A cross-platform tool for managing the build process.
- GNU Make: A tool which controls the generation of executables and other non-source files from source files.
- A C++ compiler: Such as g++ or clang, to compile the source code.

## Installation Instructions

Follow these steps to install and run MEEv on your system:

1. **Clone the Repository:**
   Begin by cloning the MEEv repository to your local machine using the following command:
   ```bash
   git clone https://github.com/Cheracpp/MEEv.git
   ```

2. **Build the Project:**
   Navigate to the MEEv directory, create a new build directory, and compile the application:
   ```bash
   cd MEEv
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Execute the Application:**
   Run MEEv by passing a mathematical expression as an argument. For example:
   ```bash
   ./MEEV '1 + (2 * 3 - 10.5)^2 + sqrt(2)'
   ```
   Output:
   `Answer: 22.6642`

   To customize the precision, specify the number of decimal places as a second argument:
   ```bash
   ./MEEV '1 + (2 * 3 - 10.5)^2 + sqrt(2)' '10'
   ```
   Output:
   `Answer: 22.66421356`

   Note: MEEv ignores whitespace within expressions but requires function names to be contiguous and in lowercase. For example, use `sqrt(a)` instead of `sqrt (a)` or `SQRT(a)`.

## Additional Notes
- **Error Handling:** MEEv robustly detects and informs the user of any malformations in the input expression, ensuring clear communication and user guidance.
- **Flexibility:** Whether your input includes spaces between numbers and operators or compact mathematical functions, MEEv is designed to process the expression accurately, maintaining its user-friendly nature.

