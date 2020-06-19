#ifndef PARSER_H
#define PARSER_H

#include "lexical.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::pair;

class Parser {
private:

    void Get(pair<string, string> &);
    bool corpo();
    bool DC();
    bool DCV();
    bool variaveis();
    bool mais_var();
    bool comandos();
    bool cmd();
    bool expressao();
    bool termo();
    bool fator();
    bool mais_fatores();
    bool outros_termos();
    bool op_un();
    bool condicao();
    bool pfalsa();
    
    int line;
    int index;
    vector<pair<string, string>> v;

public:
    Lexical *l;
    
    Parser(const std::vector<std::string>& cmd_table, const string&);


    bool start();


    int getLine() { return line;}

};



#endif