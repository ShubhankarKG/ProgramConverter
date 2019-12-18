#include "TokenType.h"
#include <string>
//#include <any>

using namespace std;
class Token{
    public :
    TokenType type;
    string lexeme;
    string literal;
    int line;
    Token(TokenType type, string lexeme, string literal, int line);
    string toString();
};