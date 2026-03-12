#include "../parser/AST.hpp"
#include <iostream>

Value BinaryExpr::evaluate(std::shared_ptr<Environment> env) {
    Value l = left->evaluate(env);
    Value r = right->evaluate(env);
    
    if (op.type == TokenType::PLUS) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number + r.number);
        if (l.type == Value::STRING && r.type == Value::STRING) return Value(l.string + r.string);
        throw RuntimeError(op.line, op.col, "Operands must be two numbers or two strings.");
    }
    if (op.type == TokenType::MINUS) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number - r.number);
        throw RuntimeError(op.line, op.col, "Operands must be numbers.");
    }
    if (op.type == TokenType::STAR) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number * r.number);
        throw RuntimeError(op.line, op.col, "Operands must be numbers.");
    }
    if (op.type == TokenType::SLASH) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) {
            if (r.number == 0) throw RuntimeError(op.line, op.col, "Division by zero.");
            return Value(l.number / r.number);
        }
        throw RuntimeError(op.line, op.col, "Operands must be numbers.");
    }
    if (op.type == TokenType::GREATER) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number > r.number ? 1.0 : 0.0);
        throw RuntimeError(op.line, op.col, "Operands must be numbers.");
    }
    if (op.type == TokenType::LESS) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number < r.number ? 1.0 : 0.0);
        throw RuntimeError(op.line, op.col, "Operands must be numbers.");
    }
    if (op.type == TokenType::GREATER_EQUAL) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number >= r.number ? 1.0 : 0.0);
        throw RuntimeError(op.line, op.col, "Operands must be numbers.");
    }
    if (op.type == TokenType::LESS_EQUAL) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number <= r.number ? 1.0 : 0.0);
        throw RuntimeError(op.line, op.col, "Operands must be numbers.");
    }
    if (op.type == TokenType::EQUAL) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number == r.number ? 1.0 : 0.0);
        if (l.type == Value::STRING && r.type == Value::STRING) return Value(l.string == r.string ? 1.0 : 0.0);
        return Value(0.0);
    }
    if (op.type == TokenType::NOT_EQUAL) {
        if (l.type == Value::NUMBER && r.type == Value::NUMBER) return Value(l.number != r.number ? 1.0 : 0.0);
        if (l.type == Value::STRING && r.type == Value::STRING) return Value(l.string != r.string ? 1.0 : 0.0);
        return Value(1.0);
    }
    throw RuntimeError(op.line, op.col, "Unknown operator.");
}

Value VariableExpr::evaluate(std::shared_ptr<Environment> env) {
    try {
        return env->get(name.lexeme);
    } catch (std::runtime_error& e) {
        throw RuntimeError(name.line, name.col, e.what());
    }
}

void PrintStmt::execute(std::shared_ptr<Environment> env) {
    Value value = expression->evaluate(env);
    std::cout << value << std::endl;
}

void LetStmt::execute(std::shared_ptr<Environment> env) {
    Value value = Value();
    if (initializer != nullptr) {
        value = initializer->evaluate(env);
    }
    env->define(name.lexeme, value);
}

void IfStmt::execute(std::shared_ptr<Environment> env) {
    if (condition->evaluate(env).isTruthy()) {
        for (auto& stmt : thenBranch) {
            stmt->execute(env);
        }
    }
}

void ForStmt::execute(std::shared_ptr<Environment> env) {
    Value startVal = start->evaluate(env);
    Value endVal = end->evaluate(env);
    
    if (startVal.type != Value::NUMBER || endVal.type != Value::NUMBER) {
        throw RuntimeError(name.line, name.col, "FOR loop bounds must be numbers.");
    }
    
    env->define(name.lexeme, startVal);
    
    double current = startVal.number;
    double limit = endVal.number;
    
    while (current <= limit) {
        env->assign(name.lexeme, Value(current));
        for (auto& stmt : body) {
            stmt->execute(env);
        }
        current += 1.0;
    }
}

void ExpressionStmt::execute(std::shared_ptr<Environment> env) {
    expression->evaluate(env);
}
