#ifndef TOKENTYPE_H
#define TOKENTYPE_H
#include <iostream>
#endif

namespace ProjectConverter{

    enum TokenType{
        // Single character tokens
        LEFT_PARAN, RIGHT_PARAN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

        // One or Two character tokens
        LOGICAL_NOT, NOT_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Literals
        IDENTIFIER, STRING, NUMBER,

        //Keywords
        FALSE, NONE, TRUE, AND, AS, ASSERT, AYNC,AWAIT, BREAK,
        CLASS, CONTINUE, DEF, DEL, ELIF, ELSE, EXCEPT, FINALLY, FOR, FROM,
        GLOBAL, IF, IMPORT, IN, IS, LAMBDA, NONLOCAL, NOT, OR, PASS,
        RAISE, RETURN, TRY, WHILE, WITH, YIELD
    };

}