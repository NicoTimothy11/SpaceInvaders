all: compile link

compile: g++ -lsrc/include -c main.cpp

link:
	g++*.o -o.main -lsrc/lib lsfml-graphics -lsfml-window -lsfml-system