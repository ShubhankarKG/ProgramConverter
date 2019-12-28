#ifndef PROGRAMCONVERTER_H
#define PROGRAMCONVERTER_H
#include <iostream>
#include <string>
#include "Scanner.hpp"
#include "Parser.hpp"
#include <cstdlib>
#include <fstream>


using namespace std;
class ProgramConverter {
    public :
    static bool hadError;
    void error(int line,const string &message);
    void runFile(const string &path);
    void runPrompt();
    void run(const string &source);
    void report(int line,const string &where,const string &message);
    void error(Token token, string message);
};

#endif