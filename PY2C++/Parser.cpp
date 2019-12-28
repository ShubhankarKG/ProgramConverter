#include "Parser.hpp"

int Parser :: current = 0;

Parser :: Parser(std :: vector<Token> tokens){
    this->tokens = tokens;
}

Expr* Parser :: expression(){
    return equality();
}

Expr* Parser :: equality(){
    Expr* expr = comparison();
    std :: vector<TokenType> v {NOT_EQUAL, EQUAL_EQUAL};
    while (match(v)){
        Token* op = previous();
        Expr* right = comparison();
        expr = new Binary(expr, op, right);
    }
    return expr;
}

Expr* Parser :: comparison(){
    Expr* expr = addition();
    std :: vector <TokenType> v{GREATER, GREATER_EQUAL, LESS, LESS_EQUAL};
    while(match(v)){
        Token* op = previous();
        Expr* right = addition();
        expr = new Binary(expr, op, right);
    }
    return expr;
}

Expr* Parser :: addition(){
    Expr* expr = multiplication();
    std :: vector<TokenType> v;
    v.push_back(MINUS);
    v.push_back(PLUS);
    while (match ( v)) {
        Token* op = previous();
        Expr* right = multiplication();
        expr = new Binary(expr, op, right);
    }
    return expr;
}

Expr* Parser :: multiplication(){
    Expr* expr = unary();
    std :: vector <TokenType> v;
    v.push_back(SLASH);
    v.push_back(STAR);
    while(match(v)){
        Token* op = previous();
        Expr* right = unary();
        expr = new Binary(expr, op, right);
    }
    return expr;
}

Expr* Parser :: unary() {
    std :: vector<TokenType> v;
    v.push_back(NOT);
    v.push_back(MINUS);
    while(match(v)){
        Token* op = previous();
        Expr* right = unary();
        return new Unary(op, right);
    }
    return primary();
}

Expr* Parser :: primary(){
    std :: vector<TokenType> v1,v2,v3,v4,v5,v6;
    v1.push_back(FALSE);
    v2.push_back(TRUE);
    v3.push_back(NONE);

    v4.push_back(NUMBER);
    v5.push_back(STRING);

    v6.push_back(LEFT_PARAN);
    if (match(v1)) return new Literal((void*) false);
    if (match(v2)) return new Literal((void*) true);
    if (match(v3)) return new Literal(nullptr);
    if (match(v4)) return new Literal((previous()->literal));
    if (match(v5)) return new Literal((previous()->literal));
    if (match(v6)) {
        Expr* expr = expression();
        consume(RIGHT_PARAN, "Expect ')' after expression.");
        return new Grouping(expr);
    }
    throw error(peek(), "Expect expression");
}

Token* Parser :: consume(TokenType type, std :: string message){
    if (check(type)) return advance();
    throw error(peek(), message);
}

Token* Parser :: previous(){
    return &tokens[current-1];
}

Token* Parser :: peek(){
    return &tokens[current];
}

Token* Parser :: advance(){
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser :: isAtEnd(){
    return peek()->type == EOFile;
}

bool Parser :: check(TokenType type){
    if (isAtEnd()) return false;
    return peek()->type == type;
}

bool Parser :: match(std :: vector<TokenType> &types){
    for (auto i = types.begin(); i!= types.end(); i++){
        if (check(*i)){
            advance();
            return true;
        }
    }
    return false;
}

ParseError Parser :: error(Token* token, std :: string message){
    ProgramConverter pc;
    ParseError pe;
    pc.error(*token, message);
    return pe;
}

void Parser :: synchronize(){
    advance();
    while(!isAtEnd()){
        if (previous()->type == NEWLINE){
            return;
        }
        switch (peek()->type){
            case CLASS:                            
            case DEF:                              
            case NUMBER:                              
            case FOR:                              
            case IF:                               
            case WHILE:                                                       
            case RETURN:                           
            return;      
        }
        advance();
    }
}

Expr* Parser :: parse(){
    try{
        return expression();
    }
    catch(ParseError& e){
        return NULL;
    }
}

ParseError:: ParseError(){}