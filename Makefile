all: main
main: onegin.cpp sorting_algs.cpp main.cpp
	g++ -o main main.cpp onegin.cpp sorting_algs.cpp