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
    //D(p.token);
    //D(i.token);
    //D(pv.token);
    if(p.token == "program" && i.token == "Id" && pv.token == ";") {
        line++;
        return corpo();
    }
    return false;
}

bool Parser::corpo() {
    SS beg, end;
    if(!DC()) return false;
    Get(beg);
    D(beg.token);
    if(beg.token != "begin") return false;



    if(!comandos()) return false;
    Get(end);
    if(end.token == "end") return true;
    return false;
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
    SS dp, type, pv;
    variaveis();
    Get(dp);
    Get(type);
    Get(pv);
    D(dp.token);
    D(type.token);

    if(!(pv.token == ";" && dp.token == ":" && (type.token == "integer" || type.token == "real"))) return false;
    SS beg;
    Get(beg);
    //D(beg.token);
    if(beg.token == "begin") index--;
    else DCV();

    return true;
}

bool Parser::variaveis() {
    SS id;
    Get(id);
    if(id.token == "Id") return mais_var();
    return false;
}


bool Parser::mais_var() {
    SS vir;
    Get(vir);

    if(vir.token == ",") return variaveis();
    if(vir.token == ":" || vir.token == ")") {
        index--;
        return true;
    }
    return true;
}


bool Parser::comandos() {
    if(!cmd()) return false;

    SS pv;
    Get(pv);
    D(pv.token);
    if(pv.token != ";") return false;
    SS test;
    Get(test);
    D(test.token);
    if(test.token == "end") {
        index--;
        return true;
    }
    index--;
    return comandos();
}

bool Parser::cmd() {
    SS tCmd;
    Get(tCmd);
    D(tCmd.token);
    SS bo, bc;

    if(tCmd.token[0] == 'r') {
        Get(bo);
        D(bo.token);
        if(!variaveis()) return false;
        Get(bc);
        D(bc.token);
        if(bo.token != "(" || bc.token != ")") return false; 
    }

    if(tCmd.token == "Id") {
        SS at;
        Get(at);
        D(at.token);
        if(at.token == ":=") {
            return expressao(); //por hora
        }

    }

    return true;
}

bool Parser::expressao() {
    if(termo()) {
        if(!outros_termos()) return false;
        return true;
    }
    return false;
}

bool Parser::termo() {
    if(op_un() && fator() && mais_fatores()) return true;
    return false;
}

bool Parser::op_un() {
    SS op;
    Get(op);
    if(op.token == "+" || op.token == "-") return true;
    index--;
    return true;
}

bool Parser::fator() {
    SS id;
    Get(id);
    D(id.token);
    if(id.token == "Id" || id.token == "integer" || id.token == "real") {
        
        return true;
    }
    index--;
    return true;
}

bool Parser::mais_fatores() {
    SS m;
    Get(m);
    bool temp = m.token == "*" || m.token == "/";
    D(m.token);
    if(temp) {
        return(fator() && mais_fatores());
    } 

    index--;
    return true;

}


bool Parser::outros_termos() {
    SS op;
    Get(op);
    D(op.token);
    bool temp = op.token == "+" || op.token == "-";
    if(temp) {
        return(termo() && outros_termos());

    }
    index--;
    return true;
}








