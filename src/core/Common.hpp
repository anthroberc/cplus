#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

enum class TokenType {
    LEFT_PAREN, RIGHT_PAREN,
    MINUS, PLUS, SLASH, STAR,
    EQUAL, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, NOT_EQUAL,
    IDENTIFIER, STRING, NUMBER,
    PRINT, LET, IF, THEN, END, FOR, TO, NEXT,
    NEWLINE, END_OF_FILE, ERROR_TOKEN
};

struct Token {
    TokenType type;
    std::string lexeme;
    double number_value = 0;
    int line = 1;
    int col = 1;
};

struct Value {
    enum Type { NUMBER, STRING, NIL } type;
    double number = 0;
    std::string string = "";

    Value() : type(NIL) {}
    Value(double n) : type(NUMBER), number(n) {}
    Value(std::string s) : type(STRING), string(s) {}

    bool isTruthy() const {
        if (type == NIL) return false;
        if (type == NUMBER) return number != 0;
        if (type == STRING) return !string.empty();
        return false;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Value& val) {
    if (val.type == Value::NUMBER) os << val.number;
    else if (val.type == Value::STRING) os << val.string;
    else os << "nil";
    return os;
}

class ParserError : public std::runtime_error {
public:
    int line, col;
    ParserError(int line, int col, const std::string& message) 
        : std::runtime_error("SyntaxError: " + message + " (Line " + std::to_string(line) + ", Col " + std::to_string(col) + ")"), line(line), col(col) {}
};

class RuntimeError : public std::runtime_error {
public:
    int line, col;
    RuntimeError(int line, int col, const std::string& message) 
        : std::runtime_error("RuntimeError: " + message + " (Line " + std::to_string(line) + ", Col " + std::to_string(col) + ")"), line(line), col(col) {}
};
