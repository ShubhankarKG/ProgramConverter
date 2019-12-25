CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main: ProgramConverter.o Scanner.o Token.o TokenType.o
		$(CXX) $(CXXFLAGS) -o main ProgramConverter.o Scanner.o Token.o TokenType.o

ProgramConverter.o: ProgramConverter.cpp ProgramConverter.h
					$(CXX) $(CXXFLAGS) -c ProgramConverter.cpp

Scanner.o: Scanner.h
Token.o: Token.h
TokenType.o: TokenType.h