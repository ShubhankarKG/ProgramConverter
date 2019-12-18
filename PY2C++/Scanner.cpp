#include "Scanner.h"
#include "Token.h"
#include "ProgramConverter.h"

int Scanner :: start = 0;
int Scanner :: current = 0;
int Scanner :: line = 1;

Scanner :: Scanner(string source){
	this->source = source;
	keywords = unordered_map<string, TokenType>();
	keywords.emplace("and", TokenType::AND);
	keywords.emplace("class", TokenType::CLASS);
	keywords.emplace("else", TokenType::ELSE);
	keywords.emplace("false", TokenType::FALSE);
	keywords.emplace("fun", TokenType::FUN);
	keywords.emplace("for", TokenType::FOR);
	keywords.emplace("if", TokenType::IF);
	keywords.emplace("nil", TokenType::NIL);
	keywords.emplace("or", TokenType::OR);
	keywords.emplace("print", TokenType::PRINT);
	keywords.emplace("return", TokenType::RETURN);
	keywords.emplace("super", TokenType::SUPER);
	keywords.emplace("this", TokenType::THIS);
	keywords.emplace("true", TokenType::TRUE);
	keywords.emplace("var", TokenType::VAR);
	keywords.emplace("while", TokenType::WHILE);
}

/*
void Scanner :: addToken(TokenType* type){
	addToken(token, NULL);
}
*/
/*
void Scanner :: addToken(TokenType* type, Object literal){
	string text = source.substr(start, current);
	tokens.add(new Token(type, text, literal, line));
}
*/
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
		//ProgramConverter.error(line, "Unterminated String.");
	}
	advance();
	string value = source.substr(start+1, current-1);
	//addToken(STRING, value);
}

void Scanner :: number(){
	while (isDigit(peek())) advance();
	if (peek() == '.' && isDigit(peekNext())){
		advance();
		while(isDigit(peek())) advance;
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
	if (i == keywords.end()) type =  TokenType::IDENTIFIER;
	//addToken(type);
}

/*
void Scanner :: scanToken(){
	char c = advance();
	switch(c) {
	case '(' : addToken(TokenType::LEFT_PARAN); break;
	case ')' : addToken(TokenType::RIGHT_PARAN); break;
	case '{' : addToken(TokenType::LEFT_BRACE); break;
	case '}' : addToken(TokenType::RIGHT_BRACE); break;
	case ',' : addToken(TokenType::COMMA); break;
	case '.' : addToken(TokenType::DOT); break;
	case '-' : addToken(TokenType::MINUS); break;
	case '+' : addToken(TokenType::PLUS); break;
	case ';' : addToken(TokenType::SEMICOLON); break;
	case '*' : addToken(TokenType::STAR); break;
	case '!' : addToken(match('=') ? TokenType::NOT_EQUAL : TokenType::NOT); break;
	case '=' : addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
	case '>' : addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
	case '<' : addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
	case '/' :
		if (match('/')) {
			while(peek() != '\n' && isAtEnd()) advance();
		}
		else {
			addToken(TokenType::SLASH);
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
			ProgramConverter::error(line, "Unterminated string.");
		}
		break;
	}
}
*/

bool Scanner :: isAtEnd() {
	return current >= source.length();
}

/*
list <Token*> Scanner :: scanTokens() {
	while (!isAtEnd()){
		start = current;
		scanToken();
	}
	tokens.add(new Token(EOFile, "", NULL, line));
	return tokens;
}
*/