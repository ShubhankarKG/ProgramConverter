#include "Expression.hpp"

Binary :: Binary(Expr left, Token op, Expr right){
    this->left = left;
    this->op = op;
    this->right = right;
}

Unary :: Unary(Token op, Expr right){
    this->op = op;
    this->right = right;
}

Grouping :: Grouping(Expr expression){
    this->expression = expression;
}

Literal :: Literal(std :: string value){
    this->value = value;
}

Literal :: Literal(long double dValue){
    this->dValue = dValue;
}

Literal :: Literal(long long int iValue){
    this->iValue = iValue;
}

void Binary :: accept(Visitor* v){
    v->visitBinary();
}

void Unary :: accept(Visitor* v){
    v->visitUnary();
}

void Grouping :: accept(Visitor* v){
    v->visitGrouping();
}

void Literal :: accept(Visitor* v){
    v->visitLiteral();
}