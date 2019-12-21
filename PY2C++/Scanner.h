#ifndef SCANNER_H
#define SCANNER_H
#include "Token.h"
#include <string>
#include <unordered_map>
#include <vector>
//#include <any>
#endif

using namespace std;

class Token;



class Scanner{
    std :: string source;
    vector <Token> tokens;
    static int start;
    static int current;
    static int line;
    /*    
    class StaticConstructor{
        public:
        StaticConstructor();
    };
    static StaticConstructor staticConstructor;
    */
    public :
    unordered_map <string, TokenType> keywords;
    Scanner();
    Scanner(string source);
    vector <Token> scanTokens();
    bool isAtEnd();
    void scanToken();
    void identifier();
    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);
    void number();
    void isString();
    char peek();
    char peekNext();
    bool match(char expected);
    char advance();
    void addToken(TokenType token);
    void addToken(TokenType token, string literal);
    void addToken(TokenType token, long double fliteral);
    void addToken(TokenType token, char cliteral);
    void addToken(TokenType type, long long int lliliteral);
};