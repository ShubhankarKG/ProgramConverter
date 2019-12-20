
#include "ProgramConverter.h"
//#include "Token.h"
#include "Scanner.h"

namespace ProjectConverter{
    bool ProgramConverter :: hadError = false;
    void ProgramConverter :: runFile(string path){
        // don't know :(
    }

    void ProgramConverter :: run (string source){
        Scanner* sc = new Scanner(source);
        list <Token*> tokens = sc->scanTokens();
        for (auto token : tokens){
            cout << token << endl;
        }
    }

    void ProgramConverter :: runPrompt(){
        for (;;){
            string s;
            cout <<">";
            getline(cin, s);
            run (s);
            hadError = false;
        }
    }

    void ProgramConverter :: report (int line, string where, string message){
        cout << "[line "  << line <<  " ] Error " << where << ": " << message << endl;
        hadError = true;
    }

    void ProgramConverter :: error (int line, string message){
        report (line, " ", message);
    }

    
}

int main(int args, char* argv[]){
        ProjectConverter :: ProgramConverter pc;
        pc.runPrompt();
        return 0;
    }
