#include "Scanner.hpp"
//#include "Token.h"

int Scanner :: start = 0;
int Scanner :: current = 0;
int Scanner :: line = 1;

//std :: unordered_map<std::string, TokenType> Scanner::keywords;

// Scanner :: StaticConstructor Scanner:: StaticConstructor;

Scanner :: Scanner(string source){
	this->source = source;
	start = 0;
	current = 0;
	keywords.emplace("False", FALSE);
	keywords.emplace("None", NONE);
	keywords.emplace("True", TRUE);
	keywords.emplace("and", AND);
	keywords.emplace("as", AS);
	keywords.emplace("assert", ASSERT);
	keywords.emplace("async", ASYNC);
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

Scanner :: Scanner(){

}

void Scanner :: addToken(TokenType type){
	addToken(type, " ");
}

void Scanner :: addToken(TokenType type, string literal){
	string text = source.substr(start, current-start);
	//std :: cout << text <<"\n";

	Token tempVar(type, text, literal, line);
	tokens.push_back(tempVar);
	//std :: cout << "Token added\n";
}

void Scanner :: addToken(TokenType type, long double fliteral){
	string text = source.substr(start, current-start);
	Token tempVar(type, text, fliteral, line);
	tokens.push_back(tempVar);
}

void Scanner :: addToken(TokenType type, long long int lliliteral){
	string text = source.substr(start, current-start);
	Token tempVar(type, text, lliliteral, line);
	tokens.push_back(tempVar);
}

void Scanner :: addToken(TokenType type, char cliteral){
	string text = source.substr(start, current-start);
	Token tempVar(type, "", cliteral, line);
	tokens.push_back(tempVar);
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

void Scanner :: isString(char c){
	while (peek() != c && !isAtEnd()){
		if (peek() == '\n') line++;
		advance();
	}
	if (isAtEnd()){
		ProgramConverter pc;
		pc.error(line, "Unterminated String.");
		return;
	}
	advance();

	addToken(STRING, source);
	//std :: cout << value ;
}

void Scanner :: number(){
	while (isDigit(peek())) advance();
	bool floating = false;	// integer by default
	if (peek() == '.' && isDigit(peekNext())){
		if(peek() == '.')	floating = true;
		advance();
		while(isDigit(peek())) advance();
	}
	// addToken(NUMBER, stod(source.substr(start, current)));
	string num = source.substr(start, current-start);
	if(floating) {
		addToken(NUMBER, stold(num));
	}
	else {
		addToken(NUMBER, stoll(num));
	}
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
	int count = 0;
	while (isAlphaNumeric(peek())) {
		advance();
		//cout << "count=" << count << endl;
		count++;
	}
	string text = source.substr(start, current-start);
	//cout << text << endl;
	unordered_map<string, TokenType> :: iterator i;
	TokenType type;
	i = keywords.find(text);
	if(i != keywords.end()) {
		type = i -> second;
	}
	else {
		type = IDENTIFIER;
	}
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
	case ':' : addToken(COLON); break;
	case '[' : addToken(LEFT_SQUARE); break;
	case ']' : addToken(RIGHT_SQUARE); break;
	case ';' : addToken(SEMICOLON); break;

	case '*' : addToken(match('*') ? POWER : STAR); break;
	case '!' : addToken(match('=') ? NOT_EQUAL : LOGICAL_NOT); break;
	case '=' : addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
	case '>' : addToken(match('=') ? GREATER_EQUAL : GREATER); break;
	case '<' : addToken(match('=') ? LESS_EQUAL : LESS); break;
	case '/' : addToken(match('/') ? DOUBLE_SLASH : SLASH); break;

	case '#' : 	while(peek() != '\n' && isAtEnd()) advance();
	case ' ' :
	case '\r':
	case '\t':
		break;
	case '\n':
		line++;
		break;
	case '\"' : isString('\"'); break;
	case '\'' : isString('\''); break;
	// case '\'\'\'' : isString('\'\'\''); break;

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
			cout << "Else switch case \n";
			pc.error(line, "Unterminated string.");
		}
		break;
	}
}

bool Scanner :: isAtEnd() {
	return current >= (int)source.length();
}


vector <Token> Scanner :: scanTokens() {
	while (!isAtEnd()){
		start = current;
		scanToken();
		//std :: cout << "Done Scanning\n";
	}
	Token tempVar(EOFile, "", "", line);
	//std :: cout << "EOF Token created \n";
	tokens.push_back(tempVar);
	return tokens;
}
