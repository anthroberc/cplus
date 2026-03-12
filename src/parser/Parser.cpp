#include "Parser.hpp"

std::vector<std::shared_ptr<Stmt>> Parser::parse() {
    std::vector<std::shared_ptr<Stmt>> statements;
    while (!isAtEnd()) {
        if (match(TokenType::NEWLINE)) continue;
        statements.push_back(statement());
    }
    return statements;
}

std::shared_ptr<Stmt> Parser::statement() {
    if (match(TokenType::PRINT)) return printStatement();
    if (match(TokenType::LET)) return letStatement();
    if (match(TokenType::IF)) return ifStatement();
    if (match(TokenType::FOR)) return forStatement();
    return expressionStatement();
}

std::shared_ptr<Stmt> Parser::printStatement() {
    std::shared_ptr<Expr> expr = expression();
    if (!isAtEnd()) consume(TokenType::NEWLINE, "Expect newline after print statement.");
    return std::make_shared<PrintStmt>(expr);
}

std::shared_ptr<Stmt> Parser::letStatement() {
    Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
    consume(TokenType::EQUAL, "Expect '=' after variable name.");
    std::shared_ptr<Expr> initializer = expression();
    if (!isAtEnd()) consume(TokenType::NEWLINE, "Expect newline after let statement.");
    return std::make_shared<LetStmt>(name, initializer);
}

std::shared_ptr<Stmt> Parser::ifStatement() {
    std::shared_ptr<Expr> condition = expression();
    consume(TokenType::THEN, "Expect 'THEN' after IF condition.");
    consume(TokenType::NEWLINE, "Expect newline after THEN.");
    
    std::vector<std::shared_ptr<Stmt>> thenBranch;
    while (!check(TokenType::END) && !isAtEnd()) {
        if (match(TokenType::NEWLINE)) continue;
        thenBranch.push_back(statement());
    }
    consume(TokenType::END, "Expect 'END' after IF block.");
    consume(TokenType::IF, "Expect 'IF' after END.");
    if (!isAtEnd()) consume(TokenType::NEWLINE, "Expect newline after END IF.");
    
    return std::make_shared<IfStmt>(condition, thenBranch);
}

std::shared_ptr<Stmt> Parser::forStatement() {
    Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
    consume(TokenType::EQUAL, "Expect '=' after variable name.");
    std::shared_ptr<Expr> start = expression();
    consume(TokenType::TO, "Expect 'TO' after FOR start value.");
    std::shared_ptr<Expr> end = expression();
    consume(TokenType::NEWLINE, "Expect newline after FOR statement.");
    
    std::vector<std::shared_ptr<Stmt>> body;
    while (!check(TokenType::NEXT) && !isAtEnd()) {
        if (match(TokenType::NEWLINE)) continue;
        body.push_back(statement());
    }
    consume(TokenType::NEXT, "Expect 'NEXT' after FOR block.");
    if (!isAtEnd()) consume(TokenType::NEWLINE, "Expect newline after NEXT.");
    
    return std::make_shared<ForStmt>(name, start, end, body);
}

std::shared_ptr<Stmt> Parser::expressionStatement() {
    std::shared_ptr<Expr> expr = expression();
    if (!isAtEnd()) consume(TokenType::NEWLINE, "Expect newline after expression.");
    return std::make_shared<ExpressionStmt>(expr);
}

std::shared_ptr<Expr> Parser::expression() {
    return equality();
}

std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr = comparison();
    while (match(TokenType::EQUAL) || match(TokenType::NOT_EQUAL)) {
        Token op = previous();
        std::shared_ptr<Expr> right = comparison();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
    std::shared_ptr<Expr> expr = term();
    while (match(TokenType::GREATER) || match(TokenType::GREATER_EQUAL) || match(TokenType::LESS) || match(TokenType::LESS_EQUAL)) {
        Token op = previous();
        std::shared_ptr<Expr> right = term();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::term() {
    std::shared_ptr<Expr> expr = factor();
    while (match(TokenType::MINUS) || match(TokenType::PLUS)) {
        Token op = previous();
        std::shared_ptr<Expr> right = factor();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr = primary();
    while (match(TokenType::SLASH) || match(TokenType::STAR)) {
        Token op = previous();
        std::shared_ptr<Expr> right = primary();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::primary() {
    if (match(TokenType::NUMBER)) {
        return std::make_shared<LiteralExpr>(Value(previous().number_value));
    }
    if (match(TokenType::STRING)) {
        return std::make_shared<LiteralExpr>(Value(previous().lexeme));
    }
    if (match(TokenType::IDENTIFIER)) {
        return std::make_shared<VariableExpr>(previous());
    }
    if (match(TokenType::LEFT_PAREN)) {
        std::shared_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_shared<GroupingExpr>(expr);
    }
    throw ParserError(peek().line, peek().col, "Expect expression.");
}
