#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Token.hpp"
#include "Expression.hpp"
#include "ProgramConverter.hpp"
#include <vector>
#include <cstdarg>

const int TOKENTYPE = 109;

class ParseError : public std::exception {
    public:
    ParseError();
};

class Parser{
    std :: vector <Token> tokens;
    static int current;

    public:
    Parser(std :: vector <Token> tokens);
    Expr* expression();
    Expr* equality();
    Expr* comparison();
    Expr* addition();
    Expr* multiplication();
    Expr* unary();
    Expr* primary();

    Token* advance();
    Token* previous();
    Token* peek();
    Token* consume(TokenType, std::string);

    bool isAtEnd();
    bool check(TokenType);
    bool match(std :: vector <TokenType> &);

    ParseError error(Token* token, std :: string message);

    void synchronize();

    Expr* parse();
};

#endif