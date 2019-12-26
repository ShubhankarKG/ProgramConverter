#include "Expression.hpp"


Binary :: Binary(const Expr& left,const Token op,const Expr& right) :
 left(left), op(op), right(right) {}

Unary :: Unary(const Token op,const Expr& right) : op(op), right(right) {}

Grouping :: Grouping(const Expr& expression): expression(expression) {}


// Literal :: Literal(std :: string value){
//     this->value = value;
// }

// Literal :: Literal(long double dValue){
//     this->dValue = dValue;
// }

// Literal :: Literal(long long int iValue){
//     this->iValue = iValue;
// }

void Binary :: accept(Visitor* v){
    v->visitBinary(*this);
}

void Unary :: accept(Visitor* v){
    v->visitUnary(*this);
}

void Grouping :: accept(Visitor* v){
    v->visitGrouping(*this);
}

// void Literal :: accept(Visitor* v){
//     v->visitLiteral();
// }