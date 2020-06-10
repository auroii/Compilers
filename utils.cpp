#include "utils.h"
#include <unordered_set>
#include <string>
#include <ctype.h>




void front_trim(const std::string& source, int& pointer) {
	while((int) source.size() > pointer && isspace(source[pointer])) pointer++;
}


bool is_ssymbol(char ch) {
	
	return(ch == '+' || ch == '-' || ch == '*' || ch == '/' 
			|| ch == ';' || ch == ':' || ch == '<' || ch == '>' 
			|| ch == '=' || ch == ')' || ch == '(' || ch == '.' || ch == ',');
}
	
