
#include "ProgramConverter.hpp"

bool ProgramConverter :: hadError = false;
void ProgramConverter :: runFile(const string &path){
    ifstream infile(path, ios::binary);
    infile.seekg(0, ios::end);
    size_t size = infile.tellg();
    infile.seekg(0, ios::beg);
    streambuf* raw_buffer = infile.rdbuf();
    char* block = new char[size];
    raw_buffer -> sgetn(block, size);
    string line(block);
    delete[] block;

    run(line);
    if (hadError) exit(1);
    // don't know :(
}

void ProgramConverter :: run (const string &source){
    Scanner *sc = new Scanner(source);
    vector <Token> tokens = sc->scanTokens();
    Parser* parser = new Parser(tokens);
    Expr* expr = parser->parse();
    cout << "No error \n";
    if (hadError) return;
    cout<< "Parser up, not sure about running\n";
    // for (auto token : tokens){
    //     cout << token.toString() << "\n";
    // }
}

void ProgramConverter :: runPrompt(){
    for (;;){
        string s;
        cout <<">";
        getline(cin, s);
        cout << s << endl;
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

void ProgramConverter :: error(Token token, string message){
    if (token.type == EOFile){
        report(token.line, "at end ", message);
    }
    else {
        report(token.line, " at '" + token.lexeme + "'" , message);
    }
}

int main(int args, char* argv[]){
        ProgramConverter pc;
        if (args>2){
            std :: cout <<"Usage : script testing \n";
            exit(0);
        }
        else if (args==2){
            pc.runFile(argv[1]);
        }
        else {
            pc.runPrompt();
        }

        return 0;
    }
