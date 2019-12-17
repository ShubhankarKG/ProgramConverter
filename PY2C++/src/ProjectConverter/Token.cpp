#include <iostream>
#include <string>
#include "TokenType.cpp"
class Token{
    TokenType type;
    public:
    Token(TokenType type){
        this->type = type;
    }
    void print(){
        std :: cout << type << "\n" ;
    }
};

int main(){
    Token token(DOT);
    token.print();
}