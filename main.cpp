#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include "headers/player.h"
using namespace std;

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view){
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main(){
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML Game");
    window.setPosition({0,0});
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));
    //Adding a texture to the shape
    sf::Texture playerTexture;
    playerTexture.loadFromFile("little-bear-walk.png");
    Player player(&playerTexture, sf::Vector2u(4,1), 0.3f, 300.0f);
    //Adding an obstacle rectangle shape
    sf::RectangleShape rect1(sf::Vector2f(50,100));
    rect1.setFillColor(sf::Color(100,250,50));
    rect1.setPosition(800.0f,300.0f);


    float deltaTime = 0.0f;
    sf::Clock clock;

    // std::cout << SFML_VERSION_MAJOR<<"."<<SFML_VERSION_MINOR<<"."<<SFML_VERSION_PATCH<< std::endl;
    // Main loop to keep the window open
    while (window.isOpen()){

	deltaTime = clock.restart().asSeconds();
        //WINDOW  Event handling
        sf::Event event;
	while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
	    }
	    if(event.type == sf::Event::Resized){
		ResizeView(window,view);
	    }
	}

	player.Update(deltaTime, player.getX(), player.getY(), );//include all coords
	view.setCenter(player.GetPosition());
	//RENDER
        // Clear the window
        window.clear(sf::Color::Black);
	window.setView(view);	
	//DRAW
        player.Draw(window);
	window.draw(rect1);
	//DISPLAY 
        window.display();
   }

    return 0;
}

