CXX = g++
CXXFLAGS = -g -std=c++11

main: ProgramConverter.o Scanner.o Token.o TokenType.o Expression.o Parser.o
		$(CXX) $(CXXFLAGS) -o main ProgramConverter.o Scanner.o Token.o TokenType.o Expression.o Parser.o

ProgramConverter.o: ProgramConverter.cpp ProgramConverter.hpp
					$(CXX) $(CXXFLAGS) -c ProgramConverter.cpp

Scanner.o: Scanner.hpp
Token.o: Token.hpp
TokenType.o: TokenType.hpp
Expression.o: Expression.hpp
Parser.o: Parser.hpp