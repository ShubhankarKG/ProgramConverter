#include <iostream>
#include <string>
#include <list>
#include <map>
#include "Token.cpp"
#include "ProgramConverter.cpp"

using namespace std;

class Scanner{
    public:
    string source;
    list <Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;
    map <string, TokenType> keywords;

    Scanner(string source){
        this->source = source;
    }

    private void number() {
		while (isDigit(peek())) advance();
		if (peek() == '.' && isDigit(peekNext())) {
			advance();
			while(isDigit(peek())) advance();
		}
		addToken(NUMBER, Double.parseDouble(source.substring(start, current)));
	}

    bool isAtEnd(){
        return current >= source.length();
    }

    void identifier(){
        while(isAlphaNumeric(peek())) advance();
		string text = source.substring(start, current);
		TokenType type = keywords.get(text);
		if (type == null) type = TokenType.IDENTIFIER; 
		addToken(type);
    }

    bool isAlphaNumeric(char c) {
		return isAlpha(c) || isDigit(c);
	}

    bool isDigit(char c) {
		return c>= '0' && c<= '9';
	}

    bool isAlpha(char c) {
		return (c>='a' && c<='z') ||
			   (c>='A' && c<='Z') || 
			   (c=='_');
	}

    void scanToken(){
        char c = advance();
        switch(c){
            case '(' : addToken(LEFT_PARAN); break;
		case ')' : addToken(RIGHT_PARAN); break;
		case '{' : addToken(LEFT_BRACE); break;
		case '}' : addToken(RIGHT_BRACE); break;
		case ',' : addToken(COMMA); break;
		case '.' : addToken(DOT); break;
		case '-' : addToken(MINUS); break;
		case '+' : addToken(PLUS); break;
		case ';' : addToken(SEMICOLON); break;
		case '*' : addToken(STAR); break;
		case '!' : addToken(match('=') ? NOT_EQUAL : NOT); break;
		case '=' : addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
		case '>' : addToken(match('=') ? GREATER_EQUAL : GREATER); break;
		case '<' : addToken(match('=') ? LESS_EQUAL : LESS); break;
		case '/' :
			if (match('/')) {
				while(peek() != '\n' && isAtEnd()) advance();
			}
			else {
				addToken(SLASH);
			}
			break;
		case ' ' :
		case '\r':
		case '\t':
			break;
		case '\n':
			line++;
			break;
		case '"' : string(); break;
		default : 
			if (isDigit(c)) {
				number();
			}
			else if (isAlpha(c)) {
				identifier();
			}
			else {
			ProgramConverter.error(line, "Unexpected character.");
			}
			break;
        }
    }

    list <Token> scanTokens(){
        while(!isAtEnd()){
            start = current;
            scanToken();
        }
        tokens.push_back(new Token(EOFile, "", NULL, line));
        return tokens;
    }

    

};