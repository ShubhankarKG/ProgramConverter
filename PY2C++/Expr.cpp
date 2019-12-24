#include "Expr.h"

Binary :: Binary(Expr left, Token op, Expr right){
  this->left = left;
  this->op = op;
  this->right = right;
}

Grouping :: Grouping(Expr expression){
  this->expression = expression;
}

Unary :: Unary(Token op, Expr right){
  this->op = op;
  this->right = right;
}

// class Literal
void Binary :: accept(Expr* v){
  v->visit(this);
}

void Unary :: accept(Expr* v){
  v->visit(this);
}

void Grouping :: accept(Expr* v){
  v->visit(this);
}

Expr :: ~Expr(){

}