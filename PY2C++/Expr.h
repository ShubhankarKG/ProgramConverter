//#include "Visitor.h"
#include "Token.h"
using namespace std;

//class Visitor;
class Binary;
class Unary;
class Grouping;
class Expr{
public:
  void accept(Expr*);
  virtual void visit(Binary* ){};
  virtual void visit(Grouping* ){};
  virtual void visit(Unary* ){};
  ~Expr();
};

class Binary : public Expr/*, public Visitor */{
public:
  Expr left, right;
  Token op;
  void accept(Expr* );
  //void visit(Binary* );
  Binary(Expr left, Token op, Expr right);
  // ~Binary();
};

class Grouping : public Expr/*, public Visitor*/ {
public:
  Expr expression;
  void accept(Expr* );
  //void visit(Grouping* );
  Grouping(Expr expression);
  // ~Grouping();
};

class Unary : public Expr/*, public Visitor */{
public:
  Token op;
  Expr right;
  void accept(Expr* );
  //void visit(Unary* );
  Unary(Token op, Expr right);
};


/*
class Literal
*/
