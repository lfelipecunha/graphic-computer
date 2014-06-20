all: editor.out game.out
editor.out: editor.cpp
	g++ -Wall editor.cpp ../../lib/*.cpp -o editor.out -lGL -lGLU -lglut
game.out: game.cpp Pista.cpp Car.cpp ../../lib/*.cpp
	g++ -Wall Car.cpp Pista.cpp game.cpp ../../lib/*.cpp -o game.out -lGL -lGLU -lglut
clean:
	rm -f *.out
