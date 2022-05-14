all: clear compileObjects link run
flags = -c -g -std=c++17 -Wall -Werror

clear:
	rm o/*

compileObjects:
	g++ $(flags) Factoring.cpp -o o/Factoring.o
	g++ $(flags) Fraction.cpp -o o/Fraction.o
	g++ $(flags) Polynomial.cpp -o o/Polynomial.o
	g++ $(flags) Term.cpp -o o/Term.o
	g++ $(flags) Variable.cpp -o o/Variable.o

link:
	g++ -std=c++17 -Wall -Werror main.cpp o/*.o -o main

run:
	./main

checkSyntax:
	g++ -fsyntax-only -Wall *.cpp