#include "utils.h"
#include "lexical.h"
#include "Parser.h"
#include <string>
#include <iostream>

using std::cerr;

#define D(x) cerr << #x << " " << x << '\n'

#define token second

using std::string;

typedef std::pair<string, string> SS;

Parser::Parser(const std::vector<std::string>& cmd_table) {

    l = new Lexical(cmd_table);


}

bool Parser::start(const string& src, int pointer) {
    SS p = l->analyser(src, pointer);
    SS i = l->analyser(src, pointer);
    SS pv = l->analyser(src, pointer);
    //D(p.token);
  //  D(i.token);
   // D(pv.token);
    if(p.token == "program" && i.token == "Id" && pv.token == ";") {
        return corpo(src, pointer);
    }

    return false;

}


bool Parser::corpo(const string& src, int pointer) {
    return true;

}