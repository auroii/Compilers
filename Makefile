all: lexical.o utils.o Parser.o tester.o test




Parser.o: Parser.cpp Parser.h lexical.h utils.h
	g++ -std=c++17 -c Parser.cpp

lexical.o: lexical.cpp lexical.h utils.h
	g++ -std=c++17 -c lexical.cpp


utils.o: utils.cpp utils.h
	g++ -std=c++17 -c utils.cpp


tester.o: tester.cpp lexical.h utils.h Parser.h
	g++ -std=c++17 -c tester.cpp


test: utils.o lexical.o Parser.o tester.o 
	g++ -std=c++17 utils.o lexical.o Parser.o tester.o -o P--


zip:
	zip compiladores *.cpp *.h *.pascal *.txt Makefile
