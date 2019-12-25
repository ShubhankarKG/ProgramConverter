#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include "Token.hpp"

class Visitor;
class Expr {
    public:
    virtual void accept(Visitor* v);
};

class Binary : public Expr, public Visitor {
    public:
    Expr left;
    Token op;
    Expr right;

    Binary(Expr left, Token op, Expr right);
    void accept(Visitor*);
};

class Unary : public Expr, public Visitor {
    public:
    Token op;
    Expr right;

    Unary(Token op, Expr right);
    void accept(Visitor*);
};

class Grouping : public Expr, public Visitor {
    public:
    Expr expression;

    Grouping(Expr expression);
    void accept(Visitor*);
};

class Literal : public Expr, public Visitor {
    public:
    std :: string value;
    long double dValue;
    long long int iValue;

    Literal(std::string value);
    Literal(long double dValue);
    Literal(long long int iValue);
    void accept(Visitor*);
};

class Visitor {
    public:
    void visitBinary(){};
    void visitUnary(){};
    void visitGrouping(){};
    void visitLiteral(){};
};

#endif