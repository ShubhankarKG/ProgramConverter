#ifndef PROGRAM_CONVERTER_H
#define PROGRAM_CONVERTER_H
#include <iostream>
#include <string>
#endif

using namespace std;
class ProgramConverter {
    public :
    static bool hadError;
    void error(int line, string message);
    void runFile(string path);
    void runPrompt();
    void run(string source);
    void report(int line, string where, string message);
};