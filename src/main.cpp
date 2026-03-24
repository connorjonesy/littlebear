#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../headers/player.h"
#include "../headers/level.h"
using namespace std;

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view){
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize({VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT});
}

int main(){
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "little bear");
    window.setPosition({0,0});
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));

    //Adding a texture to the shape
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/little-bear-walk.png"))
        return -1;
    Level level;
    Player player(&playerTexture, sf::Vector2u(4,1), 0.3f, 300.0f);
    Platform ground; //grass floor
    ground.shape.setSize(sf::Vector2f(500,500));
    ground.shape.setPosition({200.0f,400.0f});
    ground.shape.setFillColor(sf::Color(100,250,50));
    level.platforms.push_back(ground);

    sf::Font font;
    if (!font.openFromFile("../assets/NorthernBack.ttf"))
        return -1;
    sf::Text text(font, "Little Bear", 44);
    text.setFillColor(sf::Color::White);
    text.setPosition({0.0f, 200.0f});

    float deltaTime = 0.0f;
    sf::Clock clock;

    // Main loop to keep the window open
    while (window.isOpen()){
        deltaTime = clock.restart().asSeconds();
        //WINDOW  Event handling
        //sf::Event event;
        while(const auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
            if(event->is<sf::Event::Resized>())
                ResizeView(window,view);
        }
        player.Update(deltaTime, level.platforms);
        view.setCenter(player.GetPosition());
        //RENDER
        // Clear the window
        window.clear(sf::Color::Black);
        window.setView(view);
        //DRAW
        player.Draw(window);
        for (auto& platform : level.platforms) {
            window.draw(platform.shape);
        }
        window.draw(text);
        //DISPLAY 
        window.display();
   }
    return 0;
}

