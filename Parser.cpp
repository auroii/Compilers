#include "utils.h"
#include "lexical.h"
#include "Parser.h"
#include <string>
#include <iostream>
#include <vector>

using std::cerr;
using std::vector;
#define D(x) cerr << #x << " " << x << '\n'

#define token second

using std::string;

typedef std::pair<string, string> SS;

Parser::Parser(const std::vector<std::string>& cmd_table, const string& src) {
    line = 0;
    l = new Lexical(cmd_table);
    SS it;
    int pointer = 0;
    index = 0;
    while(true) {
        it = l->analyser(src, pointer);
        if(!it.token.empty() && it.token != "-1") v.push_back(it);
        else if(it.token == "-1") break;
    }

}


void Parser::Get(SS & curr) {
    if(index < (int) v.size()) curr = v[index++]; 
    else curr = {"", "-1"};
}

bool Parser::start() {
    SS p, i, pv;
    Get(p);
    Get(i);
    Get(pv);
    D(p.token);
    D(i.token);
    D(pv.token);
    if(p.token == "program" && i.token == "Id" && pv.token == ";") {
        line++;
        //return corpo();
    }
    return false;
}

bool Parser::corpo() {
    SS beg, end;
    if(!DC()) return false;
    Get(beg);
    if(beg.token != "begin") return false;
    return true;
}

bool Parser::DC() {
    SS dc;
    Get(dc);
    D(dc.token);
    if(dc.token[0] == 'v') {
        return DCV();
    }

    return false;
}


bool Parser::DCV() {
    SS dp, type;
    variaveis();
    Get(dp);
    Get(type);

    D(dp.token);
    D(type.token);

    if(!(dp.token == ":" && (type.token == "integer" || type.token == "real"))) return false;
    SS beg;
    Get(beg);
    D(beg.token);
    if(beg.token == "begin") index--;
    else DCV();

    return true;
}

bool Parser::variaveis() {
    SS id;
    Get(id);
    if(id.token == "Id") return mais_var();

}


bool Parser::mais_var() {
    SS vir;
    Get(vir);

    if(vir.token == ",") return variaveis();

}











