# C+ (C-Plus) Programming Language

C+ is a modern, high-performance programming language designed for clarity, safety, and efficiency. It features a clean, block-based syntax and a robust standard library, making it an excellent choice for everything from systems programming to rapid application development.

## Key Features

- **Modern Syntax**: Uses a consistent, block-based structure for better readability and maintainability.
- **Automated Memory Management**: Features built-in memory safety with automated cleanup, allowing you to focus on logic rather than manual memory allocation.
- **Strongly Typed**: Provides type safety while remaining flexible enough for dynamic data structures.
- **Cross-Platform**: Compiles and runs seamlessly on Linux, macOS, and Windows.
- **Extensible Architecture**: Built with a modular C++20 core, designed for easy extension and high performance.

## Getting Started

### Installation

You can download the latest pre-compiled binaries for your platform from the [Releases](https://github.com/sapirrior/cplus/releases) page.

To run a C+ script:

```bash
./cplus script.cp
```

To enter the interactive REPL:

```bash
./cplus
```

### Your First C+ Program

Create a file named `hello.cp`:

```cplus
def greet(name) {
    if (name == None) {
        print("Hello, World!");
    } else {
        print("Hello, " + name + "!");
    };
};

greet("Developer");
```

Run it with: `./cplus hello.cp`

## Documentation

Comprehensive guides are available in the `documentation/` directory:

1. [Introduction to C+](documentation/01-introduction.md)
2. [Language Syntax](documentation/02-syntax.md)
3. [Control Flow](documentation/03-control-flow.md)
4. [Operators & Expressions](documentation/04-operators.md)
5. [CLI Usage](documentation/05-cli-usage.md)

## Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for more information.

## License

C+ is licensed under the MIT License.
