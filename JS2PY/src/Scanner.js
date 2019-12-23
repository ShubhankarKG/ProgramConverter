import ProgramConverter from './ProgramConverter'
import TokenType from './TokenType'
import Token from './Token'

class Scanner {
    ProgramConverter = new ProgramConverter()
    static keywords = new Map()
    start = 0
    current = 0
    line = 1
    source = ""
    tokens = new Array()

    constructor(source) {
        this.source = source
        keywords.set("and", TokenType.AND);
        keywords.set("class", TokenType.CLASS);
        keywords.set("else", TokenType.ELSE);
        keywords.set("false", TokenType.FALSE);
        keywords.set("fun", TokenType.FUN);
        keywords.set("for", TokenType.FOR);
        keywords.set("if", TokenType.IF);
        keywords.set("nil", TokenType.NIL);
        keywords.set("or", TokenType.OR);
        keywords.set("print", TokenType.PRINT);
        keywords.set("return", TokenType.RETURN);
        keywords.set("super", TokenType.SUPER);
        keywords.set("this", TokenType.THIS);
        keywords.set("true", TokenType.TRUE);
        keywords.set("var", TokenType.VAR);
        keywords.set("while", TokenType.WHILE);
    }

    scanTokens = () => {
        while (!isAtEnd()) {
            start = current
            this.scanToken()
        }
        this.tokens.push(new Token(TokenType.EOF, "", null, line))
        return this.tokens
    }

    isAtEnd = () => {
        return this.current >= this.source.length
    }
    scanToken = () => {
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
                    ProgramConverter.error(line, "Unexpected character.");
                }
                break;
        }
    }
    identifier = () => {
        while (isAlphaNumeric(peek())) advance();
        let text = this.source.substr(this.start, this.current - this.start)
        let type = keywords.get(text)
        if (type === null) type = TokenType.IDENTIFIER;
        addToken(type);
    }
    isAlpha = c => {
        return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_');
    }
    isDigit = c => {
        return c >= '0' && c <= '9'
    }
    isAlphaNumeric = c => {
        return this.isAlpha(c) || this.isDigit(c)
    }
    number = () => {
        while (isDigit(peek())) advance();
        if (peek() == '.' && isDigit(peekNext())) {
            advance();
            while (isDigit(peek())) advance();
        }
        addToken(TokenType.NUMBER, parseFloat(this.source.substr(this.start, this.current - this.start)))
    }
    string = () => {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }
        if (isAtEnd()) {
            ProgramConverter.error(line, "Unterminated string.");
            return;
        }
        advance();
        let value = this.source.substr(this.start + 1, this.current - this.start - 2)
        addToken(TokenType.STRING, value)
    }
    peek = () => {
        if (isAtEnd()) return '\0';
        return source.charAt(current);
    }
    peekNext = () => {
        if (isAtEnd()) return '\0';
        return source.charAt(current + 1);
    }
    match = expected => {
        if (isAtEnd()) return false;
        if (source.charAt(current) != expected) return false;
        this.current++;
        return true;
    }
    advance = () => {
        this.current++
        return this.source.charAt(this.current - 1)
    }
    addToken = token => {
        addToken(token, null)
    }
    addToken = (type, literal) => {
        text = this.source.substr(this.start, this.current - this.start)
        this.tokens.push(new Token(type, text, literal, line))
    }
}

export default Scanner