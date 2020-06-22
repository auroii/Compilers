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


    //todas as rotinas abaixo implementam a gramatica do pascal pelo algoritmo descendente recursivo, fazendo o uso do fato de que estão fatoradas
    //e nao ha recursao a esquerda
    //as rotinas com um interiro op de parametro sao aquelas que inserem o identificador de variaveis declaradas para inspecao posterior
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
    
    //ERROS ---> enumeracao para especificar que tipo de erro sintatico ocorreu
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

    void pError(int); //funcao que recebe um inteiro mapeado pelo enum acima e printa um erro baseado neste inteiro

    int line; //linha atual do codigo
    int index; //token atual que o analisador lexico propocionou
    bool scannerError; //flag que seta como true se um erro lexico foi encontrado
    vector<pair<string, string>> v; //vetor de pares (nome, token) pós loop lexico
    set<string> bag; //conjunto de variaveis declaradas pelo seu identificador
    

public:
    Lexical *l; //uma instancia de um analisador lexico
    
    Parser(const std::vector<std::string>& cmd_table, const string&); //constroi a tabela de palavras reservadas, e extrai uma lista de tokens via analise lexica


    bool start(); //realiza o parser em si


    int getLine() { return line;}

};



#endif
