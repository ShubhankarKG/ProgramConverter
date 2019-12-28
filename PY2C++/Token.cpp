
#include "Token.hpp"


// Token :: Token(TokenType type, std :: string lexeme, std :: string literal, int line){
//     this->type = type;
//     this->lexeme = lexeme;
//     this->literal = literal;
//     this->line = line;
// }

// Token :: Token(TokenType type, std :: string lexeme, long double fliteral, int line){
//     this->type = type;
//     this->lexeme = lexeme;
//     this->fliteral = fliteral;
//     this->line = line;
// }

// Token :: Token(TokenType type, std :: string lexeme, char cliteral, int line){
//     this->type = type;
//     this->lexeme = lexeme;
//     this->cliteral = cliteral;
//     this->line = line;
// }

// Token :: Token(TokenType type, std :: string lexeme, long long lliliteral, int line){
//     this->type = type;
//     this->lexeme = lexeme;
//     this->lliliteral = lliliteral;
//     this->line = line;
// }

Token :: Token(TokenType type, std :: string lexeme, void* literal, int line) : type(type), lexeme(lexeme), literal(literal), line(line) {}

std :: string Token :: toString(){
   std :: string typeString = enum2str(type);
   return typeString ;
}
