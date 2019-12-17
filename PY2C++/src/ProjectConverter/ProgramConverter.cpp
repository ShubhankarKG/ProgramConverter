#include <iostream>
#include <cstdlib>
#include "Token.cpp"
#include <list>
#include <iterator>
#include "Scanner.cpp"

using namespace std;
bool hadError = false;

void report(int line, string where, string message){
    cout << "[line " << line << " ] Error" << where << ": " << message;
    hadError = true;
}

void error(int line, string message){
    report(line, "", message);
}

void run(string source){
    Scanner scanner = new Scanner(source);
    list <Token> tokens = scanner.scanTokens();
    for (Token token : tokens){
        token.print() ;
        cout <<" \n";
    }
}

void runFile(string path){
    // Don't know still :(
}

void runPrompt(){
    for(;;){
        string s;
        cout <<"> ";
        cin >> s;
        run(s);
        hadError = false;
    }
}

int main(int args, char* argv[]){
    if (args > 1){
        cout <<" Usage: programConverter [script] \n";
        exit(0);
    }
    else if (args == 1){
        runFile(argv[0]);
    }
    else {
        runPrompt();
    }
}
