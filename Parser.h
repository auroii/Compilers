#ifndef PARSER_H
#define PARSER_H

#include "lexical.h"
#include <string>
#include <vector>
#include <set>

using std::vector;
using std::string;
using std::pair;
using std::set;

class Parser {
private:

    void Get(pair<string, string> &);
    bool corpo();
    bool DC();
    bool DCV();
    bool variaveis(int op = 0);
    bool mais_var(int op = 0);
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
    bool DCC();
    bool DCP();
    bool tipo_var();
    bool parametros(int op = 0);
    bool lista_par(int op = 0);
    bool mais_par(int op = 0);
    bool corpo_p();
    bool DC_loc();
    bool mais_ident();
    bool lista_arg();
    bool argumentos();
    
    //ERROS
    enum {
        PONTO_VERGULA,
        ESTRUTURA,
        TIPO,
        DOIS_PONTOS,
        IDENT,
        LOOP,
        VAR,
        OPERADOR

    };

    void pError(int);

    int line;
    int index;
    bool scannerError;
    vector<pair<string, string>> v;
    set<string> bag;
    

public:
    Lexical *l;
    
    Parser(const std::vector<std::string>& cmd_table, const string&);


    bool start();


    int getLine() { return line;}

};



#endif
