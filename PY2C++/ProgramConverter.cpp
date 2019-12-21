
#include "ProgramConverter.h"
//#include "Token.h"
#include "Scanner.h"
#include <cstdlib>

bool ProgramConverter :: hadError = false;
void ProgramConverter :: runFile(const string &path){
    // don't know :(
}

void ProgramConverter :: run (const string &source){
    Scanner *sc = new Scanner(source);
    vector <Token*> tokens = sc->scanTokens();
    for (auto token : tokens){
        cout << token << endl;
    }
    // for (auto token : tokens){
    //     cout << token.literal <<" " <<token.line << endl;
    // }
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

void ProgramConverter :: report (int line,const string& where,const string& message){
    cout << "[line "  << line <<  " ] Error " << where << ": " << message << endl;
    hadError = true;
}

void ProgramConverter :: error (int line,const string& message){
    report (line, "", message);
}

int main(int args, char* argv[]){
        ProgramConverter pc;
        if (args>2){
            std :: cout <<"Usage : script testing \n";
            exit(0);
        }
        else if (args==2){
            pc.runPrompt();
        }
        else {
            pc.runFile(argv[1]);
        }

        return 0;
    }
