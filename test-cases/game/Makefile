all: editor.out game.out
editor.out: editor.cpp
	g++ -Wall editor.cpp ../../lib/*.cpp -o editor.out -lGL -lGLU -lglut
game.out: game.cpp Pista.cpp
	g++ -Wall Pista.cpp game.cpp ../../lib/*.cpp -o game.out -lGL -lGLU -lglut
clean:
	rm -f *.out
