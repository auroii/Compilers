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
    return (DCC() && DCV() && DCP());
}


bool Parser::tipo_var() {
    SS type;
    Get(type);
    D(type.token);
    return (type.token == "integer" || type.token == "real");
}

bool Parser::DCP() {

}



bool Parser::DCC() {
    SS c;
    Get(c);
    if(c.token != "const") {
        index--;
        return true;
    }
    SS n, eq;
    Get(c);
    Get(eq);
    Get(n);
    D(c.token);
    D(n.token);
    D(eq.token);
    if(c.token != "Id" || eq.token != "=" || (n.token != "real" && n.token != "integer")) {
        return false;
    }
    SS pv;
    Get(pv);
    return DCC();

}


bool Parser::DCV() {
    SS var;
    Get(var);
    D(var.token);
    if(var.token != "var") {
        index--;
        return true;
    }

    if(!variaveis()) return false;
    SS dp;
    Get(dp);
    D(dp.token);
    if(dp.token != ":") return false;
    if(!tipo_var()) return false;
    SS pv;
    Get(pv);
    D(pv.token);
    if(pv.token != ";") return false;
    return DCV();
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


    if(tCmd.token[0] == 'i') {
        if(!condicao()) return false;
        SS th;
        Get(th);
        D(th.token);
        if(th.token != "then" || !(cmd() && pfalsa())) return false;
        return true;
    }

    if(tCmd.token[0] == 'b') {
        if(!comandos()) return false;
        SS e;
        Get(e);
        return (e.token == "end");
    }


    if(tCmd.token[0] == 'r' || tCmd.token == "write") {
        Get(bo);
        D(bo.token);
        if(!variaveis()) return false;
        Get(bc);
        D(bc.token);
        if(bo.token != "(" || bc.token != ")") return false; 
    }


    if(tCmd.token == "while") {
        Get(bo);
        D(bo.token);
        if(!condicao()) return false;
        Get(bc);
        D(bc.token);
        SS d;
        Get(d);
        D(d.token);
        if(d.token != "do" && bo.token != "(" || bc.token != ")") return false; 
        return cmd();
    }


    if(tCmd.token == "Id") {
        SS at;
        Get(at);
        D(at.token);
        if(at.token == ":=") {
            return expressao(); //por hora
        }

    }

    if(tCmd.token == "for") {
        SS i, rr;
        Get(i);
        Get(rr);
        D(i.token);
        D(rr.token);
        if(i.token != "Id" || rr.token != ":=") return false;

        if(!expressao()) return false;

        SS tt;
        Get(tt);
        D(tt.token);
        if(tt.token != "to" || !expressao()) return false;
        
        SS d;
        Get(d);
        D(d.token);
        if(d.token != "do") return false;
        return cmd();
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


bool Parser::condicao() {
    if(expressao()) {
        SS rel;
        Get(rel);
        D(rel.token);
        if(rel.token != "=" && rel.token != "<>" && rel.token != ">=" &&
                rel.token != "<=" && rel.token != ">" && rel.token != "<") {
                    return false;
        }

        return expressao();
    }
    return false;
}





bool Parser::pfalsa() {
    SS el;
    Get(el);
    if(el.token == "else") {
        D(el.token);
        return cmd();
    }

    index--;
    return true;
}