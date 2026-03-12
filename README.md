# C+ Interpreter

A modern, production-grade BASIC-style interpreter written in C++17.

## Features
- **Modern Syntax**: Clean, BASIC-inspired syntax (LET, PRINT, IF/THEN, FOR/NEXT).
- **Optimized Execution**: AST-based execution with C++ smart pointer-based memory management.
- **Robust CLI**: Supports running scripts, interactive REPL, and version checking.
- **Error Handling**: Detailed Syntax and Runtime error reporting (Line X, Col Y).

## Getting Started

### Prerequisites
- C++17 compatible compiler (e.g., clang++, g++).

### Compiling
To compile the interpreter, use the following command:
```bash
clang++ -std=c++17 src/main.cpp src/core/*.cpp src/lexer/*.cpp src/parser/*.cpp src/interpreter/*.cpp -I src/ -o cplus
```

### Usage
- **Run a script**: `./cplus your_script.cp`
- **Start REPL**: `./cplus`
- **Check Version**: `./cplus -version`
- **Help**: `./cplus -help`

## Example Code (test.cp)
```basic
LET x = 10
PRINT "Running FOR loop:"
FOR i = 1 TO 5
    PRINT x + i
NEXT
IF x > 5 THEN
    PRINT "x is greater than 5"
END IF
```
