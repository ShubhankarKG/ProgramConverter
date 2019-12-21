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
    long long int lliliteral;
    char cliteral;
    int line;
    Token(TokenType type, std :: string lexeme, std :: string literal, int line);
    Token(TokenType type, std :: string lexeme, long double fliteral, int line);
    Token(TokenType type, std :: string lexeme, char cliteral, int line);
    Token(TokenType type, std :: string lexeme, long long lliliteral, int line);

    std :: string toString();
};