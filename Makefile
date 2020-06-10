all: lexical.o utils.o tester.o test



lexical.o: lexical.cpp lexical.h utils.h
	g++ -std=c++17 -c lexical.cpp


utils.o: utils.cpp utils.h
	g++ -std=c++17 -c utils.cpp


tester.o: tester.cpp lexical.h utils.h
	g++ -std=c++17 -c tester.cpp


test: utils.o lexical.o tester.o
	g++ -std=c++17 utils.o lexical.o tester.o -o P--


zip:
	zip compiladores *.cpp *.h *.pascal *.txt Makefile
