#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../headers/player.h"
#include "../headers/level.h"
using namespace std;
#include <iostream>

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view){
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    float viewWidth = VIEW_HEIGHT * aspectRatio;
	view.setSize({VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT});
    view.setCenter({VIEW_HEIGHT / 2.0f, VIEW_HEIGHT / 2.0f});
    view.setCenter({viewWidth / 2.0f, VIEW_HEIGHT / 2.0f});
}

int main(){

    std::cout << "SFML Version: " 
              << SFML_VERSION_MAJOR << "." 
              << SFML_VERSION_MINOR << "." 
              << SFML_VERSION_PATCH << std::endl;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "little bear");
    sf::View view;
    ResizeView(window,view);

    //Add background image (TEMP: can add multiple levels and bg's later)
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("../assets/bg1.png"))
        return -1;

    sf::Sprite bg(bgTexture);
    sf::Vector2u textureSize = bgTexture.getSize();

    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    bg.setScale({scaleX, scaleY});
    bg.setPosition({0.0f,0.0f});

    //Adding the little bear text to screen
    sf::Font font;
    if (!font.openFromFile("../assets/NorthernBack.ttf"))
        return -1;
    sf::Text text(font, "Little Bear", 44);
    text.setFillColor(sf::Color::Black);
    text.setPosition({0.0f, 200.0f});

    //Create player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/little-bear-walk.png"))
        return -1;
    Player player(&playerTexture, sf::Vector2u(4,1), 0.3f, 300.0f);
    
    //Create level & platforms
    Level level;
    Platform ground; //grass floor
    ground.shape.setSize(sf::Vector2f(2000,10));
    ground.shape.setPosition({-460.0f,960.0f});
    ground.shape.setFillColor(sf::Color::Transparent);
    level.platforms.push_back(ground);
    //Test platform for testing jumping physics moving forward
    Platform tester;
    tester.shape.setSize(sf::Vector2f(400,40));
    tester.shape.setPosition({0.0f,460.0f});
    tester.shape.setFillColor(sf::Color::Black);
    level.platforms.push_back(tester);
    //Create Menu object
    Menu menu;

    // Main loop to keep the window open
    bool isPaused = false;
    float deltaTime = 0.0f;
    sf::Clock clock;
    while (window.isOpen()){
        deltaTime = clock.restart().asSeconds();
        //WINDOW  Event handling
        //sf::Event event;
        while(const auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
            if(event->is<sf::Event::Resized>())
                ResizeView(window,view);
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    isPaused = !isPaused;
            }

        }
        player.Update(deltaTime, level.platforms);
        //RENDER
        // Clear the window
        window.clear(sf::Color::Black);
        window.setView(view);
        //DRAW --order decides z-index
        window.draw(bg);
        window.draw(text);
        player.Draw(window);
        for (auto& platform : level.platforms) {
            window.draw(platform.shape);
        }
        if(isPaused){
            menu.showMenu(1, window);
        }
        //DISPLAY 
        window.display();
   }
    return 0;
}

