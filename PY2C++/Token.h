#ifndef TOKEN
#define TOKEN
#include "TokenType.h"
#include <string>
//#include <any>
#endif

namespace ProjectConverter{

    class Token{
        public :
        TokenType type;
        std :: string lexeme;
        std :: string literal;
        int line;
        Token(TokenType type, std :: string lexeme, std :: string literal, int line);
        std :: string toString();
    };

}