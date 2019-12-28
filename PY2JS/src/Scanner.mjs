import { error } from './ProgramConverter.mjs'
import { TokenType } from './TokenType.mjs'
import { Token } from './Token.mjs'

let keywords = new Map()
let start = 0
let current = 0
let line = 1
let source = ""
let tokens = new Array()

keywords.set("False", TokenType.FALSE);
keywords.set("None", TokenType.NONE);
keywords.set("True", TokenType.TRUE);
keywords.set("and", TokenType.AND);
keywords.set("as", TokenType.AS);
keywords.set("assert", TokenType.ASSERT);
keywords.set("async", TokenType.AYNC);
keywords.set("await", TokenType.AWAIT);
keywords.set("break", TokenType.BREAK);
keywords.set("class", TokenType.CLASS);
keywords.set("continue", TokenType.CONTINUE);
keywords.set("def", TokenType.DEF);
keywords.set("del", TokenType.DEL);
keywords.set("elif", TokenType.ELIF);
keywords.set("else", TokenType.ELSE);
keywords.set("except", TokenType.EXCEPT);
keywords.set("finally", TokenType.FINALLY);
keywords.set("for", TokenType.FOR);
keywords.set("from", TokenType.FROM);
keywords.set("global", TokenType.GLOBAL);
keywords.set("if", TokenType.IF);
keywords.set("import", TokenType.IMPORT);
keywords.set("in", TokenType.IN);
keywords.set("is", TokenType.IS);
keywords.set("lambda", TokenType.LAMBDA);
keywords.set("nonlocal", TokenType.NONLOCAL);
keywords.set("not", TokenType.NOT);
keywords.set("or", TokenType.OR);
keywords.set("pass", TokenType.PASS);
keywords.set("raise", TokenType.RAISE);
keywords.set("return", TokenType.RETURN);
keywords.set("try", TokenType.TRY);
keywords.set("while", TokenType.WHILE);
keywords.set("with", TokenType.WITH);
keywords.set("yield", TokenType.YIELD);


export const scanTokens = (params) => {
    source = params
    while (!isAtEnd()) {
        start = current
        scanToken()
    }
    tokens.push(new Token(TokenType.EOF, "", null, line))
    return tokens
}

const isAtEnd = () => {
    return current >= source.length
}
const scanToken = () => {
    let c = advance()
    switch (c) {
        case '(': addToken(TokenType.LEFT_PARAN); break;
        case ')': addToken(TokenType.RIGHT_PARAN); break;
        case '{': addToken(TokenType.LEFT_BRACE); break;
        case '}': addToken(TokenType.RIGHT_BRACE); break;
        case ',': addToken(TokenType.COMMA); break;
        case '.': addToken(TokenType.DOT); break;
        case '-': addToken(TokenType.MINUS); break;
        case '+': addToken(TokenType.PLUS); break;
        case ';': addToken(TokenType.SEMICOLON); break;
        case '*': addToken(TokenType.STAR); break;
        case '!': addToken(match('=') ? TokenType.BANG_EQUAL : TokenType.BANG); break;
        case '=': addToken(match('=') ? TokenType.EQUAL_EQUAL : TokenType.EQUAL); break;
        case '>': addToken(match('=') ? TokenType.GREATER_EQUAL : TokenType.GREATER); break;
        case '<': addToken(match('=') ? TokenType.LESS_EQUAL : TokenType.LESS); break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && isAtEnd()) advance();
            }
            else {
                addToken(TokenType.SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            line++;
            break;
        case '"': string(); break;
        default:
            if (isDigit(c)) {
                number();
            }
            else if (isAlpha(c)) {
                identifier();
            }
            else {
                error(line, "Unexpected character.");
            }
            break;
    }
}
const identifier = () => {
    while (isAlphaNumeric(peek())) advance();
    let text = source.substr(start, current - start)
    let type = keywords.get(text)
    if (type === null) type = TokenType.IDENTIFIER;
    addToken(type);
}
const isAlpha = c => {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '_');
}
const isDigit = c => {
    return c >= '0' && c <= '9'
}
const isAlphaNumeric = c => {
    return isAlpha(c) || isDigit(c)
}
const number = () => {
    while (isDigit(peek())) advance();
    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) advance();
    }
    addToken(TokenType.NUMBER, parseFloat(source.substr(start, current - start)))
}
const string = () => {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }
    if (isAtEnd()) {
        error(line, "Unterminated string.");
        return;
    }
    advance();
    let value = source.substr(start + 1, current - start - 2)
    addToken(TokenType.STRING, value)
}
const peek = () => {
    if (isAtEnd()) return '\0';
    return source.charAt(current);
}
const peekNext = () => {
    if (isAtEnd()) return '\0';
    return source.charAt(current + 1);
}
const match = expected => {
    if (isAtEnd()) return false;
    if (source.charAt(current) != expected) return false;
    current++;
    return true;
}
const advance = () => {
    current++
    return source.charAt(current - 1)
}
const addToken = token => {
    addTokens(token, null)
}
const addTokens = (type, literal) => {
    let text = source.substr(start, current - start)
    tokens.push(new Token(type, text, literal, line))
}