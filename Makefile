all:
	g++ -o game main.cpp -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm