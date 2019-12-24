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

class Binary : public Expr{
public:
  Expr left, right;
  Token op;
  void accept(Expr* );
  Binary(Expr left, Token op, Expr right);
};

class Grouping : public Expr {
public:
  Expr expression;
  void accept(Expr* );
  Grouping(Expr expression);
};

class Unary : public Expr{
public:
  Token op;
  Expr right;
  void accept(Expr* );
  Unary(Token op, Expr right);
};


/*
class Literal
*/
