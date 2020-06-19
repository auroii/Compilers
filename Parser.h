#ifndef PARSER_H
#define PARSER_H

#include "lexical.h"
#include <string>

using std::string;

class Parser {
public:
    Lexical *l;
    static int line = 0;
    Parser(const std::vector<std::string>& cmd_table);


    bool start(const string&, int);
    bool corpo(const string& src, int pointer);


};



#endif