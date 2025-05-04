g++ -c main.cpp animation.cpp player.cpp
g++ main.o animation.o player.o -o bin/sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./bin/sfml-app
