# run ./compiler.sh on Linux
# Use cmake on MacOs
g++ -c main.cpp animation.cpp player.cpp
g++ main.o animation.o player.o -o bin/sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./bin/sfml-app
