#ifndef TOKEN
#define TOKEN
#include "TokenType.h"
#include <string>
//#include <any>
#endif


class Token{
    public :
    TokenType type;
    std :: string lexeme;
    std :: string literal;
    long double fliteral;
    char cliteral;
    int line;
    Token(TokenType type, std :: string lexeme, std :: string literal, int line);
    Token(TokenType type, std :: string lexeme, long double fliteral, int line);
    Token(TokenType type, std :: string lexeme, char cliteral, int line);

    std :: string toString();
};