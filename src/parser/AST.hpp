#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../core/Common.hpp"
#include "../core/Environment.hpp"

class Expr {
public:
    virtual ~Expr() = default;
    virtual Value evaluate(std::shared_ptr<Environment> env) = 0;
};

class BinaryExpr : public Expr {
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
public:
    BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) {}
    Value evaluate(std::shared_ptr<Environment> env) override;
};

class LiteralExpr : public Expr {
    Value value;
public:
    LiteralExpr(Value value) : value(value) {}
    Value evaluate(std::shared_ptr<Environment> env) override { return value; }
};

class GroupingExpr : public Expr {
    std::shared_ptr<Expr> expression;
public:
    GroupingExpr(std::shared_ptr<Expr> expression) : expression(expression) {}
    Value evaluate(std::shared_ptr<Environment> env) override { return expression->evaluate(env); }
};

class VariableExpr : public Expr {
    Token name;
public:
    VariableExpr(Token name) : name(name) {}
    Value evaluate(std::shared_ptr<Environment> env) override;
};

class Stmt {
public:
    virtual ~Stmt() = default;
    virtual void execute(std::shared_ptr<Environment> env) = 0;
};

class PrintStmt : public Stmt {
    std::shared_ptr<Expr> expression;
public:
    PrintStmt(std::shared_ptr<Expr> expression) : expression(expression) {}
    void execute(std::shared_ptr<Environment> env) override;
};

class LetStmt : public Stmt {
    Token name;
    std::shared_ptr<Expr> initializer;
public:
    LetStmt(Token name, std::shared_ptr<Expr> initializer) : name(name), initializer(initializer) {}
    void execute(std::shared_ptr<Environment> env) override;
};

class IfStmt : public Stmt {
    std::shared_ptr<Expr> condition;
    std::vector<std::shared_ptr<Stmt>> thenBranch;
public:
    IfStmt(std::shared_ptr<Expr> condition, std::vector<std::shared_ptr<Stmt>> thenBranch) : condition(condition), thenBranch(thenBranch) {}
    void execute(std::shared_ptr<Environment> env) override;
};

class ForStmt : public Stmt {
    Token name;
    std::shared_ptr<Expr> start;
    std::shared_ptr<Expr> end;
    std::vector<std::shared_ptr<Stmt>> body;
public:
    ForStmt(Token name, std::shared_ptr<Expr> start, std::shared_ptr<Expr> end, std::vector<std::shared_ptr<Stmt>> body) : name(name), start(start), end(end), body(body) {}
    void execute(std::shared_ptr<Environment> env) override;
};

class ExpressionStmt : public Stmt {
    std::shared_ptr<Expr> expression;
public:
    ExpressionStmt(std::shared_ptr<Expr> expression) : expression(expression) {}
    void execute(std::shared_ptr<Environment> env) override;
};
