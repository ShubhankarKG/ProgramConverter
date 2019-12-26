CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main: ProgramConverter.o Scanner.o Token.o TokenType.o
		$(CXX) $(CXXFLAGS) -o main ProgramConverter.o Scanner.o Token.o TokenType.o

ProgramConverter.o: ProgramConverter.cpp ProgramConverter.hpp
					$(CXX) $(CXXFLAGS) -c ProgramConverter.cpp

Scanner.o: Scanner.hpp
Token.o: Token.hpp
TokenType.o: TokenType.hpp