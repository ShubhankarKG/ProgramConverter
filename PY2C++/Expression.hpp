#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <sstream>
#include "Token.hpp"

class Visitor;
class Expr {
    public:
    virtual void accept(Visitor* v) = 0;
};

class Binary : public Expr {
    public:
    const Expr* left;
    const Token op;
    const Expr* right;

    Binary(const Expr* left,const Token op,const Expr* right);
    void accept(Visitor*);
};

class Unary : public Expr {
    public:
    const Token op;
    const Expr* right;

    Unary(const Token op,const Expr* right);
    void accept(Visitor*);
};

class Grouping : public Expr {
    public:
    const Expr* expression;

    Grouping(const Expr* expression);
    void accept(Visitor*);
};

class Literal : public Expr {
    public:
    std :: string value;
    long double dValue;
    long long int iValue;
    bool bValue;

    Literal(bool bValue);
    Literal(std::string value);
    Literal(long double dValue);
    Literal(long long int iValue);
    void accept(Visitor*);
};

class Visitor {
    public:
    virtual void visitBinary(const Binary&) = 0;
    virtual void visitUnary(const Unary&) = 0;
    virtual void visitGrouping(const Grouping&) = 0;
    virtual void visitLiteral(const Literal&) = 0;
};

#endif