#include "Scanner.h"
//#include "Token.h"
#include "ProgramConverter.h"

namespace ProjectConverter {
	int Scanner :: start = 0;
	int Scanner :: current = 0;
	int Scanner :: line = 1;

	std :: unordered_map<std::string, TokenType> Scanner::keywords;
	
	Scanner :: StaticConstructor :: StaticConstructor() {
		//keywords = new unordered_map<string, TokenType>;
		keywords.emplace("False", FALSE);
		keywords.emplace("None", NONE);
		keywords.emplace("True", TRUE);
		keywords.emplace("and", AND);
		keywords.emplace("as", AS);
		keywords.emplace("assert", ASSERT);
		keywords.emplace("async", AYNC);
		keywords.emplace("await", AWAIT);
		keywords.emplace("break", BREAK);
		keywords.emplace("class", CLASS);
		keywords.emplace("continue", CONTINUE);
		keywords.emplace("def", DEF);
		keywords.emplace("del", DEL);
		keywords.emplace("elif", ELIF);
		keywords.emplace("else", ELSE);
		keywords.emplace("except", EXCEPT);
		keywords.emplace("finally", FINALLY);
		keywords.emplace("for", FOR);
		keywords.emplace("from", FROM);
		keywords.emplace("global", GLOBAL);
		keywords.emplace("if", IF);
		keywords.emplace("import", IMPORT);
		keywords.emplace("in", IN);
		keywords.emplace("is", IS);
		keywords.emplace("lambda", LAMBDA);
		keywords.emplace("nonlocal", NONLOCAL);
		keywords.emplace("not", NOT);
		keywords.emplace("or", OR);
		keywords.emplace("pass", PASS);
		keywords.emplace("raise", RAISE);
		keywords.emplace("return", RETURN);
		keywords.emplace("try", TRY);
		keywords.emplace("while", WHILE);
		keywords.emplace("with", WITH);
		keywords.emplace("yield", YIELD);
	}
	
	// Scanner :: StaticConstructor Scanner:: StaticConstructor;

	Scanner :: Scanner(string source){
		this->source = source;
		
	}

	Scanner :: Scanner(){
		
	}

	void Scanner :: addToken(TokenType type){
		addToken(type,"");
	}

	void Scanner :: addToken(TokenType type, string literal){
		string text = source.substr(start, current);
		tokens.push_back(new Token(type, text, literal, line));
	}

	char Scanner :: advance(){
		current++;
		return source[current-1];
	}

	bool Scanner :: match(char expected){
		if (isAtEnd()) return false;
		if (source[current] != expected) return false;
		current++;
		return true;
	}

	char Scanner :: peekNext(){
		if (isAtEnd()) return '\0';
		return source[current+1];
	}

	char Scanner :: peek(){
		if (isAtEnd()) return '\0';
		return source[current];
	}

	void Scanner :: isString(){
		while (peek() != '"' && !isAtEnd()){
		if (peek() == '\n') line++;
		advance();
		}
		if (isAtEnd()){
			//::error(line, "Unterminated String.");
			ProgramConverter pc;
			pc.error(line, "Unterminated String.");
		}
		advance();
		string value = source.substr(start+1, current-1);
		addToken(STRING, value);
	}

	void Scanner :: number(){
		while (isDigit(peek())) advance();
		if (peek() == '.' && isDigit(peekNext())){
			advance();
			while(isDigit(peek())) advance();
		}
		//addToken(NUMBER, stod(source.substr(start, current)));
	}

	bool Scanner :: isAlphaNumeric(char c){
		return isAlpha(c) || isDigit(c);
	}

	bool Scanner :: isDigit(char c){
		return c>='0' && c<='9';
	}

	bool Scanner :: isAlpha(char c){
		return (c>='a' && c<='z')||
			(c>='A' && c<='Z')||
			(c=='_');
	}

	void Scanner :: identifier(){
		while (isAlphaNumeric(peek())) {
			advance();
		}
		string text = source.substr(start, current);
		unordered_map<string, TokenType> :: iterator i;
		TokenType type;
		i = keywords.find(text);
		type = i->second;
		if (i == keywords.end()) type = IDENTIFIER;
		addToken(type);
	}


	void Scanner :: scanToken(){
		char c = advance();
		switch(c) {
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

		case '!' : addToken(match('=') ? NOT_EQUAL : LOGICAL_NOT); break;
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

		case '"' : isString(); break;

		default : 
			if (isDigit(c)) {
				number();
			}
			else if (isAlpha(c)) {
				identifier();
			}
			else {
				//ProgramConverter::error(line, "Unterminated string.");
				ProgramConverter pc;
				pc.error(line, "Unterminated string.");
			}
			break;
		}
	}

	bool Scanner :: isAtEnd() {
		return current >= source.length();
	}


	list <Token*> Scanner :: scanTokens() {
		while (!isAtEnd()){
			start = current;
			scanToken();
		}
		return tokens;
	}
}

// int main(){
// 	return 0;
// }