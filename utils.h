#ifndef UTILS_H
#define UTILS_H


#include <unordered_set>
#include <string>
#include <vector>



//tabela de palaras reservadas
static const std::vector<std::string> cmd_table { 
	"program", 
	"begin",
	"end",
	"read",
	"write",
	"while",
	"do",
	"if",
	"then",
	"to",
	"ident",
	"integer",
	"real",
	"var",
	"for",
	"else",
	"procedure", 
	"(",
	")",
	"{",
	"}",
	".",
	";",
	",",
	":",
	":=",
	"=",
	"+",
	"-",
	"*",
	"/",
	">",
	"<",
	">=",
	"<=",
	"<>",
	"const"};

//funcao que avanca pointer ate que nao haja mais caracteres transparentes
void front_trim(const std::string& source, int& pointer);
//retorna TRUE se for um caracter especial ou FALSE caso contrario
bool is_ssymbol(char ch);
			  	
#endif
