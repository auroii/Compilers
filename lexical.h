#ifndef LEXICAL_H
#define LEXICAL_H

#include <utility>
#include <string>
#include <unordered_set>
#include <vector>


//classe que modela de forma desacoplacada um analisador lexico
class Lexical {
private:
	std::unordered_set<std::string> hash; //tabela hash de palavras reservadas 

	//metodo que implementa de forma implicita um automato que reconhece numeros inteiros e reais
	//retorna um par (cadeia, token)
	std::pair<std::string, std::string> process_number(const std::string& source, int& pointer);
	
	//metodo que implementa de forma implicita um automato que reconhece cadeias identificadoras ou reservadas
	//retorna um par (cadeia, token)
	std::pair<std::string, std::string> process_string(const std::string& source, int& pointer);

	//metodo que implementa de forma implicita um automato que reconhece caracteres especiais
	//retorna um par (cadeia, token)
	std::pair<std::string, std::string> process_ssymbols(const std::string& source, int& pointer);

public:
	//construtor da classe, usa a tabela de de palavras reservadas para construir a hash em tempo de execucao 
	Lexical(const std::vector<std::string>& cmd_table);
	
	//metodo que recebe uma string @source que possuir o codigo fonte do programa
	//@return (cadeia que acabou de ser lida, token para ser processado pelo analisador sintatico)
	//@pointer que eh a localizacao atual no codigo fonte
	std::pair<std::string, std::string> analyser(const std::string& source, int& pointer);
	
	//metodo que verifica se o programa possui balanceamento de parenteses
	//Eh executado antes de tudo, pois depende de informacoes de todo o codigo
	//return TRUE caso balanceado, FALSE cc
	bool brackets_balance(const std::string& source);	
};




#endif

