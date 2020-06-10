#include <utility>
#include <string>
#include "lexical.h"
#include <unordered_set>
#include <vector>
#include <iostream>
#include <assert.h>
#include "utils.h"
#include <ctype.h>


bool Lexical::brackets_balance(const std::string& source) {
	int counter = 0; //contador que eh incrementado caso encontrar ( ou decrementado caso )

	for(char ch : source) {
		if(ch == '(') counter++;
		else if(ch == ')') {
			counter--;
			if(counter < 0) return false; //se counter < zero, entao ha mais fechadas do que abertas
		}
	}

	return (counter == 0); //true se o numero de abertas for igual ao de fechadas
}

//caso o primeiro caracter for um numero zero...nove
std::pair<std::string, std::string> Lexical::process_number(const std::string& source, int& pointer) {
	//definicao das variaveis usadas
	std::string buffer = ""; //cadeia
	std::string token = ""; //token
	int N = source.size(); //tamanho total do codigo
	buffer += source[pointer++]; //coloca o primeiro numero no buffer
	

	//enquanto tiver numeros, inserir no buffer
	while(pointer < N && isdigit(source[pointer])) buffer += source[pointer++];
		
	//letra latina dentro de um numero, erro -> numero mal formatado
	if(pointer < N && isalpha(source[pointer])) {
		return make_pair(buffer, "ERRO: NUMERO MAL FORMATADO");
	}
		

	if(pointer < N && source[pointer] == '.') { //encontrou um ponto, entao eh numero real
		token = "real";
		buffer += source[pointer++]; //inserir ponto no buffer
		bool any = false; //any eh false se nao ha numero depois do ponto, true caso contrario
		while(pointer < N && isdigit(source[pointer])) { //lendo os numeros apos o ponto
			any = true;
			buffer += source[pointer++];
		}
		
		if(!any || (pointer < N && isalpha(source[pointer]))) { //numero mal formatado	
			return make_pair(buffer, "ERRO: NUMERO MAL FORMATADO");
		}
	} else token = "integer";
	
	return std::make_pair(buffer, token);
}


//caso o primeiro caracter seja uma letra do alfabeto latino
std::pair<std::string, std::string> Lexical::process_string(const std::string& source, int& pointer) {
	std::string buffer = ""; //inicializa a cadeia e le a primeira letra
	int N = source.size();
	buffer += source[pointer++]; 
	
	while(true) { //loop ate encontrar um quebra de padrao
		if(pointer < N) { //se o codigo nao chegou ao fim

			//se o caracter for uma letra ou um numero, inserir no buffer
			if(isalnum(source[pointer])) buffer += source[pointer++]; 
			//se for um simbolo especial ou caracter transparente, encerrar tokenizacao
			else if(is_ssymbol(source[pointer]) || isspace(source[pointer])) {
				//verifica se eh palavra reservada
				if(hash.count(buffer)) return std::make_pair(buffer, buffer);
				else return std::make_pair(buffer, "Id"); //caso nao for, eh um identificador
			} 
			else {	
				buffer += source[pointer++];//caracter nao permitido foi encontrado 
				return std::make_pair(buffer, "ERRO: CARACTER NAO PERMITIDO");
			}
		} else break;
	}

	return std::make_pair(buffer, "Id");
}


//caso o primeiro caracter seja especial
std::pair<std::string, std::string> Lexical::process_ssymbols(const std::string& source, int& pointer) {
	std::string buffer = ""; //cadeia a ser retornada
	int N = source.size();
	

	//operadores unarios
	if(source[pointer] == '+') {
		pointer++;
		return {"+", "+"};
	}
	if(source[pointer] == '-') {
		pointer++;
		return {"-", "-"};
	}
	if(source[pointer] == '*') {
		pointer++;
		return {"*", "*"};
	}
	if(source[pointer] == '/') {
		pointer++;
		return {"/", "/"};
	}

	if(source[pointer] == '(') {
		pointer++;
		return {"(", "("};
	}

	if(source[pointer] == ')') {
		pointer++;
		return {")", ")"};
	}
	if(source[pointer] == ';') {
		pointer++;
		return {";", ";"};
	}
	
	if(source[pointer] == ',') {
		pointer++;
		return {",", ","};
	}
	if(source[pointer] == '.') {
		pointer++;
		return {".", "."};
	}

	//operadores que podem ser unarios ou nao
	if(source[pointer] == ':') {
		if(pointer + 1 < N) {
			if(source[pointer + 1] == '=') {
				pointer += 2;
				return {":=", ":="};
			}
		}
		pointer++;
		return {":", ":"};
	}

	if(source[pointer] == '>') {
		if(pointer + 1 < N) {
			if(source[pointer + 1] == '=') {
				pointer += 2;
				return {">=", ">="};
			}
		} 
		pointer++;
		return {">", ">"};
	} 


	if(source[pointer] == '<') {
		if(pointer + 1 < N) {
			if(source[pointer + 1] == '=') {
				pointer += 2;
				return {"<=", "<="};
			} else if(source[pointer + 1] == '>') {
				pointer += 2;
				return {"<>", "<>"};
			}
		}
		
		pointer++;
		return {"<", "<"};
	}
	
	if(source[pointer] == '=') {
		pointer++;
		return {"=", "="};
	}
		
	return {"", ""};
}
	

//metodo mestre do analisador, que invoca os metodos auxiliares
std::pair<std::string, std::string> Lexical::analyser(const std::string& source, int& pointer) {
	front_trim(source, pointer); //remove os espacos iniciais
	
	if(source[pointer] == '{') { //caso for comentario, ignorar ate fecha de colchetes
		while(pointer < (int) source.size() && source[pointer++] != '}');
		return {"", ""};
	}


	if((int) source.size() == pointer) return {"", ""}; //esta no final do codigo fonte

	if(isdigit(source[pointer])) { //se o primeiro caracter for um digito numerico
		return process_number(source, pointer);
	}  
	else if(isalpha(source[pointer])) {//se o primeiro caracter for uma letra do alfabeto
		return process_string(source, pointer);
	} else if(is_ssymbol(source[pointer])) { //se o primeiro caracter for especial
		return process_ssymbols(source, pointer);
	}
	

	return {"", ""}; 
}


Lexical::Lexical(const std::vector<std::string>& cmd_table) {
	for(std::string it : cmd_table) { //para cada string reservada, inserir na hash
		hash.insert(it);
	}

}




