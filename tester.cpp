#include "utils.h"
#include "lexical.h"
#include <string>
#include <list>
#include <utility>
#include <iostream>
#include <fstream>


//CODIGO DE TESTE PARA SIMULAR AS CHAMADAS DO ANALISADOR LEXICO 
//RECEBE UM ARQUIVO .PASCAL E APLICA A ANALISE LEXICA

int main(int argc, char **argv) {
	std::ifstream fp;
	fp.open(argv[1]); //abre o arquivo e o salva numa string
	
	std::string src = "";
	while(!fp.eof()) {
		src += fp.get();
	}
	src.pop_back();
	//std::cerr << src;

	Lexical *lex = new Lexical(cmd_table); //instancia um objetivo analisador lexico
	
	if(lex->brackets_balance(src) == false) {
		std::cerr << "BRACKETS UNBALANCED\n";
	}

	int pointer = 0;//ponteiro que indica a posicao atual no programa
	std::list<std::pair<std::string, std::string>> token_table; //lista de pares (cadeia, token)
	
	//loop para ir recuperando de token em token 
	std::pair<std::string, std::string> p;
	while(pointer < (int) src.size()) {
		p = lex->analyser(src, pointer);
		//std::cerr << p.first << ' ' << p.second << '\n';
		token_table.push_back(p);
	}

	for(auto it : token_table) { //print da lista
		std::cerr << it.first << " " << it.second << '\n';
	}

	delete lex; 
	fp.close();

}





