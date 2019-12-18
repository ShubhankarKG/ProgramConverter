
#include "ProgramConverter.h"
#include "Token.h"
#include "Scanner.h"

bool ProgramConverter :: hadError = false;
void ProgramConverter :: runFile(string path){
    // don't know :(
}

void ProgramConverter :: run (string source){
    // list <Token*> tokens = scanTokens();
    // for (auto token : tokens){
    //     cout << token << endl;
    // }
}

void ProgramConverter :: runPrompt(){
    // for (;;){
    //     string s;
    //     cout <<">";
    //     getline(cin, s);
    //     run (s);
    //     hadError = false;
    // }
}

void ProgramConverter :: report (int line, string where, string message){
    cout << "[line "  << line <<  " ] Error " << where << ": " << message << endl;
    hadError = true;
}

void ProgramConverter :: error (int line, string message){
    report (line, " ", message);
}

int main(int args, char* argv[]){
    return 0;
}