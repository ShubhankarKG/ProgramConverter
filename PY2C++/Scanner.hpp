#ifndef SCANNER_H
#define SCANNER_H
#include "Token.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include "ProgramConverter.hpp"
#include <stdio.h>

using namespace std;
class Scanner{
    std :: string source;
    vector <Token> tokens;
    static int start;
    static int current;
    static int line;
    
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
    void isString(char c);
    char peek();
    char peekNext();
    bool match(char expected);
    char advance();
    void addToken(TokenType token);
    void addToken(TokenType token, void* literal);
    // void addToken(TokenType token, long double fliteral);
    // void addToken(TokenType token, char cliteral);
    // void addToken(TokenType type, long long int lliliteral);
};

#endif