#ifndef PROGRAM_CONVERTER_H
#define PROGRAM_CONVERTER_H
#include <iostream>
#include <string>
#endif


using namespace std;
class ProgramConverter {
    public :
    static bool hadError;
    void error(int line,const string &message);
    void runFile(const string &path);
    void runPrompt();
    void run(const string &source);
    void report(int line,const string &where,const string &message);
};