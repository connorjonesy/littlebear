#include <SFML/Graphics.hpp>
#include "../headers/menus.h"
#include <iostream>

Menu::Menu(){};

void Menu::showMenu(int choice, sf::RenderWindow& window){
	std::string selection;
	switch(choice){
		case 0:
			displayMainMenu();
			break;
		case 1:
			displayPauseMenu(window);
			break;
		default:
			std::cout << "Not a valid selection for a menu" << std::endl;
			break;
	}
}

void Menu::displayPauseMenu(sf::RenderWindow& window){
	//TODO fix hardcoded centering of UI elements
	sf::RectangleShape menu_UI;
	menu_UI.setOrigin({0.0f,0.0f});
	menu_UI.setPosition({600.0f,300.0f});
	menu_UI.setSize({300.0f, 100.0f});
	menu_UI.setFillColor(sf::Color::Black);

	sf::Font font;
	if (!font.openFromFile("../assets/NorthernBack.ttf"))
		std::cout << "Couldnt open the font lad" << std::endl;
	sf::Text exit_text(font, "Exit to Destop", 44);
	exit_text.setFillColor(sf::Color::White);
	exit_text.setPosition({630.0f, 320.0f}); //hardcoded centering... for now

	window.draw(menu_UI);
	window.draw(exit_text);

	sf::Vector2i localMousePos = sf::Mouse::getPosition(window); //relative to the window
	std::cout << "Mouse x,y: (" << localMousePos.x << "," << localMousePos.y << ")" << std::endl;
	
	//TODO Refactor lol
	if(localMousePos.x > menu_UI.getPosition().x && localMousePos.x < (menu_UI.getPosition().x + menu_UI.getSize().x) && localMousePos.y > menu_UI.getPosition().y && localMousePos.y < (menu_UI.getPosition().y + menu_UI.getSize().y))
		std::cout << "Mouse is within Pause Menu" << std::endl;

	//if user clicks button
	    //window.close();

}

void Menu::displayMainMenu(){
}
