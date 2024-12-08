CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: main.cpp Grille.cpp Cellule.cpp Vue.cpp Controleur.cpp
	$(CXX) $(CXXFLAGS) -o jeu_de_la_vie main.cpp Grille.cpp Cellule.cpp Vue.cpp Controleur.cpp $(LDFLAGS)

clean:
	rm -f main
