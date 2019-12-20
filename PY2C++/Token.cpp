#include "Token.h"

namespace ProjectConverter{

    Token :: Token(TokenType type, std :: string lexeme, std :: string literal, int line){
        this->type = type;
        this->lexeme = lexeme;
        this->literal = literal;
        this->line = line;
    }

    std :: string Token :: toString(){
        return type + " "+ lexeme + " " + literal;
    }

}